/*
 * A simple example to control a simple light source (not a real one, a simple trick using the fragment shader) using mouse input
 * Use the Mouse to move around to locate the lost diamond and click the LMB to capture the diamonds lost (infinite diamonds to be found) 
 */
#include <fireworks.h>

using namespace fireworks;

class LightSaber : public Fireworks
{
private:
    Window*     window;
    Camera2D*   camera;
    Layer*      layer;
    Shader*     basicShader;
    Sprite*     diamond;

    double      mouseX;
    double      mouseY;
public:
    LightSaber() { }

    ~LightSaber() { }

    // Runs once per initialization
    void init() override
    {
        window = createWindow("Light Saber : Mouse Input Example", 800, 600);
		camera = new Camera2D(mat4::orthographic(-8.0f, 8.0f, -6.0f, 6.0f, -1.0f, 1.0f));

		basicShader = new Shader(".\\shaders\\basic.vert", ".\\shaders\\light.frag");
		BatchRenderer2D* batchRenderer = new BatchRenderer2D(camera, basicShader);

		layer = new Layer(batchRenderer);

        Texture* diamondTex = new Texture(".\\resources\\diamond.png");
        diamond = new Sprite(vec3(0.0f, 2.5f, 0.0f), vec2(0.7f, 0.5f), diamondTex);
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
       vec2 view_matrixMousePos = vec2(clamp(mouseX, -8.0, 8.0, 800.0, 0.0), -1.0f * clamp(mouseY, -6.0, 6.0, 600.0, 0.0));
       basicShader->setUniform2f("light_pos", localMousePos);

       float squaredDistance = (float)abs(pow(diamond->position.x - view_matrixMousePos.x, 2) +
                                          pow(diamond->position.y - view_matrixMousePos.y, 2));

       if (squaredDistance <= 0.4f && window->isMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
       {
           vec3 randPos = vec3(getRandomValue(-7, 7), getRandomValue(-5, 5), 0.0f);
           diamond->position = randPos;
       }
    }

    // Runs as fast as possible
    void render() override
    {
        layer->render();
    }
};

