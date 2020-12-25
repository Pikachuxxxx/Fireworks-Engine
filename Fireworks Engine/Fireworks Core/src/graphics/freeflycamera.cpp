#include "freeflycamera.h"

namespace fireworks { namespace graphics {

    FreeFlyCamera::FreeFlyCamera(maths::vec3 position, float flySpeed /*= 3.0f*/, float lookSensitivity /*= 0.25f*/)
        : PerspectiveCamera(position), MovementSpeed(flySpeed), MouseSensitivity(lookSensitivity), yaw(-90.0f), pitch(0.0f)
    {

    }

    void FreeFlyCamera::processKeyboardMovement(FreeFlyCameraMoveDirection direction, float deltaTime)
    {
        float velocity = this->MovementSpeed * deltaTime;

        if (direction == FreeFlyCameraMoveDirection::FORWARD)
            this->position -= this->camFront * velocity;
        if (direction == FreeFlyCameraMoveDirection::BACKWARD)
            this->position += this->camFront* velocity;

        if (direction == FreeFlyCameraMoveDirection::LEFT)
            this->position -= this->camRight * velocity;
        if (direction == FreeFlyCameraMoveDirection::RIGHT)
            this->position += this->camRight * velocity;

        if (direction == FreeFlyCameraMoveDirection::UP)
            this->position += this->camUp * velocity;
        if (direction == FreeFlyCameraMoveDirection::DOWN)
            this->position -= this->camUp * velocity;

        if (direction == FreeFlyCameraMoveDirection::YAW_LEFT)
            processMouseMovement(-1.0f, 0.0f);
        if(direction == FreeFlyCameraMoveDirection::YAW_RIGHT)
            processMouseMovement(1.0f, 0.0f);

        updateCameraVectors();
    }

    // TODO: Fix this
    void FreeFlyCamera::processMouseMovement(float Xoffset, float Yoffset, bool constrainPitch /*= true*/)
    {
        Xoffset *= this->MouseSensitivity;
        Yoffset *= this->MouseSensitivity;

        this->yaw += Xoffset;
        this->pitch += Yoffset;

        // Make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (this->pitch > 89.0f)
                this->pitch = 89.0f;
            if (this->pitch < -89.0f)
                this->pitch = -89.0f;
        }

        // Updating the camFront vector based on mouse input (Converting to Cartesian screen space coordinates from Polar world space coordinates)
        maths::vec3 front;
        front.x = cos(maths::toRadians(this->yaw)) * cos(maths::toRadians(this->pitch));
        front.y = sin(maths::toRadians(this->pitch));
        front.z = sin(maths::toRadians(this->yaw)) * cos(maths::toRadians(this->pitch));
        this->camFront = maths::vec3::normalize(front);
        updateCameraVectors();
    }

} }
