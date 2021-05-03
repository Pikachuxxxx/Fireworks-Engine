#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace fireworks { namespace graphics {

	/// The eye of the 2D world.
	///
	/// aka Orthographic Camera, every scene and renderer requires a camera to see anything
	class Camera2D // aka Orthographic Camera
	{
	private:
		glm::vec3			m_Position;
		float				m_Rotation = 0.0f;

		glm::mat4			m_ProjectionMatrix;
		glm::mat4			m_ViewMatrix;
		glm::mat4			m_ViewProjectionMatrix;
	public:
		/// Creates a camera by taking in a projection matrix
		///
		/// @param projection The projection matrix onto which the world will be mapped to
		Camera2D(glm::mat4 projection);

		/// Updates the camera
		void update();

		/// Sets the position of the camera
		///
		/// @param pos The position of the camera in the world
		void setPosition(const glm::vec3& pos) { m_Position = pos; updateViewMatrix(); }
		/// Sets the rotation of the camera
		///
		/// @param rot The rotation of the camera in the world
		void setRotaion(float rot) { m_Rotation = rot; updateViewMatrix(); }

		/// Gets the position of the camera in the world
		const glm::vec3& getPosition() const { return m_Position; }
		/// Gets the rotation of the camera in the world
		const float getRotation() const { return m_Rotation; }

		/// Gets the projection matrix with which the camera is rendering the scene
		const glm::mat4& getProjectionMatrix() const { return m_ProjectionMatrix; }
		/// Gets the view matrix of the camera
		const glm::mat4& getViewMatrix()	const { return m_ViewMatrix; }
		/// Gets the View * Projection matrix
		const glm::mat4& getProjectionViewMatrix() const { return m_ViewProjectionMatrix; }
	private:
		void updateViewMatrix();
	};


} }
