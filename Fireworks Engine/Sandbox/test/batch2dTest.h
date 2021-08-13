#pragma once
#include <fireworks.h>

using namespace fireworks;

class Batch2DTest : public Fireworks
{
private:
	Window* window;
	Camera2D* camera;
	Layer* layer;
public:
	Batch2DTest()
	{
		window = createWindow("Testing Instance rendering", 800, 600);
		camera = new Camera2D(ortho(0.0f, 16.0f, 0.0f, 10.0f, -1.0f, 1.0f));

		Shader* basicShader = new Shader(".\\shaders\\basic.vert", ".\\shaders\\basic.frag");
		BatchRenderer2D* batchRenderer = new BatchRenderer2D(camera, basicShader);

		layer = new Layer(batchRenderer);

		Texture* test = new Texture(".\\resources\\glow triangle.png");


		for (float x = 0; x < 16.0f; x += 0.1f)
		{
			for (float y = 0; y < 10.0f; y += 0.1f)
			{
				Sprite* sprite = new Sprite(vec3(x, y, 0.0f), vec2(0.1f, 0.1f), vec4(rand() % 1000 / 1000.0f, 0, 1, 1), Primitive2D::Quad);
				layer->add(sprite);
			}
		}
	}

	~Batch2DTest()
	{

	}

	// Runs once per initialization
	void init() override
	{

	}

	// Runs once per second
	void tick() override
	{
		std::cout << "FPS : " << getFPS() << std::endl;
	}

	// Runs 60 times per second
	void update() override
	{

	}

	// Runs as fast as possible
	void render() override
	{
		layer->render();
	}
};