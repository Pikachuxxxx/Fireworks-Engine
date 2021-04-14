#pragma once

#include "src/audio/audioclip.h"

#include "src/components/component.h"

#include "src/graphics/camera2d.h"
#include "src/graphics/freeflycamera.h"
#include "src/graphics/mesh.h"
#include "src/graphics/model.h"
#include "src/graphics/scene3d.h"
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
#include "src/graphics/renderables/renderable3d.h"

#include "src/graphics/renderers/batchrenderer2d.h"
#include "src/graphics/renderers/batchrenderer3d.h"
#include "src/graphics/renderers/renderer2d.h"
#include "src/graphics/renderers/renderer3d.h"
#include "src/graphics/renderers/ShotRenderer2D.h"

#include "src/managers/physicsmanager.h"

#include "src/maths/maths.h"

#include "src/physics/rigidbody2d.h"

#include "src/utils/fileutils.h"
#include "src/utils/timer.h"
#include "src/utils/wavloader.h"

namespace fireworks {

	using namespace audio;
	using namespace components;
    using namespace graphics;
    using namespace maths;
	using namespace physics;
    using namespace utils;

    /// The Game class to use the Fireworks Engine.
    /// 
    /// It is the main class from which the game class must be derived from to use the fireworks engine
    class Fireworks
    {
    private:
        /// The main window of the engine's game
        graphics::Window*   m_Window;
        /// Timer object to keep track of the game loop time
        Timer*              m_Timer;
        /// The total Frames per second (FPS)
        unsigned int        m_FramesPerSecond;
        /// The total Updates happening per second (UPS)
        unsigned int        m_UpdatePerSecond;
        /// The Time Scale of the engine update loop
        float               m_TimeScale = 1.0f;
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

        inline void SetTimeScale(float ts) { m_TimeScale = ts; }
    private:
        void run();
    };
}
