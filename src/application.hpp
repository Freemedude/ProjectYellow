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
    Window m_window {};

    RasterPipeline m_defaultPipeline {};

    Assets m_assets {};
    Inputs m_inputs {};
    Scene m_scene {};

    float m_movespeed = 0.05f;
    float m_mouseSensitivity = 0.05f;

    glm::vec3 m_lightDirection {1, -1, 1};

    Camera m_camera;

public:
    Application();

    ~Application();

    void BeginFrame();

    void Update();

    void RenderGUI();

    void EndFrame();

    bool Done();


private:

    void InitializeImGui();

    void HandleInputs();

    void HandleCameraInputs();
};


#endif //PROJECT_YELLOW_APPLICATION_HPP
