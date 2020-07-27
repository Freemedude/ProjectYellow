//
// @author freemedude
// @date 2020-07-19
// @brief 
//

#include "window.hpp"

#include <iostream>
#include <string>

#include <glad/glad.h>

#include "utility.hpp"
#include "application.hpp"

void GLAPIENTRY OpengGLMessageCB(
    GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar *message,
    const void *userParam);

Window::~Window()
{
    glfwTerminate();
}

void Window::Init(const std::string &name, int width, int height, Application *app)
{
    glfwSetErrorCallback(GlfwCb_Error);

    if (!glfwInit())
    {
        throw std::runtime_error("Failed to initialize GLFW");
    }
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    m_window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);

    if (!m_window)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to created GLFW window");
    }

    SetGLFWCallbacks();
    glfwSetWindowUserPointer(m_window, app);
    glfwMakeContextCurrent(m_window);

    gladLoadGL();

    // During init, enable debug output
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(OpengGLMessageCB, nullptr);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthRange(-1, 1);
    glDepthFunc(GL_LESS);
}

void Window::GlfwCb_Error(int error, const char *description)
{
    std::cerr << "--- GLFW ERROR ---" << std::endl;
    std::cerr << "  Error: " << error << std::endl;
    std::cerr << "  Description: " << description << std::endl;
}

bool Window::ShouldClose() const
{
    return glfwWindowShouldClose(m_window);
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(m_window);
}

glm::ivec2 Window::FrameBufferSize()
{
    int width;
    int height;

    glfwGetFramebufferSize(m_window, &width, &height);

    return {width, height};
}

float Window::AspectRatio()
{
    glm::ivec2 size =  FrameBufferSize();
    return (float)size.x / (float)size.y;
}

GLFWwindow *Window::GlfwWindow()
{
    return m_window;
}

void Window::GetInputs()
{
    glfwPollEvents();
}

void Window::Close()
{
    glfwSetWindowShouldClose(m_window, true);
}

void Window::CursorLocked(bool locked)
{
    glfwSetInputMode(
        m_window,
        GLFW_CURSOR,
        locked ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}

void Window::KeyCB(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    auto changeIfNotRepeat = [](bool &value, int action)
    {
        if(action == GLFW_PRESS)
        {
            value = true;
        }
        else if (action == GLFW_RELEASE)
        {
            value = false;
        }
    };
    UNUSED(scancode);

    Inputs &inputs = ApplicationFromUserPointer(window)->GetInputs();

    bool shiftPressed = (mods & GLFW_MOD_SHIFT) != 0;

    inputs.moveSlow = shiftPressed;

    switch (key)
    {
        case GLFW_KEY_ESCAPE:
            inputs.quit = true;
            break;
        case GLFW_KEY_F1:
            if (action == GLFW_RELEASE)
            {
                inputs.cursorLocked = !inputs.cursorLocked;
            }
            break;
        case GLFW_KEY_W:
            changeIfNotRepeat(inputs.forward, action);
            break;
        case GLFW_KEY_A:
            changeIfNotRepeat(inputs.left, action);
            break;
        case GLFW_KEY_S:
            changeIfNotRepeat(inputs.back, action);
            break;
        case GLFW_KEY_D:
            changeIfNotRepeat(inputs.right, action);
            break;
        case GLFW_KEY_R:
            changeIfNotRepeat(inputs.up, action);
            break;
        case GLFW_KEY_F:
            changeIfNotRepeat(inputs.down, action);
            break;
        default:
            break;
    }
}

void Window::CursorMoveCB(GLFWwindow *window, double xpos, double ypos)
{
    Inputs &inputs = ApplicationFromUserPointer(window)->GetInputs();
    inputs.mousePos = {xpos, ypos};

    if(inputs.invalidLastCursor)
    {
        inputs.lastMousePos = inputs.mousePos;
    }
}

Application *Window::ApplicationFromUserPointer(GLFWwindow *window)
{
    void *userPointer = glfwGetWindowUserPointer(window);
    Application *app = (Application *) userPointer;
    return app;
}

void Window::SetGLFWCallbacks()
{
    glfwSetKeyCallback(m_window, KeyCB);
    glfwSetCursorPosCallback(m_window, CursorMoveCB);
    glfwSetFramebufferSizeCallback(m_window, ResizeCB);
}

void Window::ResizeCB(GLFWwindow *window, int width, int height)
{
    Application *app = ApplicationFromUserPointer(window);
    app->Resize(width, height);
}

void GLAPIENTRY OpengGLMessageCB(
    GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar *message,
    const void *userParam)
{
    UNUSED(source);
    UNUSED(length);
    UNUSED(userParam);

    // ignore non-significant error/warning codes
    if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;
    std::string typeBanner = type == GL_DEBUG_TYPE_ERROR ? "ERROR" : "";
    std::cerr << "--- OpenGL Callback " << typeBanner << " ---" << std::endl;
    std::cerr << "  Type: " << type << std::endl;
    std::cerr << "  Severity: " << severity << std::endl;
    std::cerr << "  Message: " << message << std::endl;
}