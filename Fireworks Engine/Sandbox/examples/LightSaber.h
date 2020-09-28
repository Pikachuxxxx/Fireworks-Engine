/*
 * A simple example to control a simple light source (not a real one, a simple trick using the fragment shader) using mouse input
 * Use the Mouse to move around to locate the lost diamond and click the LMB to capture the diamonds lost (infinite diamonds to be found) 
 */
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
        window = createWindow("Light Saber : Mouse Input Example", 800, 600);

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
       vec2 localMousePos = vec2(clamp(mouseX, -1.0, 1.0, 800.0, 0.0), -clamp(mouseY, -1.0, 1.0, 600.0, 0.0));
       vec2 view_matrixMousePos = vec2(clamp(mouseX, 0.0, 16.0, 800.0, 0.0), clamp(mouseY, 9.0, 0.0, 600.0, 0.0));
       layer->m_Shader->setUniform2f("light_pos", localMousePos);

       float squaredDistance = (float)abs(pow(diamond->position.x - view_matrixMousePos.x, 2) +
                                          pow(diamond->position.y - view_matrixMousePos.y, 2));

       if (squaredDistance <= 0.4f && window->isMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
       {
           vec3 randPos = vec3(rand() % 16, rand() % 9, 0.0f);
           diamond->position = randPos;
       }
    }

    // Runs as fast as possible
    void render() override
    {
        layer->render();
    }
};

