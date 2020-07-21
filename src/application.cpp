//
// @author freemedude
// @date 2020-07-18
// @brief 
//

#include "application.hpp"

#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

Application::Application()
{
    m_window.Init("Project Yellow", 1280, 720, &m_inputs);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glDepthRange(-1, 1);

    InitializeImGui();
    m_assets.Init("assets");

    m_inputs.invalidLastCursor = true;

    m_scene.TestScene();

    glm::ivec2 frameBufferSize = m_window.FrameBufferSize();
    float aspectRatio = (float) frameBufferSize.x / (float) frameBufferSize.y;
    float fov = glm::radians(45.0f);
    m_camera.InitPerspective(fov, aspectRatio, 0.1f, 100.0f);
    m_camera.Transform().position = {0, 0, 10};
    m_camera.Transform().rotation = {0, 0, 0};
}

Application::~Application()
{
    glfwTerminate();
}

bool Application::Done()
{
    return m_window.ShouldClose();
}


void Application::Update()
{
    HandleInputs();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();


    RenderScene();

    RenderGui();
    m_window.SwapBuffers();
}

void Application::RenderGui()
{
    ImVec4 headerColor = {1, 0, 0, 1};

    ImGui::Begin("Hello, world!");
    float frameRate = ImGui::GetIO().Framerate;
    ImGui::Text(
        "Application average %.3f ms/frame (%.1f FPS)",
        1000.0f /
        frameRate, frameRate);

    ImGui::Checkbox("Cursor disabled", &m_inputs.cursorLocked);
    if (m_inputs.cursorLocked)
    {
        ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NoMouse;
    } else
    {
        uint mask = ~ImGuiConfigFlags_NoMouse;
        ImGui::GetIO().ConfigFlags &= mask;
    }


    ImGui::TextColored(headerColor, "Light");
    ImGui::DragFloat3("Light Direction", &m_lightDirection[0], 0.25f, -1, 1);

    ImGui::TextColored(headerColor, "Camera");
    ImGui::DragFloat3("Cam_Position", &m_camera.Transform().position[0]);
    ImGui::DragFloat3("Cam_Rotation", &m_camera.Transform().rotation[0]);

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Application::InitializeImGui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;
    const char *glsl_version = "#version 450";
    io.ConfigFlags |= ImGuiConfigFlags_NoMouse;
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(m_window.GlfwWindow(), true);
    ImGui_ImplOpenGL3_Init(glsl_version);
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
    // Camera Controls
    if (m_inputs.forward)
    {
        m_camera.AddLocal({0, 0, m_movespeed});
    }

    if (m_inputs.back)
    {
        m_camera.AddLocal({0, 0, -m_movespeed});
    }

    if (m_inputs.left)
    {
        m_camera.AddLocal({-m_movespeed, 0, 0});
    }

    if (m_inputs.right)
    {
        m_camera.AddLocal({m_movespeed, 0, 0});
    }

    if (m_inputs.up)
    {
        m_camera.Transform().position.y += m_movespeed;
    }

    if (m_inputs.down)
    {
        m_camera.Transform().position.y -= m_movespeed;
    }

    // Rotation
    {
        glm::vec2 delta = m_inputs.mousePos - m_inputs.lastMousePos;
        delta.y = -delta.y;
        delta *= m_mouseSensitivity;

        glm::vec2 newRot = delta.yx + m_camera.Transform().rotation.xy;

        // Avoid gimbal lock
        newRot.x = glm::clamp(newRot.x, -89.0f, 89.0f);

        m_camera.Transform().rotation.xy = newRot;

        m_inputs.lastMousePos = m_inputs.mousePos;
        m_inputs.invalidLastCursor = false;
    }
}

void Application::RenderScene()
{
    glm::mat4 lightMatrix = glm::lookAt({0, 0, 0}, m_lightDirection, {0, 1, 0});
    glm::vec3 lightDir = lightMatrix * glm::vec4{0, 0, -1, 0};

    for (auto model : m_scene.Models())
    {
        glm::mat4 modelMatrix = model->GetTransform().Matrix();

        glm::mat4 matrix =
            m_camera.ViewProjectionMatrix() *
            modelMatrix;

        auto mat = model->GetMaterial();
        auto pipeline = mat->Pipeline();

        pipeline->Use();

        pipeline->SetMatrix4("u_matrix", matrix);
        pipeline->SetVector4("u_color", mat->Color());
        pipeline->SetVector3("u_lightDirection", lightDir);


        auto mesh = model->GetMesh();
        mesh->Bind();

        glDrawElements(GL_TRIANGLES, mesh->Count(), GL_UNSIGNED_INT, nullptr);
    }

}

