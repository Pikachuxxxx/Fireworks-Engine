#pragma once

#include "src/graphics/window.h"
#include "src/graphics/shader.h"
#include "src/graphics/texture.h"
#include "src/graphics/renderer2d.h"
#include "src/graphics/batchrenderer2d.h"

#include "src/graphics/buffers/buffer.h"
#include "src/graphics/buffers/indexbuffer.h"
#include "src/graphics/buffers/vertexarray.h"

#include "src/graphics/layers/layer.h"
#include "src/graphics/layers/group.h"

#include "src/graphics/renderables/label.h"
#include "src/graphics/renderables/sprite.h"
#include "src/graphics/renderables/static_sprite.h"
#include "src/graphics/renderables/renderable2d.h"

#include "src/maths/maths.h"
#include "src/utils/fileutils.h"
#include "src/utils/timer.h"

namespace fireworks {

    using namespace graphics;
    using namespace maths;
    using namespace utils;

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
        // Runs once per initialisation
        virtual void init() = 0;
        // Runs once per second
        virtual void tick() { };
        // Runs 60 times per second
        virtual void update() { };
        // Runs as fast as possible
        virtual void render() = 0;

        const unsigned int getFPS() { return m_FramesPerSecond; }
        const unsigned int getUPS() { return m_UpdatePerSecond; }
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
                m_Window->clear();
                if(m_Timer->elapsed() - updateTimer > updateTick)
                {
                    update();
                    updates++;
                    updateTimer += updateTick;

                }
                frames++;
                render();
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
