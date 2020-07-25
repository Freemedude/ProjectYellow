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

class Application
{
private:
    Window m_window{};

    Assets m_assets{};
    Inputs m_inputs{};
    Scene m_scene{};

    float m_moveSpeed = 10.0f;
    float m_mouseSensitivity = 0.05f;

    glm::vec3 m_ambientColor{0.9f, 0.9f, 0.1f};
    float m_ambientIntensity = 0.1f;

    float m_lightPitch = 0;
    float m_lightYaw = 0;

    float m_lightYawSpeed = 30.0f;
    float m_lightPitchSpeed = 10.0f;

    float m_deltaTime = 0;
    double m_frameStart = 0;
    double m_frameEnd = 0;

    Camera m_camera{};


public:
    Application() = default;

    ~Application();

    void Init();

    void StartFrame();

    void Update();

    void EndFrame();

    void RenderGui();

    bool Done();

private:


    void InitOpenGL();

    void InitDearImGui();

    void HandleInputs();

    void HandleCameraInputs();

    void RenderScene();

    float ClampDegrees(float deg);
};


#endif //PROJECT_YELLOW_APPLICATION_HPP
