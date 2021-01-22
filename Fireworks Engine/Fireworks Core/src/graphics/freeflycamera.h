#pragma once
#include "perspectivecamera.h"

namespace fireworks { namespace graphics {

    /// The direction of the freefly camera
    enum class FreeFlyCameraMoveDirection
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
        float yaw;
        float pitch;
    public:
        /// Creates a 3D camera.
        ///
        /// @param position The starting position of the camera in 3d space
        /// @param flySpeed The movement speed of the camera
        /// @param lookSensitivity The look speed of the camera
        FreeFlyCamera(maths::vec3 position, float flySpeed = 3.0f, float lookSensitivity = 0.25f);
        
        // TODO: make this private, update the camera movement using other utility function or via event callbacks
        void processKeyboardMovement(FreeFlyCameraMoveDirection direction, float deltaTime);
        void processMouseMovement(float Xoffset, float Yoffset, bool constrainPitch = true);
    };

} }

