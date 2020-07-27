//
// @author freemedude
// @date 2020-07-19
// @brief 
//

#ifndef PROJECT_YELLOW_WINDOW_HPP
#define PROJECT_YELLOW_WINDOW_HPP

#include <string>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "integers.h"
#include "inputs.hpp"

class Application;

class Window
{
private:

    GLFWwindow *m_window;
public:
    Window() = default;

    ~Window();

    void Init(const std::string &name, int width, int height, Application *app);

    bool ShouldClose() const;

    void SwapBuffers();


    glm::ivec2 FrameBufferSize();

    void CursorLocked(bool locked);

    GLFWwindow *GlfwWindow();

    static void GetInputs();

    void Close();

    float AspectRatio();

private:
    void SetGLFWCallbacks();

    // Callbacks
    static Application *ApplicationFromUserPointer(GLFWwindow *window);

    static void GlfwCb_Error(int error, const char *description);

    static void KeyCB(GLFWwindow *window, int key, int scancode, int action, int mods);

    static void CursorMoveCB(GLFWwindow *window, double xpos, double ypos);

    static void ResizeCB(GLFWwindow* window, int width, int height);

};


#endif //PROJECT_YELLOW_WINDOW_HPP
