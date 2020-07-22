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

struct DebugGuiSettings
{
    bool lighting;
    bool camera;
};

class Application
{
private:
    Window m_window{};

    Assets m_assets{};
    Inputs m_inputs{};
    Scene m_scene{};

    float m_movespeed = 0.05f;
    float m_mouseSensitivity = 0.05f;

    float m_lightPitchSpeed = 0;
    float m_lightYawSpeed = 0;

    float m_lightPitch = 0;
    float m_lightYaw = 0;

    glm::vec3 m_ambientColor{0.1, 0.1, 0.2};
    float m_ambientIntensity = 0;

    double m_deltaTime {};
    double m_frameEnd {};

    Camera m_camera {};

public:
    Application();

    ~Application();

    void Update();

    void RenderGui();

    bool Done();

private:


    void InitializeImGui();

    void HandleInputs();

    void HandleCameraInputs();

    void RenderScene();
};


#endif //PROJECT_YELLOW_APPLICATION_HPP
