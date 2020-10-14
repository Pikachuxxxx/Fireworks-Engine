/*
 * A simple example showing the usage of groups to nest object relative to one another
 * Note : the sprite that you add first to group will be rendered top 
 * FIFO (first-in-first-out) way of rendering the sprites is done in the groups
 */
#include <fireworks.h>

using namespace fireworks;

class GroupsDemo : public Fireworks
{
private:
    Window*     window;
    Camera2D*   camera;
    Layer*      layer;
    Group*      group1;
    Group*      group2;
public:
    GroupsDemo() { }

    ~GroupsDemo()
    {
        delete layer;
    }

    // Runs once per initialization
    void init() override
    {
		window = createWindow("Groups Example : Fireworks Engine", 800, 600);
		camera = new Camera2D(mat4::orthographic(-16.0f, 16.0f, -12.0f, 12.0f, -1.0f, 1.0f));

		Shader* basicShader = new Shader(".\\shaders\\basic.vert", ".\\shaders\\basic.frag");
		BatchRenderer2D* batchRenderer = new BatchRenderer2D(camera, basicShader);

		layer = new Layer(batchRenderer);

        group1 = new Group(mat4::translation(vec3(2.0f, 2.5f, 0.0f)));
        group1->add(new Sprite(vec3(0.0f, 0.0f, 0.0f), vec2(5.0f, 3.0f), vec4(1.0f, 1.0f, 0.0f, 1.0f)));

        group2 = new Group(mat4::translation(vec3(0.5f, 0.5f, 1.0f))); // placed relative to group 1
        group2->add(new Sprite(vec3(0.5f, 0.5f, 0.0f), vec2(3.0f, 1.0f), vec4(0.2f, 0.3f, 0.0f, 1.0f))); // FIFO : the sprite that you add first first will be rendered on top
        group2->add(new Sprite(vec3(0.0f, 0.0f, 0.0f), vec2(4.0f, 2.0f), vec4(1.0f, 0.0f, 1.0f, 1.0f)));

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