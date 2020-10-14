/*
 * A simple example to draw a square sprite with custom texture image
 */
#include <fireworks.h>

using namespace fireworks;

class TextImage : public Fireworks
{
private:
    Window*     window;
    Camera2D*   camera;
    Layer*      layer;
public:
    TextImage() { }

    ~TextImage()
    {
        delete layer;
    }

    // Runs once per initialization
    void init() override
    {
        window = createWindow("Textures Example : Fireworks Engine", 800, 600);
		camera = new Camera2D(mat4::orthographic(-16.0f, 16.0f, -12.0f, 12.0f, -1.0f, 1.0f));

		Shader* basicShader = new Shader(".\\shaders\\basic.vert", ".\\shaders\\basic.frag");
		BatchRenderer2D* batchRenderer = new BatchRenderer2D(camera, basicShader);

		layer = new Layer(batchRenderer);

		Texture* testTex = new Texture(".\\resources\\test.png");
        Sprite* box = new Sprite(vec3(4.0f, 4.0f, 0.0f), vec2(4.0f, 4.0f), testTex);
        layer->add(box);
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

