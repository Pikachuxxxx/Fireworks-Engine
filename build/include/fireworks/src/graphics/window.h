#pragma once

// STD. includes
#include <iostream>
#define GL_SILENCE_DEPRECATION
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>

namespace fireworks { namespace graphics {

#define MAX_KEYS     1024
#define MAX_BUTTONS  32


    // Forward declerations of friend functions
    static void glfw_initialisation_error(int error, const char* description);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void window_resize_callback(GLFWwindow* window, int width, int height);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    static void mouse_position_callback(GLFWwindow* window, double xpos, double ypos);

    class Window
    {
    private:
        // FIXME: probably use a custom string class later instead of std::string or char*'s
        const char *m_Title;
        int m_Width, m_Height;
        GLFWwindow *m_Window;
        bool m_Closed; // A boolean to know if the window was closed or not

        bool m_Keys[MAX_KEYS];
        bool m_MouseButtons[MAX_BUTTONS];
        double m_MouseX, m_MouseY;
    public:
        Window(const char *title, int width, int height);
        ~Window();
        void clear() const;
        void update() const;
        bool closed() const;

        inline int getWidth() const { return m_Width; }
        inline int getHeight() const { return m_Height; }
        inline GLFWwindow* getGLFWwindow() const { return m_Window; }

        bool isKeyPressed(unsigned int keycode) const;
        bool isMouseButtonPressed(unsigned int button) const;
        // TODO: Make the function return a Vec2 once the engine specific vector math API is added to the namespace
        void getMousePosition(double& x, double& y) const;
    private :
        bool init();
        friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        friend void window_resize_callback(GLFWwindow* window, int width, int height);
        friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
        friend void mouse_position_callback(GLFWwindow* window, double xpos, double ypos);
    };

} }
