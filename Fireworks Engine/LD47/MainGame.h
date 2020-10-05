#pragma once

#include <string>
#include <chrono>
#include <thread>

#include "src/AABBCollisionManager.h"
#include <fireworks.h>
using namespace fireworks;

#define SIDE_WALL_COUNT 2
#define HORIZONTAL_WALL_COUNT 4
enum PlayerState
{
	IDLE, 
	FORWARD, 
	BACK,
	LEFT, 
	RIGHT
};
class MainGame : public Fireworks
{
private:
	Window*					window;
	Shader*					defaultShader;
	Layer*					defaultLayer;
	AABBCollisionManager	collisionManager;

	Texture*		playerIdle;
	Texture*		playerRight;
	Texture*		playerLeft;
	Texture*		playerForward;
	Texture*		playerBack;
	Texture*		ground;
	Texture*		sideWall;
	Texture*		topWall;

	Sprite*			playerSprite;
	Sprite*			goundSprite;
	Sprite*			leftWall[SIDE_WALL_COUNT];
	Sprite*			rightWall[SIDE_WALL_COUNT];
	Sprite*			upWall[HORIZONTAL_WALL_COUNT];
	Sprite*			downWall[HORIZONTAL_WALL_COUNT];

	PlayerState		playerState;
	Timer			timer;
	float 			speed;
	float			idleAnimFrameRate;
	float			currentTime;
	int				currentFrame;
	bool			shouldMoveLeft;
	bool			shouldMoveRight;
	bool			shouldMoveUp;
	bool			shouldMoveDown;

public:
	MainGame() : speed(4.0f), idleAnimFrameRate(0.8f), currentTime(0.0f), currentFrame(0), playerState(PlayerState::IDLE), shouldMoveLeft(true), shouldMoveRight(true), shouldMoveUp(true), shouldMoveDown(true)
	{
		window = createWindow("Main Game", 1200, 800);
		defaultShader	= new Shader(".\\shaders\\basic.vert", ".\\shaders\\basic.frag");
		defaultLayer	= new Layer(new BatchRenderer2D(), defaultShader, mat4::orthographic(-12.0f, 12.0f, -8.0f, 8.0f, -1.0f, 1.0f));

		playerIdle		= new Texture(".\\res\\Sprites\\Player\\drake_idle.png");
		playerRight		= new Texture(".\\res\\Sprites\\Player\\drake_walk_cycle_right.png");
		playerLeft		= new Texture(".\\res\\Sprites\\Player\\drake_walk_cycle_left.png");
		playerForward	= new Texture(".\\res\\Sprites\\Player\\drake_walk_cycle_forward.png");
		playerBack		= new Texture(".\\res\\Sprites\\Player\\drake_walk_cycle_back.png");

		sideWall		= new Texture(".\\res\\Sprites\\Environment\\side_wall.png");
		topWall			= new Texture(".\\res\\Sprites\\Environment\\back_wall.png");
		ground			= new Texture(".\\res\\Sprites\\Environment\\bg_design.png");
		
		playerSprite	= new Sprite(0.0f, 0.0f, 0.8f, 2.2f, playerIdle, 0, 2);
		goundSprite		= new Sprite(-12, -8, 24, 16, ground);

		for (int i = 0; i < SIDE_WALL_COUNT; i++)
		{
			leftWall[i] = new Sprite(-12.0f, -0.0f - i * 4.0f, 1.0f, 4.0f, sideWall);
			rightWall[i] = new Sprite(11.0f, -0.0f - i * 4.0f, 1.0f, 4.0f, sideWall);
		}

		for (int i = 0; i < HORIZONTAL_WALL_COUNT; i++)
		{
			upWall[i] = new Sprite(-12.0f + 6.0f * i, 4.0f, 6.0f, 4.0f, topWall);
			downWall[i] = new Sprite(-12.0f + 6.0f * i, -8.0f, 6.0f, 4.0f, topWall);
		}


	}

	~MainGame()  
	{
		delete defaultLayer;
		delete defaultShader;

		// FIXME: Delete all the texture objects
	}

	// Runs once per initialization
	void init() override
	{
		// b : 835
		glClearColor(0.890f, 0.863f, 0.8350f, 1.0f); // 0xe3dcd5 

		for (int i = 0; i < SIDE_WALL_COUNT; i++)
		{
			defaultLayer->add(leftWall[i]);
			defaultLayer->add(rightWall[i]);
		}
		for (int i = 0; i < HORIZONTAL_WALL_COUNT; i++)
		{
			defaultLayer->add(upWall[i]);
			defaultLayer->add(downWall[i]);
		}

		defaultLayer->add(playerSprite);
		defaultLayer->add(goundSprite);
	}
	       
	// Runs once per second
	void tick() override
	{
		if (shouldMoveLeft)
		{
			for (int i = 0; i < SIDE_WALL_COUNT; i++)
			{
				leftWall[i]->position.x += 1.0f;
			}
		}
		else
		{
			for (int i = 0; i < SIDE_WALL_COUNT; i++)
			{
				leftWall[i]->position.x -= 1.0f;
			}
		}
		if (shouldMoveRight)
		{
			for (int i = 0; i < SIDE_WALL_COUNT; i++)
			{
				rightWall[i]->position.x -= 1.0f;
			}
		}
		else
		{
			for (int i = 0; i < SIDE_WALL_COUNT; i++)
			{
				rightWall[i]->position.x += 1.0f;
			}
		}
		//-------------------------------------------------------
		if (shouldMoveUp)
		{
			for (int i = 0; i < HORIZONTAL_WALL_COUNT; i++)
			{
				upWall[i]->position.y -= 1.0f;
			}
		}
		else
		{
			for (int i = 0; i < HORIZONTAL_WALL_COUNT; i++)
			{
				upWall[i]->position.y += 1.0f;
			}
		}
		if (shouldMoveDown)
		{
			for (int i = 0; i < HORIZONTAL_WALL_COUNT; i++)
			{
				downWall[i]->position.y += 1.0f;
			}
		}
		else
		{
			for (int i = 0; i < HORIZONTAL_WALL_COUNT; i++)
			{
				downWall[i]->position.y -= 1.0f;
			}
		}

	}

	// Runs 60 times per second
	void update() override
	{
		playerSprite->m_Texture = playerIdle;
		playerSprite->totalFrames = 2;
		playerState = PlayerState::IDLE;


		if (window->isKeyPressed(GLFW_KEY_UP) && shouldMoveUp)
		{
			playerSprite->position.y += 0.02f * speed;
			playerSprite->m_Texture = playerForward;
			playerSprite->totalFrames = 2;
			playerState = PlayerState::FORWARD;
		}
		else if (window->isKeyPressed(GLFW_KEY_DOWN) && shouldMoveDown)
		{
			playerSprite->position.y -= 0.02f * speed;
			playerSprite->m_Texture = playerBack;
			playerSprite->totalFrames = 2;
			playerState = PlayerState::BACK;
		}
		if (window->isKeyPressed(GLFW_KEY_RIGHT) && shouldMoveRight)
		{
			playerSprite->position.x += 0.02f * speed;
			playerSprite->m_Texture = playerRight;
			playerSprite->totalFrames = 3;
			playerState = PlayerState::RIGHT;
		}
		else if (window->isKeyPressed(GLFW_KEY_LEFT) && shouldMoveLeft)
		{
			playerSprite->position.x -= 0.02f * speed;
			playerSprite->m_Texture = playerLeft;
			playerSprite->totalFrames = 3;
			playerState = PlayerState::LEFT;
		}

		if (currentTime > idleAnimFrameRate)
		{
			if (playerState == PlayerState::IDLE || playerState == PlayerState::FORWARD || playerState == PlayerState::BACK)
			{
				playerSprite->sprframe = !playerSprite->sprframe;
			}
			if((playerState == PlayerState::LEFT || playerState == PlayerState::RIGHT) && currentFrame < 6)
			{
				playerSprite->sprframe = currentFrame;
				currentFrame++;
			}
			else
			{
				currentFrame = 0;
			}
			currentTime = 0.0f;
			timer.reset();
		}
		currentTime += timer.elapsed();
	}

	// Runs as fast as possible
	void render() override
	{
		//std::cout << "FPS : " << getFPS() << std::endl;
		// Collision check
		bool leftColl = false;
		bool rightColl = false;
		bool upColl = false;
		bool downColl = false;
		for (int i = 0; i < SIDE_WALL_COUNT; i++)
		{
			leftColl |= collisionManager.CheckCollision(*leftWall[i], *playerSprite);
		}
		for (int i = 0; i < SIDE_WALL_COUNT; i++)
		{
			rightColl |= collisionManager.CheckCollision(*rightWall[i], *playerSprite);
		}
		for (int i = 0; i < HORIZONTAL_WALL_COUNT; i++)
		{
			upColl |= collisionManager.CheckCollision(*upWall[i], *playerSprite);
		}
		for (int i = 0; i < HORIZONTAL_WALL_COUNT; i++)
		{
			downColl |= collisionManager.CheckCollision(*downWall[i], *playerSprite);
		}

		shouldMoveLeft = true;
		shouldMoveRight = true;
		shouldMoveUp = true;
		shouldMoveDown = true;

		if (leftColl)
			shouldMoveLeft = false;
		if (rightColl)
			shouldMoveRight = false;
		if (upColl)
			shouldMoveUp = false;
		if (downColl)
			shouldMoveDown = false;



		std::string fps = "FPS : " + std::to_string(getFPS());
		defaultLayer->m_Renderer->drawString(fps, vec3(1, 1, 0), vec4(1, 1, 1, 1), 2);

		if ((rightColl && leftColl) || (upColl && downColl))
		{
			std::cout << "Dead!!!" << std::endl;
			defaultLayer->m_Renderer->drawString("Dead !!!", vec3(250, 350, 0), vec4(1, 0.1, 0.1, 1), 7);
		}
		defaultLayer->render();

	}
};
