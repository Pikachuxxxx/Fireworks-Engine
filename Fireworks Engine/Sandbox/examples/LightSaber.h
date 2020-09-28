#include <fireworks/fireworks.h>

using namespace fireworks;

class LightSaber : public Fireworks
{
private:
    Window* window;
    Layer* layer;
    Sprite* diamond;

    double mouseX;
    double mouseY;
public:
    LightSaber() { }

    ~LightSaber() { }

    // Runs once per initialisation
    void init() override
    {
        window = createWindow("Hungry Box : Keyboard Input Example", 800, 600);

        layer = new Layer(
                new BatchRenderer2D(),
                new Shader(".\\shaders\\basic.vert",
                           ".\\shaders\\light.frag"),
                mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f));

        Texture* diamondTex = new Texture(".\\resources\\diamond.png");
        diamond = new Sprite(8.0f, 4.5f, 0.7f, 0.5f, diamondTex);
        layer->add(diamond);

        srand(time(0));
    }

    // Runs once per second
    void tick() override { }

    // Runs 60 times per second
    void update() override
    {
       window->getMousePosition(mouseX, mouseY);
       layer->m_Shader->setUniform2f("light_pos", vec2(clamp(mouseX, -1.0, 1.0, 800.0, 0.0), clamp(mouseY, -1.0, 1.0, 600.0, 0.0)));
    }

    // Runs as fast as possible
    void render() override
    {
        layer->render();
    }
};

