#include <fireworks/fireworks.h>

using namespace fireworks;

class SimpleBox : public Fireworks
{
private:
    Window* window;
    Layer* layer;
public:
    SimpleBox() { }

    ~SimpleBox()
    {
        delete layer;
    }

    // Runs once per initialisation
    void init() override
    {
        window = createWindow("Test Game Example : Fireworks Engine", 800, 600);

        #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
        #ifdef _WIN64
            layer = new Layer(new BatchRenderer2D(),
                    new Shader("C:\\Dev\\Fireworks-Engine\\fireworks-core\\src\\shaders\\basic.vert",
                               "C:\\Dev\\Fireworks-Engine\\fireworks-core\\src\\shaders\\basic.frag"),
                    mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f));
        #endif
        #elif __APPLE__
            layer = new Layer(new BatchRenderer2D(),
                    new Shader("../Fireworks-core/src/shaders/basic.vert",
                               "../Fireworks-core/src/shaders/basic.frag"),
                    mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f));
        #endif

        Sprite* box = new Sprite(4.0f, 4.0f, 4.0f, 4.0f, vec4(1.0f, 1.0f, 0.0f, 1.0f));
        layer->add(box);
    }

    // Runs once per second
    void tick() override
    {

    }

    // Runs 60 times per second
    void update() override
    {
        layer->m_Shader->setUniformMat4("model", mat4::translation(vec3(sin(glfwGetTime()) * 2, 2.0f, 0.0f)));
    }

    // Runs as fast as possible
    void render() override
    {
        layer->render();
    }
};
