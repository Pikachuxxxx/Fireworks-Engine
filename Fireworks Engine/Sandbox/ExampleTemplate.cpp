#include <fireworks.h>

using namespace fireworks;

class ExampleTemplate : public Fireworks
{
private:
    Window* window;
public:
    ExampleTemplate()
    {
        window = createWindow(" Example", 800, 600);
    }

    ~ExampleTemplate()
    {

    }

    // Runs once per initialization
    void init() override
    {

    }

    // Runs once per second
    void tick() override
    {

    }

    // Runs 60 times per second
    void update() override
    {

    }

    // Runs as fast as possible
    void render() override
    {

    }
};

int main()
{
    ExampleTemplate game;
    game.start();
    return 0;
}
