#pragma once

// Std. Includes
#include <vector>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include "../maths/maths.h"

namespace fireworks { namespace graphics {

    /// A perspective camera to view objects in perspective projection
    class PerspectiveCamera
    {
    public:
        /// The position of the camera in 3d space
        maths::vec3 position;
        /// The front vector of the camera
        maths::vec3 camFront;
        /// The up vector of the camera
        maths::vec3 camUp;
        /// The right vector of the camera
        maths::vec3 camRight;
        /// The world up vector
        maths::vec3 worldUp;
        /// Field of view angle of the camera
        float       FOV;
        /// Camera view's aspect ratio
        float       aspectRatio;
        /// near clipping distance of the camera
        float       nearClipping;
        /// far clipping distance of the camera
        float       farClipping;
        /// The yaw angle of the camera in world space 
		float       yaw;
        /// The pitch angle of the camera in world space
		float       pitch;
    private:
        maths::mat4 m_ViewMatrix;
        maths::mat4 m_ProjectionsMatrix;
        maths::mat4 m_ViewProjectionMatrix;
    public:
        /// Creates a perspective camera
        ///
        /// @param position The position of the camera in 3d space
        /// @param worldUp The world up vector
        /// @param aspectRatio The aspect ratio of the scene
        /// @param fov The field of view for the perspective projection
        PerspectiveCamera(maths::vec3 position = maths::vec3(0.0f, 0.0f, 0.0f), maths::vec3 worldUp = maths::vec3(0.0f, 1.0f, 0.0f), float aspectRatio = 1.33f, float fov = 45.0f);
        /// Creates a perspective camera using default settings and scalar quantities
        ///
        /// @param posX The x position of the camera
        /// @param posY The y position of the camera
        /// @param posZ The z position of the camera 
        /// @param upX The x position of the world Up vector
        /// @param upY The y position of the world Up vector
        /// @param upZ The z position of the world Up vector 
        PerspectiveCamera(float posX, float posY, float posZ, float upX, float upY, float upZ);

        /// Gets the reference to the camera's view matrix
        const maths::mat4& getViewMatrix() { updateViewMatrix(); return m_ViewMatrix; }
        /// Gets the reference to the camera's projection matrix
        const maths::mat4& getProjectionMatrix() const { return m_ProjectionsMatrix;}
        /// Gets the reference to the camera's ViewProjections matrix
        const maths::mat4& getViewProjectionsMatrix() const { return m_ViewProjectionMatrix;}
    protected:
        void updateCameraVectors();
        void updateViewMatrix();
        void updateProjectionMatrix();
    };
    
} }

