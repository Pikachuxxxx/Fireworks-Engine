#pragma once
#include "perspectivecamera.h"

namespace fireworks { namespace graphics {

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

    class FreeFlyCamera : public PerspectiveCamera
    {
    public:
        float MovementSpeed;
        float MouseSensitivity;
    private:
        float yaw;
        float pitch;
    public:
        FreeFlyCamera(maths::vec3 position, float flySpeed = 3.0f, float lookSensitivity = 0.25f);
        
        // TODO: make this private, update the camera movement using other utility function or via event callbacks
        void processKeyboardMovement(FreeFlyCameraMoveDirection direction, float deltaTime);
        void processMouseMovement(float Xoffset, float Yoffset, bool constrainPitch = true);
    };

} }

