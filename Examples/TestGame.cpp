#include <fireworks/fireworks.h>

using namespace fireworks;

class TestGame : public Fireworks
{
private:
    Window* window;
    Layer* layer;
public:
    TestGame() { }

    ~TestGame()
    {
        delete window;
        delete layer;
    }

    void init() override
    {
        window = createWindow("Test Game Example : Fireworks Engine", 800, 600);
        
        layer = new Layer(new BatchRenderer2D(),
                          new Shader("../Fireworks-core/src/shaders/basic.vert", "../Fireworks-core/src/shaders/basic.frag"),
                          mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f , 1.0f));

        Sprite* box = new Sprite(4.0f, 4.0f, 4.0f, 4.0f, vec4(1.0f, 1.0f, 0.0f, 1.0f));
        layer->add(box);
    }

    void render() override
    {
        layer->render();
    }
};

int main()
{
    TestGame game;
    game.start();
    return 0;
}
