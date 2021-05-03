#include "perspectivecamera.h"

namespace fireworks { namespace graphics {

    PerspectiveCamera::PerspectiveCamera(glm::vec3 position /*= glm::vec3(0.0f, 0.0f, 0.0f)*/, glm::vec3 worldUp /*= glm::vec3(0.0f, 1.0f, 0.0f)*/, float aspectRatio /*= 1.0f*/, float fov /*= 45.0f*/)
        : camFront(glm::vec3(0.0f, 0.0f, -1.0f)), nearClipping(0.1f), farClipping(100.0f), FOV(fov), aspectRatio(aspectRatio), yaw(-90.0f), pitch(0.0f)
    {
        this->position = position;
        this->worldUp = worldUp;
        this->updateCameraVectors();
        this->updateViewMatrix();
        this->updateProjectionMatrix();
    }

    PerspectiveCamera::PerspectiveCamera(float posX, float posY, float posZ, float upX, float upY, float upZ)
        : camFront(glm::vec3(0.0f, 0.0f, -1.0f)), yaw(-90.0f), pitch(0.0f)
    {
        position = glm::vec3(posX, posY, posZ);
        worldUp = glm::vec3(upX, upY, upZ);
        updateCameraVectors();
        updateViewMatrix();
        updateProjectionMatrix();
    }

    void PerspectiveCamera::updateCameraVectors()
    {
	    // Updating the camFront vector based on mouse input (Converting to Cartesian screen space coordinates from Polar world space coordinates)
		glm::vec3 front;
		front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
		front.y = sin(glm::radians(this->pitch));
		front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
		this->camFront = glm::normalize(front);
		// Also re-calculate the Right and Up vector
		camRight = glm::normalize(glm::cross(camFront, worldUp));
		camUp = glm::normalize(glm::cross(camRight, camFront));

        updateViewMatrix();
    }

    void PerspectiveCamera::updateViewMatrix()
    {
        m_ViewMatrix = glm::lookAt(position, position + camFront, camUp);
    }

    void PerspectiveCamera::updateProjectionMatrix()
    {   
        m_ProjectionsMatrix = glm::perspective(FOV, aspectRatio, nearClipping, farClipping);
    }
} }