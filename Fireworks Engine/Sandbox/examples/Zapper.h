#include <fireworks.h>

using namespace fireworks;

class Zapper : public Fireworks
{
private:
	Window*					window;
	Camera2D*				camera;
	Layer*					defaultLayer;

	AudioClip*				zapclip;
	Texture*				bulletTex;
	std::vector<Sprite*>	bullets;
	Sprite*					spaceShip;

	float					spaceshipSpeed;
	Label* stats;
public:
	Zapper()
		:spaceshipSpeed(9.0f)
	{
		window = createWindow(" Example", 600, 900);
		camera = new Camera2D(mat4::orthographic(-12.0f, 12.0f, -18.0f, 18.0f, -1.0f, 1.0f));
		Shader* basicShader = new Shader(".\\shaders\\basic.vert", ".\\shaders\\basic.frag");
		BatchRenderer2D* batchRenderer = new BatchRenderer2D(camera, basicShader);
		defaultLayer = new Layer(batchRenderer);
		
		zapclip = new AudioClip(".\\resources\\sounds\\laser8.wav");
		Font font(".\\resources\\fonts\\FiraCode-Light.ttf", 12);
		Texture* shipTex = new Texture(".\\resources\\spaceship.png");
		bulletTex = new Texture(".\\resources\\test3.png");

		spaceShip = new Sprite(vec3(-2, -10, 0), vec2(4, 4), shipTex);

		stats = new Label("", vec3(25, 500, 0), vec3(0, 0, 0), font);

		defaultLayer->add(spaceShip);
	}

	~Zapper()
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
		
		spaceShipMovement();
		spaceShipShoot();
		
		
	}

	// Runs as fast as possible
	void render() override
	{
		glClearColor((float)243 / 255, (float)146 / 255, (float)51 / 255, 1.0f);

		defaultLayer->render();

		stats->renderText();
		stats->text = "Bullets : " + std::to_string(bullets.size());
	}
	
	void spaceShipMovement()
	{
		// clamp the spaceship's position
		if (spaceShip->position.x >= 8.0f)
			spaceShip->position.x = 8.0f;
		if (spaceShip->position.x <= -12)
			spaceShip->position.x = -12.0f;

		// side wise movement
		if (window->isKeyHeld(GLFW_KEY_RIGHT))
			spaceShip->position.x += 0.02f * spaceshipSpeed;
		else if (window->isKeyHeld(GLFW_KEY_LEFT))
			spaceShip->position.x -= 0.02f * spaceshipSpeed;
	}

	void spaceShipShoot()
	{
		// spaceship shoot
		if ((window->isKeyPressed(GLFW_KEY_UP) || window->isKeyPressed(GLFW_KEY_ENTER)) && !zapclip->isPlaying())
		{
			zapclip->PlayOnce();
			bullets.push_back(new Sprite(spaceShip->position + vec3(2, 0, 0), vec2(1, 1), bulletTex));
		}

		// Instantiate and delete bullets after going out of the bounds of the screen
		for (int i = 0; i < bullets.size(); i++)
		{
			defaultLayer->add(bullets[i]);
			bullets[i]->position.y += 2.0f;

			if (bullets[i]->position.y > 18)
			{
				bullets.erase(bullets.begin() + i);
			}
		}
	}
};