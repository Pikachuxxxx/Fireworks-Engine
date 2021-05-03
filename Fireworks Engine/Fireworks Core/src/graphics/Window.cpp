#include "window.h"

namespace fireworks { namespace graphics {

    Window::Window(const char *title, int width, int height) : backgroundColor(glm::vec4(0, 0, 0, 1))
    {
        m_Title = title;
        m_Width = width;
        m_Height = height;
        if(!init())
            glfwTerminate();

        for(int i = 0; i < MAX_KEYS ; i++)
        {
            m_HeldKeys[i] = false;
			m_PressedKeys[i] = false;
			m_ReleasedKeys[i] = false;
        }
        for(int i = 0; i < MAX_BUTTONS ; i++)
        {
            m_HeldMouseButtons[i] = false;
        }

		firstMouse = true;
		lastMouseX = width / 2;
		lastMouseY = height / 2;
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

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
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

        // Window Callback Functions 
        glfwSetFramebufferSizeCallback(m_Window, window_resize_callback);
        glfwSetKeyCallback(m_Window, key_callback);
        glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
        glfwSetCursorPosCallback(m_Window, mouse_position_callback);

        glewExperimental = GL_TRUE; // To use modern OpenGL features
        if(glewInit() != GLEW_OK){
            std::cerr << "ERROR::GLEW::Could Not initialise GLEW" << '\n';
            return false;
        }

        GLCall(glEnable(GL_BLEND));
        GLCall(glEnable(GL_DEPTH_TEST));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        return true;
    }

    bool Window::isKeyPressed(unsigned int keycode)
    {
		if (keycode >= MAX_KEYS)
			return false;

        bool result = m_PressedKeys[keycode];
        m_PressedKeys[keycode] = false;

        return result;
    }

	bool Window::isKeyReleased(unsigned int keycode)
	{
		if (keycode >= MAX_KEYS)
			return false;

		bool result = m_ReleasedKeys[keycode];
        m_ReleasedKeys[keycode] = false;

        return result;
	}

	bool Window::isKeyHeld(unsigned int keycode) const
	{
		// TODO: Log this
		if (keycode >= MAX_KEYS)
			return false;

		return m_HeldKeys[keycode];
	}

	bool Window::isMouseButtonPressed(unsigned int button)
    {
		if (button >= MAX_BUTTONS)
			return false;

		bool result = m_PressedMouseButtons[button];
        m_PressedMouseButtons[button] = false;

		return result;
    }

	bool Window::isMouseButtonReleased(unsigned int button)
	{
		if (button >= MAX_BUTTONS)
			return false;

		bool result = m_ReleasedMouseButtons[button];
        m_ReleasedMouseButtons[button] = false;

		return result;
	}

	bool Window::isMouseButtonHeld(unsigned int button) const
	{
		// TODO: Log this
		if (button >= MAX_BUTTONS)
			return false;

		return m_HeldMouseButtons[button];
	}

	void Window::getMousePosition(double& x, double& y) const
    {
        x = m_MouseX;
        y = m_MouseY;
    }

    void Window::clear() const
    {
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
        GLCall(glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, backgroundColor.w));
    }

    void Window::update() const
    {
        // Replaced with GLCall assert macro
        /*   GLenum error = glGetError();
           if(error != GL_NO_ERROR)
           {
               std::cout << "ERROR::OpenGL::" << error << std::endl;
           }*/
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

    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        Window* wind = (Window *) glfwGetWindowUserPointer(window);
		wind->m_ReleasedKeys[key] = ((action == GLFW_RELEASE) && wind->m_HeldKeys[key]);
        wind->m_HeldKeys[key] = action != GLFW_RELEASE;
        if(!wind->m_PressedKeys[key])
            wind->m_PressedKeys[key] = (action == GLFW_PRESS);
        
        
        // Window closing
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        {
            std::cout << "Escape Key Pressed..." << "Quiting..." <<'\n';
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
    }

    void window_resize_callback(GLFWwindow* window, int width, int height)
    {
        GLCall(glViewport(0, 0, width, height));
        Window* wind = (Window *) glfwGetWindowUserPointer(window);
        wind->m_Width = width;
        wind->m_Height = height;
    }

    void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
    {
        Window* wind = (Window *) glfwGetWindowUserPointer(window);
		wind->m_ReleasedMouseButtons[button] = ((action == GLFW_RELEASE) && wind->m_ReleasedMouseButtons[button]);
        wind->m_HeldMouseButtons[button] = action != GLFW_RELEASE;
		if (!wind->m_PressedMouseButtons[button])
		    wind->m_PressedMouseButtons[button] = action == GLFW_PRESS;
    }

    void mouse_position_callback(GLFWwindow* window, double xpos, double ypos)
    {
        Window* wind = (Window *) glfwGetWindowUserPointer(window);
        wind->m_MouseX = xpos;
        wind->m_MouseY = ypos;

		if (wind->firstMouse)
		{
			wind->lastMouseX = xpos;
			wind->lastMouseY = ypos;
			wind->firstMouse = false;
		}
		wind->deltaMouseX = xpos - wind->lastMouseX;
		wind->deltaMouseY = wind->lastMouseY - ypos;

		wind->lastMouseX = xpos;
		wind->lastMouseY = ypos;
    }

} }
