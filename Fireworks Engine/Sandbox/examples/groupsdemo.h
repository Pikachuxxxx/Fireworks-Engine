/*
 * A simple example showing the usage of groups to nest object relative to one another
 * Note : the sprite that you add first to group will be rendered top 
 * FIFO (first-in-first-out) way of rendering the sprites is done in the groups
 */
#include <fireworks/fireworks.h>

using namespace fireworks;

class GroupsDemo : public Fireworks
{
private:
    Window* window;
    Layer*  layer;
    Group*  group1;
    Group*  group2;
public:
    GroupsDemo() { }

    ~GroupsDemo()
    {
        delete layer;
    }

    // Runs once per initialisation
    void init() override
    {
        window = createWindow("Example Template", 800, 600);

        layer = new Layer(
                new BatchRenderer2D(),
                new Shader(".\\shaders\\basic.vert",
                           ".\\shaders\\basic.frag"),
                mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f));

        group1 = new Group(mat4::translation(vec3(2.0f, 2.5f, 0.0f)));
        group1->add(new Sprite(0.0f, 0.0f, 5.0f, 3.0f, vec4(1.0f, 1.0f, 0.0f, 1.0f)));

        group2 = new Group(mat4::translation(vec3(0.5f, 0.5f, 1.0f))); // palced relative to group 1
        group2->add(new Sprite(2.5f, 0.0f, 3.0f, 1.0f, vec4(0.2f, 0.3f, 0.0f, 1.0f))); // fifo : the sprite that you add first first will be rendered on top
        group2->add(new Sprite(0.0f, 0.0f, 4.0f, 2.0f, vec4(1.0f, 0.0f, 1.0f, 1.0f)));

        group1->add(group2);

        layer->add(group1);
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