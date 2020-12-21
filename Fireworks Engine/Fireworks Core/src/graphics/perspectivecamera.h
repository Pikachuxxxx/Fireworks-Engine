#pragma once

// Std. Includes
#include <vector>

#include "../maths/maths.h"

namespace fireworks { namespace graphics {

    class PerspectiveCamera
    {
    public:
        maths::vec3 position;
        maths::vec3 camFront;
        maths::vec3 camUp;
        maths::vec3 camRight;
        maths::vec3 worldUp;
        float       FOV;
        float       aspectRatio;
        float       nearClipping;
        float       farClipping;
    private:
        maths::mat4 m_ViewMatrix;
        maths::mat4 m_ProjectionsMatrix;
        maths::mat4 m_ViewProjectionMatrix;
    public:
        PerspectiveCamera(maths::vec3 position = maths::vec3(0.0f, 0.0f, 0.0f), maths::vec3 worldUp = maths::vec3(0.0f, 1.0f, 0.0f), float aspectRatio = 1.33f, float fov = 45.0f);
        PerspectiveCamera(float posX, float posY, float posZ, float upX, float upY, float upZ);

        const maths::mat4& getViewMatrix() const { return m_ViewMatrix; }
        const maths::mat4& getProjectionMatrix() const { return m_ProjectionsMatrix;}
        const maths::mat4& getViewProjectionsMatrix() const { return m_ViewProjectionMatrix;}
    private:
        void updateCameraVectors();
        void updateViewMatrix();
        void updateProjectionMatrix();
    };
    
} }

