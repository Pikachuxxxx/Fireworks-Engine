#include "camera2d.h"

namespace fireworks { namespace graphics {
	
	Camera2D::Camera2D(maths::vec2 viewXBounds, maths::vec2 viewYBounds)
		: m_ProjectionMatrix(maths::mat4::orthographic(viewXBounds.x, viewXBounds.y, viewYBounds.x, viewYBounds.y, -1.0f, 1.0f))
	{

	}

	void Camera2D::update()
	{

	}

	void Camera2D::updateViewMatrix()
	{
		using namespace maths;

		mat4 transform = mat4::translation(m_Position) * mat4::rotation(m_Rotation, maths::vec3(0.0f, 0.0f, 1.0f));

		m_ViewMatrix = transform.invert();

		//m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

} }