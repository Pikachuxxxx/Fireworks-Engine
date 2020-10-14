/*
 * A simple example to control a simple sprite using keyboard input
 * Use the Arrow keys to move the hungry player and feed him the food 
 * every time you catch a food block you change into the collected food item color
 */
#include <fireworks.h>

using namespace fireworks;

class HungryBox : public Fireworks
{
private:
    Window*     window;
    Camera2D*   camera;
    Layer*      layer;
    Sprite*     playerBox;
    Sprite*     food;
    float       speed;
    vec4        prevColor;
public:
    HungryBox() : speed(5.0f), prevColor(vec4(1, 0, 0, 1)) { }

    ~HungryBox() { }

    // Runs once per initialization
    void init() override
    {
        window = createWindow("Hungry Box : Keyboard Input Example", 800, 600);
		camera = new Camera2D(mat4::orthographic(-8.0f, 8.0f, -6.0f, 6.0f, -1.0f, 1.0f));

		Shader* basicShader = new Shader(".\\shaders\\basic.vert", ".\\shaders\\basic.frag");
		BatchRenderer2D* batchRenderer = new BatchRenderer2D(camera, basicShader);

		layer = new Layer(batchRenderer);

        playerBox = new Sprite(vec3(0.0f, 0.0f, 0.0f), vec2(1.0f, 1.0f), vec4(1.0f, 1.0f, 0.0f, 1.0f));
        food = new Sprite(vec3(4.0f, 2.5f, 0.0f), vec2(0.5f, 0.5f), vec4(1.0f, 0.0f, 0.0f, 1.0f));
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

        if (squaredDistance <= 0.6f)
        {
            vec3 randPos = vec3(getRandomValue(-7, 7), getRandomValue(-5, 5), 0.0f);
            vec4 randColor = vec4(getRandomValue(0, 255) / 255.0f, getRandomValue(0, 255) / 255.0f, getRandomValue(0, 255) / 255.0f, 1.0f);
            food->position = randPos;
            food->color = randColor;
            playerBox->color = prevColor;
            prevColor = randColor;
        }
    }

    // Runs as fast as possible
    void render() override
    {
        layer->render();
    }
};
