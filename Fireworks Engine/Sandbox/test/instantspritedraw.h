#include <fireworks.h>

using namespace fireworks;

class IR2DTest : public Fireworks
{
private:
	Window* window;
	Camera2D* camera;
	Layer* layer;
	Layer* b_layer;
	Sprite* playerBox;
public:
	IR2DTest()
	{
	}

	~IR2DTest()
	{

	}

	// Runs once per initialization
	void init() override
	{
		window = createWindow("testing instance rendering", 800, 600);
		camera = new Camera2D(mat4::orthographic(-8.0f, 8.0f, -6.0f, 6.0f, -1.0f, 1.0f));

		Shader* basicShader = new Shader(".\\shaders\\basic.vert", ".\\shaders\\basic.frag");
		InstanceRenderer2D* instanceRenderer = new InstanceRenderer2D(camera);
		BatchRenderer2D* batchRenderer = new BatchRenderer2D(camera, basicShader);

		layer = new Layer(instanceRenderer);
		b_layer = new Layer(batchRenderer);

		playerBox = new Sprite(vec3(0.0f, 0.0f, 0.0f), vec2(1.0f, 1.0f), vec4(1.0f, 1.0f, 0.0f, 1.0f), basicShader);
		Sprite* redBox = new Sprite(vec3(-2.0f, 2.0f, 0.0f), vec2(1.0f, 1.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f), basicShader);
		Sprite* blueBox = new Sprite(vec3(2.0f, 2.0f, 0.0f), vec2(1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f));
		Sprite* lightBlueBox = new Sprite(vec3(2.0f, 4.0f, 0.0f), vec2(1.0f, 1.0f), vec4(0.1f, 0.4f, 0.6f, 1.0f));


		layer->add(playerBox);
		layer->add(redBox);

		b_layer->add(blueBox);
		b_layer->add(lightBlueBox);

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
		layer->render();
		b_layer->render();
	}
};

