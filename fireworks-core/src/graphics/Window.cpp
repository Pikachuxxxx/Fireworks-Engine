#include "Window.h"

namespace fireworks { namespace graphics {

    Window::Window(const char *title, int width, int height)
    {
        m_Title = title;
        m_Width = width;
        m_Height = height;
        if(!init())
            glfwTerminate();

        for(int i = 0; i < MAX_KEYS ; i++)
        {
            m_Keys[i] = false;
        }
        for(int i = 0; i < MAX_BUTTONS ; i++)
        {
            m_MouseButtons[i] = false;
        }
    }

    Window::~Window()
    {
        glfwTerminate();
    }

    bool Window::init()
    {
        glfwSetErrorCallback(glfw_initialisation_error);
        if(!glfwInit())
            return false;

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
        if(!m_Window)
        {
            glfwTerminate();
            std::cerr << "ERROR::GLFW::Could not initialise GLFW Window" << '\n';
            return false;
        }
        glfwMakeContextCurrent(m_Window);
        glfwSetWindowUserPointer(m_Window, this);

        glfwSetWindowSizeCallback(m_Window, window_resize_callback);
        glfwSetKeyCallback(m_Window, key_callback);
        glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
        glfwSetCursorPosCallback(m_Window, mouse_position_callback);

        glewExperimental = GL_TRUE; // To use modern OpenGL features
        if(glewInit() != GLEW_OK){
            std::cerr << "ERROR::GLEW::Could Not initialise GLEW" << '\n';
            return false;
        }

        return true;
    }

    bool Window::isKeyPressed(unsigned int keycode) const
    {
        // TODO: Log this
        if(keycode >= MAX_KEYS)
            return false;

        return m_Keys[keycode];
    }

    bool Window::isMouseButtonPressed(unsigned int button) const
    {
        // TODO: Log this
        if(button >= MAX_BUTTONS)
            return false;

        return m_MouseButtons[button];
    }

    void Window::getMousePosition(double& x, double& y) const
    {
        x = m_MouseX;
        y = m_MouseY;
    }

    void Window::clear() const
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Window::update() const
    {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }

    bool Window::closed() const
    {
        return glfwWindowShouldClose(m_Window) == 1;
    }

    void glfw_initialisation_error(int error, const char* description)
    {
        std::cerr << "ERROR::GLFW::" << error << "::DESCRIPTION::" << description << std::endl;
    }

    void window_resize_callback(GLFWwindow* window, int widht, int height)
    {
        glViewport(0, 0, widht, height);
    }

    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        Window* wind = (Window *) glfwGetWindowUserPointer(window);
        wind->m_Keys[key] = action != GLFW_RELEASE;

        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        {
            std::cout << "Escape Key Pressed..." << "Quiting..." <<'\n';
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
    }

    void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
    {
        Window* wind = (Window *) glfwGetWindowUserPointer(window);
        wind->m_MouseButtons[button] = action != GLFW_RELEASE;
    }

    void mouse_position_callback(GLFWwindow* window, double xpos, double ypos)
    {
        Window* wind = (Window *) glfwGetWindowUserPointer(window);
        wind->m_MouseX = xpos;
        wind->m_MouseY = ypos;
    }


} }
