/* 
 * A simple example to draw a square sprite with custom color
 */
#include <fireworks.h>

using namespace fireworks;

class SimpleBox : public Fireworks
{
private:
    Window* window;
    Layer*  layer;
public:
    SimpleBox() { }

    ~SimpleBox()
    {
        delete layer;
    }

    // Runs once per initialization
    void init() override
    {
        window = createWindow("Simple Box Example : Fireworks Engine", 800, 600);
        layer = new Layer(new BatchRenderer2D(),
                new Shader(".\\shaders\\basic.vert",
                           ".\\shaders\\basic.frag"),
                mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f));

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
