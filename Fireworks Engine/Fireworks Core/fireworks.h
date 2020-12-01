#pragma once

#include "src/audio/audioclip.h"

#include "src/components/component.h"

#include "src/graphics/batchrenderer2d.h"
#include "src/graphics/camera2d.h"
#include "src/graphics/ShotRenderer2D.h"
#include "src/graphics/renderer2d.h"
#include "src/graphics/shader.h"
#include "src/graphics/texture.h"
#include "src/graphics/window.h"

#include "src/graphics/buffers/buffer.h"
#include "src/graphics/buffers/framebuffer.h"
#include "src/graphics/buffers/indexbuffer.h"
#include "src/graphics/buffers/vertexarray.h"

#include "src/graphics/layers/group.h"
#include "src/graphics/layers/layer.h"

#include "src/graphics/renderables/label.h"
#include "src/graphics/renderables/sprite.h"
#include "src/graphics/renderables/renderable2d.h"

#include "src/managers/physicsmanager.h"

#include "src/maths/maths.h"

#include "src/physics/rigidbody2d.h"

#include "src/utils/fileutils.h"
#include "src/utils/timer.h"
#include "src/utils/wavloader.h"

namespace fireworks {

	using namespace audio;
    using namespace graphics;
    using namespace maths;
    using namespace utils;
	using namespace components;
	using namespace physics;

    /// The Game class to use the Fireworks Engine.
    /// 
    /// It is the main class from which the game class must be derived from to use the fireworks engine
    class Fireworks
    {
    private:
        graphics::Window* m_Window;
        Timer* m_Timer;
        unsigned int m_FramesPerSecond, m_UpdatePerSecond;        
    protected:
        Fireworks()
            : m_FramesPerSecond(0), m_UpdatePerSecond(0)
        {

        }

        virtual ~Fireworks()
        {
            delete m_Window;
            delete m_Timer;
        }
        /// A function to create the Main Window
        /// 
        /// @param name The name of the window
        /// @param width The width of the window
        /// @param height The height of the window
        /// @returns An pointer object to the currently created of type graphics::Window
        /// Use this object to set properties of the window and control the input
        /// @see graphics::Window for more details on using/seeting the window properties
        graphics::Window* createWindow(const char* name, int width, int height)
        {
            m_Window = new graphics::Window(name, width, height);
            return m_Window;
        }
    public:
        /// A function that starts the main game loop.
        /// 
        /// @attention The main class the derives from fireworks::Fireworks must use this method (in main.cpp) to start the game
        void start()
        {
            init();
            run();
         }
    protected:
        /// Runs once per initialization
        virtual void init() = 0;
        /// Runs once per second
        virtual void tick() { };
        /// Runs 60 times per second
        virtual void update() { };
        /// Runs as fast as possible
        virtual void render() = 0;

		/// A function to get the current FPS : Frames per second .
		/// 
		/// @returns Returns the current FPS of type unsigned int 
		inline const unsigned int getFPS() { return m_FramesPerSecond; }

		/// A function to get the current UPS : Updates per second .
        /// 
        /// We usually want the number of updates to be around 60 per second
        /// @returns Returns the current UPS of type unsigned int 
		inline const unsigned int getUPS() { return m_UpdatePerSecond; }
    private:
        void run()
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
            while(!m_Window->closed())
            {
                m_Window->clear();
                World.Step(physicsTick, velocityIterations, positionIterations);

				if (m_Timer->deltaTime() - updateTimer > updateTick)
				{
					update();
					updates++;
					updateTimer += updateTick;
				}
                frames++;
				render();
                m_Window->update();
                if(m_Timer->deltaTime() - timer > 1.0f)
                {
                    timer += 1.0f;
                    m_FramesPerSecond = frames;
                    m_UpdatePerSecond = updates;
                    frames = 0;
                    updates = 0;
                    tick();
                }
            }
        }
    };
}
