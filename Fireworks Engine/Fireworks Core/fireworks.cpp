#include "fireworks.h"

namespace fireworks {

	void Fireworks::run()
	{
		m_Timer = new Timer();
		float timer = 0.0f;
		float updateTick = 1.0f / 60.0f;
		float updateTimer = 0.0f;
		float physicsTick = 1.0f / 60.0f;
		int velocityIterations = 6;
		int positionIterations = 2;
		unsigned int frames = 0;
		unsigned int updates = 0;
		while (!m_Window->closed())
		{
			m_Window->clear();
			World.Step(physicsTick, velocityIterations, positionIterations);

			if (m_Timer->elapsedTime() - updateTimer > (updateTick * m_TimeScale))
			{
				update();
				updates++;
				updateTimer += updateTick * m_TimeScale;
			}
			frames++;
			render();
			m_Window->update();
			if (m_Timer->elapsedTime() - timer > (1.0f * m_TimeScale))
			{
				timer += (1.0f * m_TimeScale);
				m_FramesPerSecond = frames;
				m_UpdatePerSecond = updates;
				frames = 0;
				updates = 0;
				tick();
			}
		}
	}

}