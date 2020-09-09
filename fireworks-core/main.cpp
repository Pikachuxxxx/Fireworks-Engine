#include "src/graphics/window.h"
#include "src/graphics/shader.h"
#include "src/graphics/renderer2d.h"
#include "src/graphics/simple2drenderer.h"
#include "src/graphics/batchrenderer2d.h"

#include "src/graphics/buffers/buffer.h"
#include "src/graphics/buffers/indexbuffer.h"
#include "src/graphics/buffers/vertexarray.h"

#include "src/maths/maths.h"
#include "src/utils/fileutils.h"

#include "src/graphics/static_sprite.h"
#include "src/graphics/sprite.h"

#include <algorithm>
#include <time.h>

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

    std::vector<Renderable2D*> sprites;
    srand(time(NULL));

    Sprite sprite(0, 0, 4, 5, maths::vec4(0.1 , 1.1, 0.1, 1.0));
    Sprite sprite2(7, 1, 2, 2, maths::vec4(0.2 , 0.1, 1.1, 1.0));
    // StaticSprite sprite3(maths::vec3(10, 1, 0), maths::vec2(2, 1), maths::vec4(0.9 , 0.1, 0.1, 1.0), shader);

    BatchRenderer2D renderer;
    for (float x = 0; x < 16.0f; x += 0.1f)
    {
        for (float y = 0; y < 10.0f; y += 0.1f)
        {
            sprites.push_back(new Sprite(x, y, 0.08f, 0.08f, maths::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
        }
    }


    while(!window.closed())
    {
        window.clear();

        double x, y;
        window.getMousePosition(x, y);
        float clampedX = clamp((float)x, -1.0f, 1.0f, 800.0f, 0.0f);
        float clampedY = clamp((float)y, -1.0f, 1.0f, 600.0f, 0.0f);
        shader.setUniform2f("light_pos", vec2(clampedX, -1.0f * clampedY));
        renderer.begin();
        // renderer.submit(&sprite);
        // renderer.submit(&sprite2);
        for (int  i = 0; i < sprites.size(); i++) {
            renderer.submit(sprites[i]);
        }
        // renderer.submit(&sprite3);
        renderer.end();
        renderer.flush();

        window.update();
    }

    return 0;
}
