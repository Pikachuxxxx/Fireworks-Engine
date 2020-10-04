#pragma once

#include <fireworks.h>
using namespace fireworks;

class MainGame : public Fireworks
{
private:
	Window*			window;
	Shader*			defaultShader;
	Layer*			defaultLayer;
	Sprite*			playerSprite;

	Texture*		playerIdleSpriteSheetTex;

	Timer			timer;
	float 			speed;
	float			idleAnimFrameRate;
	float			currentTime;
public:
	MainGame() : speed(4.0f), idleAnimFrameRate(0.8f), currentTime(0.0f)
	{
		window = createWindow("Main Game", 1200, 800);
		defaultShader = new Shader(".\\shaders\\basic.vert", ".\\shaders\\basic.frag");
		defaultLayer = new Layer(new BatchRenderer2D(), defaultShader, mat4::orthographic(-12.0f, 12.0f, -8.0f, 8.0f, -1.0f, 1.0f));

		playerIdleSpriteSheetTex = new Texture(".\\res\\Sprites\\Drake_Idle_spritesheet.png");
		
		playerSprite = new Sprite(0.0f, 0.0f, 0.8f, 2.2f, playerIdleSpriteSheetTex, 0);

	}

	~MainGame()
	{
		delete defaultLayer;
		delete defaultShader;

		// TODO: Delete all the texture objects
	}

	// Runs once per initialization
	void init() override
	{
		glClearColor(0.890f, 0.863f, 0.835f, 1.0f); // #e3dcd5 
		defaultLayer->add(playerSprite);

	}
	       
	// Runs once per second
	void tick() override
	{

	}

	// Runs 60 times per second
	void update() override
	{
		if (window->isKeyPressed(GLFW_KEY_UP))
		{
			playerSprite->position.y += 0.02f * speed;
		}
		else if (window->isKeyPressed(GLFW_KEY_DOWN))
		{
			playerSprite->position.y -= 0.02f * speed;
		}
		if (window->isKeyPressed(GLFW_KEY_RIGHT))
		{
			playerSprite->position.x += 0.02f * speed;
		}
		else if (window->isKeyPressed(GLFW_KEY_LEFT))
		{
			playerSprite->position.x -= 0.02f * speed;
		}

		if (currentTime > idleAnimFrameRate)
		{
			playerSprite->sprframe = !playerSprite->sprframe;
			currentTime = 0.0f;
			timer.reset();
		}
		currentTime += timer.elapsed();
	}

	// Runs as fast as possible
	void render() override
	{
		std::cout << "FPS : " << getFPS() << std::endl;
		defaultLayer->render();
	}
};
