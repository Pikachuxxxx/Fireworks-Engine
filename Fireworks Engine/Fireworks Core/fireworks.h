#pragma once

#include "src/graphics/batchrenderer2d.h"
#include "src/graphics/camera2d.h"
#include "src/graphics/instancerenderer2d.h"
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

#include "src/maths/maths.h"
#include "src/utils/fileutils.h"
#include "src/utils/timer.h"

namespace fireworks {

    using namespace graphics;
    using namespace maths;
    using namespace utils;

    /// The Game class to use the fireworks engine
    /// 
    /// It is the main class from which the game class must be derived from to use the fireworks engine
    class Fireworks
    {
    private:
        graphics::Window* m_Window;
        Timer* m_Timer;
        unsigned int m_FramesPerSecond, m_UpdatePerSecond;
        double m_CurrentFrame, m_LastFrame;
    protected:  
        /// The completion time in seconds since the last frame 
        double deltaTime;
    protected:
        Fireworks()
            : m_FramesPerSecond(0), m_UpdatePerSecond(0), m_CurrentFrame(0.0), m_LastFrame(0.0)
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
        /// @returns An object of type Window
        graphics::Window* createWindow(const char* name, int width, int height)
        {
            m_Window = new graphics::Window(name, width, height);
            return m_Window;
        }
    public:
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

		inline const unsigned int getFPS() { return m_FramesPerSecond; }
		inline const unsigned int getUPS() { return m_UpdatePerSecond; }
    private:
        void run()
        {
            m_Timer = new Timer();
            float timer = 0.0f;
            float updateTick = 1.0f / 60.0f;
            float updateTimer = 0.0f;
            unsigned int frames = 0;
            unsigned int updates = 0;
            while(!m_Window->closed())
            {
                m_CurrentFrame = glfwGetTime();
                m_Window->clear();

				if (m_Timer->elapsed() - updateTimer > updateTick)
				{
					update();
					updates++;
					updateTimer += updateTick;

				}
                frames++;
                render();
                deltaTime = m_CurrentFrame - m_LastFrame;
                m_LastFrame = m_CurrentFrame;
                m_Window->update();
                if(m_Timer->elapsed() - timer > 1.0f)
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
