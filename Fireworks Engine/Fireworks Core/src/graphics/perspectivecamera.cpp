#include "perspectivecamera.h"

namespace fireworks { namespace graphics {

    PerspectiveCamera::PerspectiveCamera(maths::vec3 position /*= maths::vec3(0.0f, 0.0f, 0.0f)*/, maths::vec3 worldUp /*= maths::vec3(0.0f, 1.0f, 0.0f)*/, float aspectRatio /*= 1.0f*/, float fov /*= 45.0f*/)
        : camFront(maths::vec3(0.0f, 0.0f, -1.0f)), nearClipping(0.1f), farClipping(100.0f), FOV(fov), aspectRatio(aspectRatio)
    {
        this->position = position;
        this->worldUp = worldUp;
        this->updateCameraVectors();
        this->updateViewMatrix();
        this->updateProjectionMatrix();
    }

    PerspectiveCamera::PerspectiveCamera(float posX, float posY, float posZ, float upX, float upY, float upZ)
        : camFront(maths::vec3(0.0f, 0.0f, -1.0f))
    {
        position = maths::vec3(posX, posY, posZ);
        worldUp = maths::vec3(upX, upY, upZ);
        updateCameraVectors();
        updateViewMatrix();
        updateProjectionMatrix();
    }

    void PerspectiveCamera::updateCameraVectors()
    {
        // TODO: Re-calculate camFront vector using additional factors or update it in the derived camera  types.
        camRight = maths::vec3::normalize(maths::vec3::crossProduct(camFront, worldUp));
        camUp = maths::vec3::normalize(maths::vec3::crossProduct(camRight, camFront));
        updateViewMatrix();
    }

    void PerspectiveCamera::updateViewMatrix()
    {
        m_ViewMatrix = maths::mat4::LookAt(position, position + camFront, camUp);
    }

    void PerspectiveCamera::updateProjectionMatrix()
    {   
        // TODO: Fix the maths::perspetive matrix  calculation.
        /*
         * Currently this Projection matrix doesn't work, we are calculating it again
         * in the BatchRenderer3D using glm::perspetive. The (0, 0) and (1, 1) elements are calculated
         * wrong by the maths::perspective. Hence Querying for the perspetive matrix using this 
         * method may result in unexpected behavior.
         */
        m_ProjectionsMatrix = maths::mat4::perspective(FOV, aspectRatio, nearClipping, farClipping);
    }

} }