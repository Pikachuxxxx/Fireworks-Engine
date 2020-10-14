#include <fireworks.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

using namespace fireworks;

#define BUILDINGS 100

class TestCam : public Fireworks
{
private:
	Window*			window;
	Layer*			defaultLayer;
	Sprite*			box;
	Sprite*			buildings[BUILDINGS];
	Camera2D*		cam;

	float   speed;
public:
	TestCam() 
		: speed(6.0f)
	
	{
		window = createWindow("Test Cam", 800, 600);
		cam = new Camera2D(mat4::orthographic(-16.0f, 16.0f, -12.0f, 12.0f, -1.0f, 1.0f));

		Shader* basicShader = new Shader(".\\shaders\\basic.vert", ".\\shaders\\basic.frag");
		BatchRenderer2D* batchRenderer = new BatchRenderer2D(cam, basicShader);

		defaultLayer = new Layer(batchRenderer);

		box = new Sprite(vec3(0, 0, 0.1), vec2(5, 5), vec4(1, 1, 0, 1), basicShader);

	}

	~TestCam()
	{

	}

	// Runs once per initialization
	void init() override
	{
		float spacing = 0.0f;

		for (int i = 0; i < BUILDINGS; i ++)
		{
			int randWidth = getRandomValue(1, 3);
			int randHeight = getRandomValue(4, 8);   

			vec4 randColor = vec4(	getRandomValue(200, 255) / 255.0f,
									getRandomValue(200, 255) / 255.0f,
									getRandomValue(200, 255) / 255.0f,
									1.0f);

			buildings[i] = new Sprite(vec3(-10 + spacing, -12.0f + randHeight, 0.0f), vec2(randWidth, randHeight), randColor);
			spacing += randWidth;

			defaultLayer->add(buildings[i]);
		}

		//std::cout << "Some random building color is : " << buildings[3]->color << std::endl;

		cam->setPosition(vec3(-2, 0, 0));
		//cam->setRotaion(30);

		defaultLayer->add(box);
	}

	// Runs once per second
	void tick() override
	{

	}

	// Runs 60 times per second
	void update() override
	{
		cam->setPosition(box->position + vec3(-2.0f, 0.0f, 0.0f));

		if (window->isKeyPressed(GLFW_KEY_UP))
		{
			box->position.y += 0.02f * speed;
		}
		else if (window->isKeyPressed(GLFW_KEY_DOWN))
		{
			box->position.y -= 0.02f * speed;
		}
		if (window->isKeyPressed(GLFW_KEY_RIGHT))
		{
			box->position.x += 0.02f * speed;
		}
		else if (window->isKeyPressed(GLFW_KEY_LEFT))
		{
			box->position.x -= 0.02f * speed;
		}
	}

	// Runs as fast as possible
	void render() override
	{
		defaultLayer->render();
	}
};
