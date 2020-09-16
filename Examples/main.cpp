#include "fireworks.h"

#define TEST_1M_SPRITES     0
#define TEST_GROUPS         0
#define TEST_TEXTURES       1

int main()
{
    using namespace fireworks;

    Window window("fireworks !!!", 800, 600);
    /* Auto-enabling Shaders while setting Uniforms */
    Shader shader("fireworks-core/src/shaders/basic.vert", "fireworks-core/src/shaders/basic.frag");
    Shader shader2("fireworks-core/src/shaders/basic.vert", "fireworks-core/src/shaders/basic.frag");
    shader.setUniform4f("colour", vec4(1.0f, 1.0f, 1.0f, 1.0f));
    shader2.setUniform4f("colour", vec4(1.0f, 1.0f, 1.0f, 1.0f));

#if TEST_1M_SPRITES

    Layer layer(&shader);
    for (float x = 0; x < 16.0f; x++)
    {
        for (float y = 0; y < 9.0f; y++)
        {
            layer.add(new Sprite(x, y, 0.8f, 0.8f, maths::vec4(rand() % 1000 / 1000.0f, 0.0f, 1.0f, 1.0f)));
        }
    }

#elif TEST_GROUPS

    Layer layer2(&shader2);

    mat4 transform = mat4::rotation(0.0f, vec3(0, 0, 1.0f)) * mat4::translation(vec3(8.0f, 4.5f, 0));
    Group* group = new Group(transform);
    group->add(new Sprite(0.0f, 0.0f, 4, 4, maths::vec4(1.0f, 0.0f, 0.2f, 1.0f)));

    Group *subGroup = new Group(mat4::translation(vec3(0.5f, 0.5f, 0.0f)));
    subGroup->add(new Sprite(0.0f, 0.0f, 3, 3, maths::vec4(1, 1, 1, 1)));
    subGroup->add(new Sprite(0.5f, 0.5f, 2, 2, maths::vec4(0.6f, 0.7f, 0.1f, 1)));

    group->add(subGroup);

    layer2.add(group);

#elif TEST_TEXTURES

    Texture* textures[] =
    {
        new Texture("Resources/test.png"),
        new Texture("Resources/test2.png"),
        new Texture("Resources/test3.png")
    };

    Layer textestLayer(new BatchRenderer2D(), &shader2, maths::mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f));
    for (float x = 0; x < 16.0f; x++)
    {
        for (float y = 0; y < 9.0f; y++)
        {
            // textestLayer.add(new Sprite(x, y, 0.8f, 0.8f, maths::vec4(rand() % 1000 / 1000.0f, 0.0f, 1.0f, 1.0f)));
            textestLayer.add(new Sprite(x, y, 0.8f, 0.8f, textures[rand() % 3]));
        }
    }

    GLint texIDs[] =
    {
        0, 1, 2, 3, 4, 5, 6, 7
    };
    shader2.setUniform1iv("textures", texIDs, 8);

    Layer textLayer(new BatchRenderer2D(), &shader2, maths::mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f));

    Label* lbl = new Label("Score : 121", 0, 0, maths::vec4(1, 1, 0.0f, 1));
    textLayer.add(lbl);


#endif

    Timer time;
    float timer = 0.0f;
    unsigned int frames = 0;

    while(!window.closed())
    {
        window.clear();
        glClearColor(1, 0.5, 1, 1);


        double x, y;
        window.getMousePosition(x, y);
        float clampedX = clamp((float)x, -1.0f, 1.0f, (float)window.getWidth(), 0.0f);
        float clampedY = clamp((float)y, -1.0f, 1.0f, (float)window.getHeight(), 0.0f);

        shader.setUniform2f("light_pos", vec2(clampedX, -1.0f * clampedY));
        shader2.setUniform2f("light_pos", vec2(clampedX, -1.0f * clampedY));

#if TEST_1M_SPRITES
        layer.render();
#elif TEST_GROUPS
        layer2.render();
#elif TEST_TEXTURES
        textestLayer.render();
#endif

textLayer.render();
        window.update();
        frames++;
        if(time.elapsed() - timer > 1.0f)
        {
            timer += 1.0f;
            std::cout << "FPS : " << frames << '\n';
            frames = 0;
        }
    }
#if TEST_TEXTURES
    for(int i = 0; i < 3; i++)
        delete textures[i];
    delete lbl;
#endif


    gltTerminate();

    return 0;
}
