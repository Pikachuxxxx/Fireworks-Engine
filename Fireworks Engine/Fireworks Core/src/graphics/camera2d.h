#pragma once

#include "../maths/maths.h"

namespace fireworks { namespace graphics {

	class Camera2D // aka Orthographic Camera
	{
	private:
		maths::vec3			m_Position;
		float				m_Rotation = 0.0f;

		maths::mat4			m_ProjectionMatrix;
		maths::mat4			m_ViewMatrix;
		maths::mat4			m_ViewProjectionMatrix;
	public:
		Camera2D(maths::mat4 projection);

		void update();

		const maths::vec3& getPosition() const { return m_Position; }
		void setPosition(const maths::vec3& pos) { m_Position = pos; updateViewMatrix(); }

		const float getRotation() const { return m_Rotation; }
		void setRotaion(float rot) { m_Rotation = rot; updateViewMatrix(); }

		const maths::mat4& getProjectionMatrix() const { return m_ProjectionMatrix; }
		const maths::mat4& getViewMatrix()	const { return m_ViewMatrix; }
		const maths::mat4& getProjectionViewMatrix() const { return m_ViewProjectionMatrix; }
	private:
		void updateViewMatrix();
	};


} }
