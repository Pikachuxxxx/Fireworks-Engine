#include "freeflycamera.h"

namespace fireworks { namespace graphics {

    FreeFlyCamera::FreeFlyCamera(maths::vec3 position, float flySpeed /*= 3.0f*/, float lookSensitivity /*= 0.25f*/)
        : PerspectiveCamera(position), MovementSpeed(flySpeed), MouseSensitivity(lookSensitivity)
    {

    }

	void FreeFlyCamera::update(Window* window, float deltaTime)
	{
        // Move the camera using the keyboard in the world space
		if (window->isKeyHeld(Keys::Q))
			this->processKeyboardMovement(FFCamDirection::UP, deltaTime);
		else if (window->isKeyHeld(Keys::E))
			this->processKeyboardMovement(FFCamDirection::DOWN, deltaTime);

		if (window->isKeyHeld(Keys::W) || window->isKeyHeld(Keys::UP))
			this->processKeyboardMovement(FFCamDirection::FORWARD, deltaTime);
		else if (window->isKeyHeld(Keys::S) || window->isKeyHeld(Keys::DOWN))
			this->processKeyboardMovement(FFCamDirection::BACKWARD, deltaTime);

		if (window->isKeyHeld(Keys::A) || window->isKeyHeld(Keys::RIGHT))
			this->processKeyboardMovement(FFCamDirection::RIGHT, deltaTime);
		else if (window->isKeyHeld(Keys::D) || window->isKeyHeld(Keys::LEFT))
			this->processKeyboardMovement(FFCamDirection::LEFT, deltaTime);

        if (window->isMouseButtonHeld(Keys::MOUSE_BUTTON_RIGHT))
        {
			this->processMouseMovement(-window->deltaMouseX, -window->deltaMouseY);
            window->deltaMouseX = 0.0f;
            window->deltaMouseY = 0.0f;
        }
	}

	void FreeFlyCamera::processKeyboardMovement(FFCamDirection direction, float deltaTime)
    {
        float velocity = this->MovementSpeed * deltaTime;

        if (direction == FFCamDirection::FORWARD)
            this->position -= this->camFront * velocity;
        if (direction == FFCamDirection::BACKWARD)
            this->position += this->camFront* velocity;

        if (direction == FFCamDirection::LEFT)
            this->position -= this->camRight * velocity;
        if (direction == FFCamDirection::RIGHT)
            this->position += this->camRight * velocity;

        if (direction == FFCamDirection::UP)
            this->position += this->camUp * velocity;
        if (direction == FFCamDirection::DOWN)
            this->position -= this->camUp * velocity;
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

		// Update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors();
    }
} }
