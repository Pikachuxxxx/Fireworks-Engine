/*
 * A simple example to control a simple sprite using keyboard input
 * Use the Arrow keys to move the hungry player and feed him the food 
 * every time you cathc a food block you change into the collected food item colour
 */
#include <fireworks/fireworks.h>

using namespace fireworks;

class LightSaber : public Fireworks
{
private:
    Window* window;
    Layer*  layer;
    Sprite* playerBox;
    Sprite* food;
    float   speed;
public:
    LightSaber() : speed(10.0f) { }

    ~LightSaber() { }

    // Runs once per initialisation
    void init() override
    {
        window = createWindow("Hungry Box : Keyboard Input Example", 800, 600);

        layer = new Layer(
            new BatchRenderer2D(),
            new Shader(".\\shaders\\basic.vert",
                       ".\\shaders\\basic.frag"),
            mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f));

        playerBox = new Sprite(8.0f, 4.5f, 0.7f, 0.5f, vec4(1.0f, 1.0f, 0.0f, 1.0f));
        food = new Sprite(4.0f, 2.5f, 0.25f, 0.25f, vec4(1.0f, 0.0f, 0.0f, 1.0f));
        layer->add(playerBox);
        layer->add(food);

        srand(time(0));
    }

    // Runs once per second
    void tick() override { }

    // Runs 60 times per second
    void update() override
    {
        if (window->isKeyPressed(GLFW_KEY_UP))
        {
            playerBox->position.y += 0.02f * speed;
        }
        else if (window->isKeyPressed(GLFW_KEY_DOWN))
        {
            playerBox->position.y -= 0.02f * speed;
        }
        if (window->isKeyPressed(GLFW_KEY_RIGHT))
        {
            playerBox->position.x += 0.02f * speed;
        }
        else if (window->isKeyPressed(GLFW_KEY_LEFT))
        {
            playerBox->position.x -= 0.02f * speed;
        }

        float squaredDistance = abs(pow(playerBox->position.x - food->position.x, 2) +
                                    pow(playerBox->position.y - food->position.y, 2) +
                                    pow(playerBox->position.z - food->position.z, 2));

        if (squaredDistance <= 0.2f)
        {
            vec3 randPos = vec3(rand() % 16, rand() % 9, 0.0f);
            food->position = randPos;
        }
    }

    // Runs as fast as possible
    void render() override
    {
        layer->render();
    }
};
