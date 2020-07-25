//
// @author freemedude
// @date 2020-07-18
// @brief 
//

#include "application.hpp"

#include <iostream>
#include <cassert>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "utility.hpp"

Application::~Application()
{
    glfwTerminate();
}

void Application::Init()
{
    m_window.Init("Project Yellow", 1280, 720, &m_inputs);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glDepthRange(-1, 1);

    InitDearImGui();
    m_assets.Init("assets");

    m_inputs.invalidLastCursor = true;

    m_scene.TestScene();

    glm::ivec2 frameBufferSize = m_window.FrameBufferSize();
    float aspectRatio = (float) frameBufferSize.x / (float) frameBufferSize.y;
    float fov = glm::radians(45.0f);
    m_camera.InitPerspective(fov, aspectRatio, 0.1f, 1000.0f);
    m_camera.Position() = {0, 0, 10};
    m_camera.Rotation() = {0, 0, 0};
}

void Application::InitDearImGui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;
    const char *glsl_version = "#version 450";
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(m_window.GlfwWindow(), true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

bool Application::Done()
{
    return m_window.ShouldClose();
}

float Application::ClampDegrees(float deg)
{
    const float degMax = 180.0f;
    float mod = glm::mod(deg + degMax, degMax * 2);
    float result = mod - degMax;
    return result;
}

void Application::Update()
{
    StartFrame();

    RenderScene();

    RenderGui();

    EndFrame();
}

void Application::StartFrame()
{
    m_frameStart = glfwGetTime();

    HandleInputs();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Application::EndFrame()
{
    m_window.SwapBuffers();
    m_frameEnd = glfwGetTime();
    m_deltaTime = (float) glm::max(m_frameEnd - m_frameStart, 0.0);
}

void Application::HandleInputs()
{
    m_window.GetInputs();

    if (m_inputs.quit)
    {
        m_window.Close();
    }

    m_window.CursorLocked(m_inputs.cursorLocked);
    m_inputs.invalidLastCursor = !m_inputs.cursorLocked;

    if (m_inputs.cursorLocked)
    {
        HandleCameraInputs();
    }
}


void Application::HandleCameraInputs()
{
    auto directionFromBooleans = [](bool negative, bool positive) -> float
    {
        float result = float(positive - negative);
        return result;
    };
    glm::vec3 cameraMovement{};
    cameraMovement.x = directionFromBooleans(m_inputs.left, m_inputs.right);
    cameraMovement.y = directionFromBooleans(m_inputs.down, m_inputs.up);
    cameraMovement.z = directionFromBooleans(m_inputs.back, m_inputs.forward);
    m_camera.AddLocal(cameraMovement * (float) m_deltaTime * m_moveSpeed);

    // Rotation
    {
        glm::vec2 delta = m_inputs.mousePos - m_inputs.lastMousePos;
        delta.y = -delta.y;
        delta *= m_mouseSensitivity;

        glm::vec3 deltaAdjusted = {delta.y, delta.x, 0};

        glm::vec3 newRot = deltaAdjusted + m_camera.Rotation();

        // Avoid gimbal lock
        newRot.x = glm::clamp(newRot.x, -89.0f, 89.0f);
        newRot.y = ClampDegrees(newRot.y);
        m_camera.Rotation() = newRot;

        m_inputs.lastMousePos = m_inputs.mousePos;
        m_inputs.invalidLastCursor = false;
    }
}

void Application::RenderScene()
{
    m_lightPitch += m_lightPitchSpeed * m_deltaTime;
    float pitch = glm::radians(m_lightPitch);

    m_lightYaw += m_lightYawSpeed * m_deltaTime;
    float yaw = glm::radians(m_lightYaw);

    glm::vec4 direction = {0, 0, -1, 0};

    direction = glm::rotateX(direction, pitch);
    direction = glm::rotateY(direction, yaw);

    for (auto model : m_scene.Models())
    {
        glm::mat4 modelMat = model->m_transform.Matrix();
        glm::mat4 viewMat = m_camera.ViewMatrix();
        glm::mat4 modelViewMat = viewMat * modelMat;
        glm::mat4 projMat = m_camera.ProjectionMatrix();
        glm::mat4 mvp = projMat * modelViewMat;

        auto mat = model->m_material;
        auto pipeline = mat->m_pipeline;
        glBindTexture(GL_TEXTURE_2D, mat->m_texture->m_id);

        mat->m_pipeline->Use();

        pipeline->SetMatrix4("u_model", modelMat);
        pipeline->SetMatrix4("u_view", viewMat);
        pipeline->SetMatrix4("u_modelView", modelViewMat);
        pipeline->SetMatrix4("u_mvp", mvp);
        pipeline->SetVector4("u_color", mat->m_color);
        pipeline->SetVector3("u_lightDirection", direction);
        pipeline->SetFloat("u_ambientIntensity", m_ambientIntensity);
        pipeline->SetVector3("u_ambientColor", m_ambientColor);
        pipeline->SetVector3("u_cameraPosition", m_camera.Position());


        model->m_mesh->Bind();

        int numIndices = (int) model->m_mesh->Count();
        glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, nullptr);
    }

}

void Application::RenderGui()
{
    ImVec4 headerColor = {1, 0, 0, 1};

    // Sanitize degrees for display
    m_lightPitch = ClampDegrees(m_lightPitch);
    m_lightYaw = ClampDegrees(m_lightYaw);

    ImGui::Begin("Hello, world!");
    float frameRate = ImGui::GetIO().Framerate;
    ImGui::Text(
            "Application average %.3f ms/frame (%.1f FPS)",
            1000.0f /
            frameRate, frameRate);
    ImGui::Text(
            "MS This Frame: %.3fms",
            m_deltaTime * 1000);

    ImGui::Checkbox("Cursor disabled", &m_inputs.cursorLocked);
    if (m_inputs.cursorLocked)
    {
        ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NoMouse;
    } else
    {
        int mask = ~ImGuiConfigFlags_NoMouse;
        ImGui::GetIO().ConfigFlags &= mask;
    }


    ImGui::TextColored(headerColor, "Light");
    ImGui::ColorEdit3("Ambient Color", &m_ambientColor[0]);
    ImGui::DragFloat("Ambient Intensity", &m_ambientIntensity, 0.1f, 0, 1);
    ImGui::SliderFloat("Light Pitch", &m_lightPitch, -180, 180);
    ImGui::SliderFloat("Light Yaw", &m_lightYaw, -180, 180);
    ImGui::SliderFloat("Light Pitch Speed", &m_lightPitchSpeed, -180, 180);
    ImGui::SliderFloat("Light Yaw Speed", &m_lightYawSpeed, -180, 180);

    ImGui::TextColored(headerColor, "Camera");
    ImGui::DragFloat3("Cam_Position", &m_camera.Position()[0]);
    ImGui::DragFloat3("Cam_Rotation", &m_camera.Rotation()[0]);

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
