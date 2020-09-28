/*
 * A simple example to draw a square sprite with cutom texture image
 */
#include <fireworks/fireworks.h>

using namespace fireworks;

class TextImage : public Fireworks
{
private:
    Window* window;
    Layer* layer;
public:
    TextImage() { }

    ~TextImage()
    {
        delete layer;
    }

    // Runs once per initialisation
    void init() override
    {
        window = createWindow("Textures Example : Fireworks Engine", 800, 600);
        layer = new Layer(new BatchRenderer2D(),
            new Shader(".\\shaders\\basic.vert",
                       ".\\shaders\\basic.frag"),
            mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f));


        Texture* testTex = new Texture(".\\resources\\test.png");
        Sprite* box = new Sprite(4.0f, 4.0f, 4.0f, 4.0f, testTex);
        layer->add(box);
    }

    // Runs once per second
    void tick() override { }

    // Runs 60 times per second
    void update() override { }

    // Runs as fast as possible
    void render() override
    {
        layer->render();
    }
};

