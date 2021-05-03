#pragma once
#include "perspectivecamera.h"
#include "Window.h"

namespace fireworks { namespace graphics {

    /// The direction of the free fly camera
    enum class FFCamDirection
    {
        FORWARD, 
        BACKWARD, 
        LEFT, 
        RIGHT,
        UP, 
        DOWN,
        YAW_LEFT, 
        YAW_RIGHT
    };

    /// A free flying 3D camera.
    class FreeFlyCamera : public PerspectiveCamera
    {
    public:
        /// The movement speed of the camera
        float MovementSpeed;
        /// The look speed of the camera
        float MouseSensitivity;
    private:
        bool firstMouse = true;
        float lastX = 400;
        float lastY = 300;
		double xpos;
		double ypos;
    public:
        /// Creates a 3D camera.
        ///
        /// @param position The starting position of the camera in 3d space
        /// @param flySpeed The movement speed of the camera
        /// @param lookSensitivity The look speed of the camera
        FreeFlyCamera(glm::vec3 position, float flySpeed = 30.0f, float lookSensitivity = 0.25f);

        void update(Window* window, float deltaTime);
    private:
        void processKeyboardMovement(FFCamDirection direction, float deltaTime);
        void processMouseMovement(float Xoffset, float Yoffset, bool constrainPitch = true);
    };

} }

