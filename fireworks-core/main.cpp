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

#include <algorithm>
#include <time.h>

int main()
{
    using namespace fireworks;
    using namespace graphics;
    using namespace maths;
    using namespace utils;

    Window window("fireworks !!!", 800, 600);

    Shader shader("fireworks-core/src/shaders/basic.vert", "fireworks-core/src/shaders/basic.frag");
    shader.setUniform2f("light_pos", vec2(4.0f, 3.0f));
    shader.setUniform4f("colour", vec4(0.9f, 0.3f, 0.4f, 1.0f));

    TileLayer layer(&shader);
    layer.add(new Sprite(0, 0, 2, 2, maths::vec4(0.2f, 0.8f, 0.8f, 1.0f)));
    layer.add(new Sprite(4, 4, 2, 2, maths::vec4(0.2f, 0.8f, 0.8f, 1.0f)));


    while(!window.closed())
    {
        window.clear();

        double x, y;
        window.getMousePosition(x, y);
        float clampedX = clamp((float)x, -1.0f, 1.0f, 800.0f, 0.0f);
        float clampedY = clamp((float)y, -1.0f, 1.0f, 600.0f, 0.0f);
        shader.setUniform2f("light_pos", vec2(clampedX, -1.0f * clampedY));

        layer.render();


        window.update();
    }
    return 0;
}
