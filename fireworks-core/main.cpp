#include "src/graphics/window.h"
#include "src/graphics/shader.h"
#include "src/maths/maths.h"
#include "src/utils/fileutils.h"

#include "src/graphics/buffers/buffer.h"
#include "src/graphics/buffers/indexbuffer.h"
#include "src/graphics/buffers/vertexarray.h"

#include "src/graphics/renderer2d.h"
#include "src/graphics/simple2drenderer.h"

#include <algorithm>

int main()
{
    using namespace fireworks;
    using namespace graphics;
    using namespace maths;
    using namespace utils;

    Window window("fireworks !!!", 800, 600);
    // glClearColor(0.8, 0.2, 0.3, 1.0f);

    mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
    Shader shader("fireworks-core/src/shaders/basic.vert", "fireworks-core/src/shaders/basic.frag");
    shader.enable();
    shader.setUniformMat4("projection", ortho);
    shader.setUniform2f("light_pos", vec2(4.0f, 3.0f));
    shader.setUniform4f("colour", vec4(0.9f, 0.3f, 0.4f, 1.0f));

    Renderable2D sprite(maths::vec3(2, 5, 0), maths::vec2(4, 4), maths::vec4(0.1 , 1.1, 0.1, 1.0), shader);
    Renderable2D sprite2(maths::vec3(7, 1, 0), maths::vec2(2, 3), maths::vec4(0.2 , 0.1, 1.1, 1.0), shader);

    Simple2DRenderer renderer;

    while(!window.closed())
    {
        window.clear();

        double x, y;
        window.getMousePosition(x, y);
        float clampedX = clampFloat((float)x, -1.0f, 1.0f, 800.0f, 0.0f);
        float clampedY = clampFloat((float)y, -1.0f, 1.0f, 600.0f, 0.0f);
        shader.setUniform2f("light_pos", vec2(clampedX, -1.0f * clampedY));

        renderer.submit(&sprite);
        renderer.submit(&sprite2);
        renderer.flush();

        window.update();
    }

    return 0;
}
