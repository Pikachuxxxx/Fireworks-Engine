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


    // Forward decelerations of friend functions
    /// Input related GLFW callback functions
    static void glfw_initialisation_error(int error, const char* description);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void window_resize_callback(GLFWwindow* window, int width, int height);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    static void mouse_position_callback(GLFWwindow* window, double xpos, double ypos);

    /// The class responsible for Window Creation.
    /// 
    /// Use this to create a new winnow of type GLFWwindow and manage input from the user and set various properties of the window
    class Window
    {
    private:
        // FIXME: probably use a custom string class later instead of std::string or char*(character pointer)'s
        const char *m_Title;
        int m_Width, m_Height;
        GLFWwindow *m_Window;
        bool m_Closed;

        bool m_Keys[MAX_KEYS];
        bool m_MouseButtons[MAX_BUTTONS];
        double m_MouseX, m_MouseY;
    public:
        /// Creates a Window by initializing GLFW.
		/// @param title The title of the window
		/// @param width The width of the window
		/// @param height The height of the window
        Window(const char *title, int width, int height);
        ~Window();
        /// Clears the window screen blank.
        /// 
        /// Uses the data from the color, depth and stencil buffer bits to clear the window according the clearing rules
        void clear() const;
		/// Updates the window.
		/// 
		/// Checks for OpenGL errors and swaps the buffers after poling for input events
        void update() const;
        /// Indicates the current state of the Window.
        /// @returns A bool indicating whether the window is closed or not
        bool closed() const;

        /// Gets the current width of the window.
        /// @returns An int denoting the current width of the graphics::Window
        inline int getWidth() const { return m_Width; }
		/// Gets the current height of the window.
		/// @returns An int denoting the current height of the graphics::Window
        inline int getHeight() const { return m_Height; }
		/// Gets the current window's pointer to it's native object.
	    /// @returns A a pointer variable to the windows GLFWwindow object
        inline GLFWwindow* getGLFWwindow() const { return m_Window; }

		/// Tells if a particular key on the keyboard was pressed or not.
        /// 
        /// @note returns true for the entire duration of the key press
        /// @param keycode The GLFW enum key code of the key to check it's status
		/// @returns A bool indicating whether the key was pressed or not
        bool isKeyPressed(unsigned int keycode) const;
		/// Tells if a particular key on the Mouse button was pressed or not.
		/// 
		/// @note returns true for the entire duration of the button press
		/// @param keycode The GLFW enum button code of the key to check it's status
		/// @returns A bool indicating whether the button was pressed or not
        bool isMouseButtonPressed(unsigned int button) const;
        // TODO: Make the function return a Vec2 once the engine specific vector math API is added to the namespace
        /// Gets the current position of the mouse in Screen Space Coordinates.
        ///  
        /// @param x A variable to the store the X coordinate of the mouse position
        /// @param y A variable to the store the Y coordinate of the mouse position
        void getMousePosition(double& x, double& y) const;
    private :
        bool init();
        // TODO: Add reference to the GLFW keycode Enums list for the key parameter and also for the mods param(add the reference to the bit fields)
		/// A callback function called when the windows registers a key press from the Keyboard.
		/// 
		/// 
		/// @param window The window that received the event
		/// @param key The keyboard key that was pressed or released
		/// @param scancode The system-specific scancode of the key
		/// @param action GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT
		/// @param mods Bit field describing which modifier keys were held down
        friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		/// A callback function called when the windows resizes
		/// 
		/// 
		/// @param window The window that received the event
		/// @param width The new width of the window
        /// @param height The new height of the window
        friend void window_resize_callback(GLFWwindow* window, int width, int height);
		// TODO: Add reference to the GLFW mouse_button Enums list for the button parameter and also for the mods param(add the reference to the bit fields)
		/// A callback function called when the windows registers a button press from the Mouse.
        /// 
        /// 
        /// @param window The window that received the event
        /// @param button The mouse button that was pressed or released
        /// @param action GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT
        /// @param mods Bit field describing which modifier keys were held down
        friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		///  A callback function called when the windows registers a change in the mouse position.
	    ///  
        /// @param window The window that received the event
	    /// @param xpos The new cursor x-coordinate, relative to the left edge of the content area
	    /// @param ypos The new cursor y-coordinate, relative to the top edge of the content area
        friend void mouse_position_callback(GLFWwindow* window, double xpos, double ypos);
    };

} }
