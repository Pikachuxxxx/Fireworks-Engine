#include <fireworks.h>

using namespace fireworks;

#define PLATFORMS_COUNT 1
class BunnysJourney : public Fireworks
{
private:
	Window*		window;
	Camera2D*	cam;
	Layer*		defaultLayer;
	Texture*	piggyTopDownSheet;
	Texture*	platformTex;
	Shader*		basicShader;
	Shader*		platformShader;
	Sprite*		piggy;
	Sprite*		platforms[PLATFORMS_COUNT];

public:
	BunnysJourney()

	{
		window = createWindow(" Example", 800, 600);
		cam = new Camera2D(vec2(-16.0f, 16.0f), vec2(-12.0f, 12.0f));
		basicShader = new Shader(".\\shaders\\basic.vert", ".\\shaders\\basic.frag");
		defaultLayer =	new Layer(new BatchRenderer2D(cam, basicShader));

		piggyTopDownSheet = new Texture(".\\resources\\bunny_spritesheet.png");
		platformTex = new Texture(".\\resources\\platform.png");


		platformShader = new Shader(".\\shaders\\basic.vert",
			".\\shaders\\basic.frag");

		piggy = new Sprite(vec3(-4, -4, 0), vec2(4, 4), basicShader, piggyTopDownSheet, vec2(8, 1));

		defaultLayer->add(piggy);
		for (int i = 0; i < PLATFORMS_COUNT; i++)
		{
			platforms[i] = new Sprite(vec3(-20 + 4 + i * 16, -8, 0), vec2(16, 4), platformShader, platformTex);
			defaultLayer->add(platforms[i]);
		}
	}

	~BunnysJourney()
	{
		delete defaultLayer;
	}

	// Runs once per initialization
	void init() override
	{
		cam->setPosition(vec3(-2, 0, 0));
		 
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

		std::cout << "FPS : " << getFPS() << std::endl;
		cam->setPosition(piggy->position + vec3(-2.0f, 0.0f, 0.0f));

		if (window->isKeyPressed(GLFW_KEY_RIGHT))
		{
			piggy->animateSprite(2, SpriteAnimationType::PING_PONG);
			piggy->position.x += 10.0f * deltaTime;
			piggy->unflipX();
		}
		else if (window->isKeyPressed(GLFW_KEY_LEFT))
		{
			piggy->animateSprite(2, SpriteAnimationType::PING_PONG);
			piggy->position.x -= 10.0f * deltaTime;
			piggy->flipX();
		}

		else
		{
			piggy->frame = 1;
		}
		piggy->m_Shader->setUniformMat4("view", cam->getViewMatrix());
		platformShader->setUniformMat4("view", cam->getViewMatrix());

		defaultLayer->render();
	}
};

