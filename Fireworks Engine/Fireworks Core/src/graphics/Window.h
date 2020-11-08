#pragma once

// STD. includes
#include <iostream>
#define GL_SILENCE_DEPRECATION
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>
#include "../maths/maths.h"

namespace fireworks { namespace graphics {

#define MAX_KEYS     1024
#define MAX_BUTTONS  32

	/// All Input Buttons mapped to a more understandable mappinng from GLFW
    enum Keys
    {
		UNKNOWN = GLFW_KEY_UNKNOWN,
		SPACE = GLFW_KEY_SPACE,
		APOSTROPHE = GLFW_KEY_APOSTROPHE,
		COMMA = GLFW_KEY_COMMA,
		MINUS = GLFW_KEY_MINUS,
		PERIOD = GLFW_KEY_PERIOD,
		SLASH = GLFW_KEY_SLASH,
		NUM0 = GLFW_KEY_0,
		NUM1 = GLFW_KEY_1,
		NUM2 = GLFW_KEY_2,
		NUM3 = GLFW_KEY_3,
		NUM4 = GLFW_KEY_4,
		NUM5 = GLFW_KEY_5,
		NUM6 = GLFW_KEY_6,
		NUM7 = GLFW_KEY_7,
		NUM8 = GLFW_KEY_8,
		NUM9 = GLFW_KEY_9,
		SEMICOLON = GLFW_KEY_SEMICOLON,
		EQUAL = GLFW_KEY_EQUAL,
		A = GLFW_KEY_A,
		B = GLFW_KEY_B,
		C = GLFW_KEY_C,
		D = GLFW_KEY_D,
		E = GLFW_KEY_E,
		F = GLFW_KEY_F,
		G = GLFW_KEY_G,
		H = GLFW_KEY_H,
		I = GLFW_KEY_I,
		J = GLFW_KEY_J,
		K = GLFW_KEY_K,
		L = GLFW_KEY_L,
		M = GLFW_KEY_M,
		N = GLFW_KEY_N,
		O = GLFW_KEY_O,
		P = GLFW_KEY_P,
		Q = GLFW_KEY_Q,
		R = GLFW_KEY_R,
		S = GLFW_KEY_S,
		T = GLFW_KEY_T,
		U = GLFW_KEY_U,
		V = GLFW_KEY_V,
		W = GLFW_KEY_W,
		X = GLFW_KEY_X,
		Y = GLFW_KEY_Y,
		Z = GLFW_KEY_Z,
		LEFT_BRACKET = GLFW_KEY_LEFT_BRACKET,
		BACKSLASH = GLFW_KEY_BACKSLASH,
		RIGHT_BRACKET = GLFW_KEY_RIGHT_BRACKET,
		GRAVE_ACCENT = GLFW_KEY_GRAVE_ACCENT,
		WORLD_1 = GLFW_KEY_WORLD_1,
		WORLD_2 = GLFW_KEY_WORLD_2,
		ESCAPE = GLFW_KEY_ESCAPE,
		ENTER = GLFW_KEY_ENTER,
		TAB = GLFW_KEY_TAB,
		BACKSPACE = GLFW_KEY_BACKSPACE,
		INSERT = GLFW_KEY_INSERT,
		DELETE = GLFW_KEY_DELETE,
		RIGHT = GLFW_KEY_RIGHT,
		LEFT = GLFW_KEY_LEFT,
		DOWN = GLFW_KEY_DOWN,
		UP = GLFW_KEY_UP,
		PAGE_UP = GLFW_KEY_PAGE_UP,
		PAGE_DOWN = GLFW_KEY_PAGE_DOWN,
		HOME = GLFW_KEY_HOME,
		END = GLFW_KEY_END,
		CAPS_LOCK = GLFW_KEY_CAPS_LOCK,
		SCROLL_LOCK = GLFW_KEY_SCROLL_LOCK,
		NUM_LOCK = GLFW_KEY_NUM_LOCK,
		PRINT_SCREEN = GLFW_KEY_PRINT_SCREEN,
		PAUSE = GLFW_KEY_PAUSE,
		F1 = GLFW_KEY_F1,
		F2 = GLFW_KEY_F2,
		F3 = GLFW_KEY_F3,
		F4 = GLFW_KEY_F4,
		F5 = GLFW_KEY_F5,
		F6 = GLFW_KEY_F6,
		F7 = GLFW_KEY_F7,
		F8 = GLFW_KEY_F8,
		F9 = GLFW_KEY_F9,
		F10 = GLFW_KEY_F10,
		F11 = GLFW_KEY_F11,
		F12 = GLFW_KEY_F12,
		F13 = GLFW_KEY_F13,
		F14 = GLFW_KEY_F14,
		F15 = GLFW_KEY_F15,
		F16 = GLFW_KEY_F16,
		F17 = GLFW_KEY_F17,
		F18 = GLFW_KEY_F18,
		F19 = GLFW_KEY_F19,
		F20 = GLFW_KEY_F20,
		F21 = GLFW_KEY_F21,
		F22 = GLFW_KEY_F22,
		F23 = GLFW_KEY_F23,
		F24 = GLFW_KEY_F24,
		F25 = GLFW_KEY_F25,
		KP_0 = GLFW_KEY_KP_0,
		KP_1 = GLFW_KEY_KP_1,
		KP_2 = GLFW_KEY_KP_2,
		KP_3 = GLFW_KEY_KP_3,
		KP_4 = GLFW_KEY_KP_4,
		KP_5 = GLFW_KEY_KP_5,
		KP_6 = GLFW_KEY_KP_6,
		KP_7 = GLFW_KEY_KP_7,
		KP_8 = GLFW_KEY_KP_8,
		KP_9 = GLFW_KEY_KP_9,
		KP_DECIMAL = GLFW_KEY_KP_DECIMAL,
		KP_DIVIDE = GLFW_KEY_KP_DIVIDE,
		KP_MULTIPLY = GLFW_KEY_KP_MULTIPLY,
		KP_SUBTRACT = GLFW_KEY_KP_SUBTRACT,
		KP_ADD = GLFW_KEY_KP_ADD,
		KP_ENTER = GLFW_KEY_KP_ENTER,
		KP_EQUAL = GLFW_KEY_KP_EQUAL,
		LEFT_SHIFT = GLFW_KEY_LEFT_SHIFT,
		LEFT_CONTROL = GLFW_KEY_LEFT_CONTROL,
		LEFT_ALT = GLFW_KEY_LEFT_ALT,
		LEFT_SUPER = GLFW_KEY_LEFT_SUPER,
		RIGHT_SHIFT = GLFW_KEY_RIGHT_SHIFT,
		RIGHT_CONTROL = GLFW_KEY_RIGHT_CONTROL,
		RIGHT_ALT = GLFW_KEY_RIGHT_ALT,
		RIGHT_SUPER = GLFW_KEY_RIGHT_SUPER,
		MENU = GLFW_KEY_MENU,
		MOUSE_BUTTON_1 = GLFW_MOUSE_BUTTON_1,
		MOUSE_BUTTON_2 = GLFW_MOUSE_BUTTON_2,
		MOUSE_BUTTON_3 = GLFW_MOUSE_BUTTON_3,
		MOUSE_BUTTON_4 = GLFW_MOUSE_BUTTON_4,
		MOUSE_BUTTON_5 = GLFW_MOUSE_BUTTON_5,
		MOUSE_BUTTON_6 = GLFW_MOUSE_BUTTON_6,
		MOUSE_BUTTON_7 = GLFW_MOUSE_BUTTON_7,
		MOUSE_BUTTON_8 = GLFW_MOUSE_BUTTON_8,
		MOUSE_BUTTON_LAST = GLFW_MOUSE_BUTTON_LAST,
		MOUSE_BUTTON_LEFT = GLFW_MOUSE_BUTTON_LEFT,
		MOUSE_BUTTON_RIGHT = GLFW_MOUSE_BUTTON_RIGHT,
		MOUSE_BUTTON_MIDDLE = GLFW_MOUSE_BUTTON_MIDDLE
    };

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
    public:
        /// The background color of the Window.
        /// 
        /// @note This sets the color in the GL_COLOR_BUFFER_BIT
        maths::vec4 backgroundColor;
    private:
        // FIXME: probably use a custom string class later instead of std::string or char*(character pointer)'s
        const char *m_Title;
        int m_Width, m_Height;
        GLFWwindow *m_Window;
        bool m_Closed;

        bool m_HeldKeys[MAX_KEYS];
		bool m_PressedKeys[MAX_KEYS];
		bool m_ReleasedKeys[MAX_KEYS];
        bool m_HeldMouseButtons[MAX_BUTTONS];
		bool m_PressedMouseButtons[MAX_BUTTONS];
		bool m_ReleasedMouseButtons[MAX_BUTTONS];
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
        /// @param keycode The GLFW enum key code of the key to check it's status
		/// @returns A bool indicating whether the key was pressed or not
        bool isKeyPressed(unsigned int keycode);

		/// Tells if a particular key on the keyboard was released or not.
		/// 
		/// @param keycode The GLFW enum key code of the key to check it's status
		/// @returns A bool indicating whether the key was released after being pressed or not
		bool isKeyReleased(unsigned int keycode);

		/// Tells if a particular key on the keyboard is being held or not.
        /// 
		/// @note returns true for the entire duration of the key press
        /// @param keycode The GLFW enum key code of the key to check it's status
        /// @returns A bool indicating whether the key was being held or not
		bool isKeyHeld(unsigned int keycode) const;

		/// Tells if a particular key on the Mouse button was pressed or not.
		/// 
		/// @param keycode The GLFW enum button code of the key to check it's status
		/// @returns A bool indicating whether the button was pressed or not
        bool isMouseButtonPressed(unsigned int button);

		// TODO: To be implemented
		bool isMouseButtonReleased(unsigned int button);

		/// Tells if a particular key on the Mouse button is being held or not.
		/// 
		/// @note returns true for the entire duration of the button press
		/// @param keycode The GLFW enum button code of the key to check it's status
		/// @returns A bool indicating whether the button was being held or not
		bool isMouseButtonHeld(unsigned int button) const;

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
