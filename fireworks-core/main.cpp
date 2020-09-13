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
#include "src/graphics/layers/tilelayer.h"
#include "src/graphics/layers/group.h"

#include "src/graphics/texture.h"

#include <algorithm>
#include <time.h>

#define TEST_1M_SPRITES 1
#define TEST_GROUPS 0
int main()
{
    using namespace fireworks;
    using namespace graphics;
    using namespace maths;
    using namespace utils;

    Window window("fireworks !!!", 800, 600);

    /* Auto-enabling Shaders while setting Uniforms */
    Shader shader("fireworks-core/src/shaders/basic.vert", "fireworks-core/src/shaders/basic.frag");
    Shader shader2("fireworks-core/src/shaders/basic.vert", "fireworks-core/src/shaders/basic.frag");
    shader.setUniform4f("colour", vec4(0.9f, 0.3f, 0.4f, 1.0f));
    shader2.setUniform4f("colour", vec4(0.9f, 0.9f, 0.9f, 1.0f));

#if TEST_1M_SPRITES
    TileLayer layer(&shader);
    for (float x = 0; x < 16.0f; x++)
    {
        for (float y = 0; y < 9.0f; y++)
        {
            layer.add(new Sprite(x, y, 0.8f, 0.8f, maths::vec4(rand() % 1000 / 1000.0f, 0.0f, 1.0f, 1.0f)));

        }
    }
#elif TEST_GROUPS

    TileLayer layer2(&shader2);

    mat4 transform = mat4::rotation(0.0f, vec3(0, 0, 1.0f)) * mat4::translation(vec3(8.0f, 4.5f, 0));
    Group* group = new Group(transform);
    group->add(new Sprite(0.0f, 0.0f, 4, 4, maths::vec4(1.0f, 0.0f, 0.2f, 1.0f)));

    Group *subGroup = new Group(mat4::translation(vec3(0.5f, 0.5f, 0.0f)));
    subGroup->add(new Sprite(0.0f, 0.0f, 3, 3, maths::vec4(1, 1, 1, 1)));
    subGroup->add(new Sprite(0.5f, 0.5f, 2, 2, maths::vec4(0.6f, 0.7f, 0.1f, 1)));

    group->add(subGroup);

    layer2.add(group);
#endif

    TileLayer textestLayer(&shader2);
    textestLayer.add(new Sprite(6, 4, 4, 4, maths::vec4(1.0f, 0.4f, 1.0f, 1.0f)));

    Texture texture("Resources/test.png");
    texture.bind();
    shader2.setUniform1i("tex", 0); // shader is auto-enabled


    while(!window.closed())
    {
        window.clear();

        double x, y;
        window.getMousePosition(x, y);
        float clampedX = clamp((float)x, -1.0f, 1.0f, 800.0f, 0.0f);
        float clampedY = clamp((float)y, -1.0f, 1.0f, 600.0f, 0.0f);

        shader.setUniform2f("light_pos", vec2(clampedX, -1.0f * clampedY));
        shader2.setUniform2f("light_pos", vec2(clampedX, -1.0f * clampedY));

        // textestLayer.render();
        layer.render();

        window.update();
    }
    return 0;
}
