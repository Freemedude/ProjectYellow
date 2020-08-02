//
// @author freemedude
// @date 2020-07-18
// @brief 
//

#ifndef PROJECT_YELLOW_APPLICATION_HPP
#define PROJECT_YELLOW_APPLICATION_HPP

#define GLM_FORCE_SWIZZLE

#include <glm/glm.hpp>

#include "mesh.hpp"
#include "raster_pipeline.hpp"
#include "assets.hpp"
#include "gpu_buffer.hpp"
#include "window.hpp"
#include "transform.hpp"
#include "camera.hpp"
#include "scene.hpp"

#include "rapidjson_wrapper.hpp"

struct DebugSettings
{
    std::vector<Shader*> shaderDialogs{};
};

class Application
{
private:
    Window m_window{};
    DebugSettings m_debugSettings{};
    Assets m_assets{};
    Inputs m_inputs{};
    Scene m_scene{};

    // Camera settings
    float m_moveSpeed = 10.0f;
    float m_moveSpeedSlowMultiplier = 0.5f;
    float m_mouseSensitivity = 0.05f;

    float m_fov = 45.0f;
    float m_near = 0.1f;
    float m_far = 1000.0f;

    //// Lighting

    // Ambient
    glm::vec3 m_ambientColor{0.9f, 0.9f, 0.1f};
    float m_ambientIntensity = 0.1f;

    // Directional
    float m_lightPitch = 0;
    float m_lightYaw = 0;

    float m_lightYawSpeed = 30.0f;
    float m_lightPitchSpeed = 10.0f;
    glm::vec3 m_sunColor = {0.9, 0.9, 0};
    float m_specularIntensity = 0.5;
    float m_shininess = 64;

    float m_deltaTime = 0;
    double m_frameStart = 0;
    double m_frameEnd = 0;

    Camera m_camera{};
    rapidjson::Document m_runtimeVariables;
    File m_runtimeFile;

public:
    Application() = default;
    ~Application();

    void Init();

    void LoadRuntimeVariables();

    void SaveRuntimeVariables();

    void StartFrame();

    void Update();

    void EndFrame();

    void RenderGui();

    bool Done();

    Inputs &GetInputs();

    void Resize(int width, int height);

private:

    void InitDearImGui();

    void HandleInputs();

    void HandleCameraInputs();

    void RenderScene();

    static float ClampDegrees(float deg);
};


#endif //PROJECT_YELLOW_APPLICATION_HPP
