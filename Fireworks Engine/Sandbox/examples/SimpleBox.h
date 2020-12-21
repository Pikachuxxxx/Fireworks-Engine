/* 
 * A simple example to draw a square sprite with custom color
 */
#include <fireworks.h>

using namespace fireworks;

class SimpleBox : public Fireworks
{
private:
    Window*     window;
    Camera2D*   camera;
    Layer*      layer;
public:
    SimpleBox() { }

    ~SimpleBox()
    {
        delete layer;
    }

    // Runs once per initialization
    void init() override
    {
        // Initialize the window and set it's properties
        window = createWindow("Simple Box Example : Fireworks Engine", 800, 600);
        // Initialize the Camera and set the Projection Matrix
        camera = new Camera2D(mat4::orthographic(-16.0f, 16.0f, -12.0f, 12.0f, -1.0f, 1.0f));
        //camera = new Camera2D(mat4::perspective(45.0f, 1.33f, 0.1f, 100.0f));

        // Create the Renderer using a shader and pass the cam onto which you wish to render
        Shader* basicShader = new Shader(".\\shaders\\basic.vert", ".\\shaders\\basic.frag");
        BatchRenderer2D* batchRenderer = new BatchRenderer2D(camera, basicShader);

        // Pass a renderer to the layer to render the renderables in that layer using that renderer
        layer = new Layer(batchRenderer);

        // Now create and add the renderables to the layer
        Sprite* box = new Sprite(vec3(0, 0, 0), vec2(4, 4), vec4(1, 1, 0, 1));
        layer->add(box);
    }

   // Runs once per second
	void tick() override { }

    // Runs 60 times per second
    void update() override { }

    // Runs as fast as possible
    void render() override 
    {
        // Render the Layer
        layer->render();
    }
};
