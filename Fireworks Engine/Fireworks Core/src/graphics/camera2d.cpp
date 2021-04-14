#include "camera2d.h"

namespace fireworks { namespace graphics {
	
	Camera2D::Camera2D(glm::mat4 projection)
		: m_ProjectionMatrix(projection), m_ViewMatrix(glm::mat4(1.0f))
	{

	}

	void Camera2D::update()
	{

	}

	void Camera2D::updateViewMatrix()
	{
		using namespace glm;

		glm::mat4 transform(1.0f);
		transform = glm::translate(transform, m_Position);
		transform *= glm::rotate(transform, m_Rotation, glm::vec3(0.0f, 0.0f, 1.0f));

		m_ViewMatrix = glm::inverse(transform);

		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

} }