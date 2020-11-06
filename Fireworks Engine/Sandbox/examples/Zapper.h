#include <fireworks.h>

using namespace fireworks;

class Zapper : public Fireworks
{
private:
	Window*					window;
	Camera2D*				camera;
	Layer*					defaultLayer;

	AudioClip*				bgm;
	AudioClip*				shipshoot;
	AudioClip*				shipmove;
	AudioClip*				shiphit;
	AudioClip*				rockDestroy;
	Texture*				bulletTex;
	Texture*				rocksTex;
	std::vector<Sprite*>	bullets;
	std::vector<Sprite*>	rocks;
	Sprite*					spaceShip;

	float					spaceshipSpeed;
	float					gameoverTimer;
	float					shakefrequency;
	std::int32_t			playerScore;
	std::int32_t			playerHealth;
	Label*					gamenamelbl;
	Label*					FPSlbl;
	Label*					scorelbl;
	Label*					healthlbl;
	Label*					pauselbl;
	Label*					gameoverlbl;
	bool					isGameOver;
	bool					isGamePaused;
public:
	Zapper() : spaceshipSpeed(9.0f), playerScore(0), playerHealth(100), isGameOver(false), isGamePaused(false), gameoverTimer(0), shakefrequency(0.0f)
	{
		window = createWindow("Zapper", 600, 900);
		window->backgroundColor = vec4((float)243 / 255, (float)146 / 255, (float)51 / 255, 1.0f);
		camera = new Camera2D(mat4::orthographic(-12.0f, 12.0f, -18.0f, 18.0f, -1.0f, 1.0f));
#if(_WIN32)
		Shader* basicShader = new Shader(".\\shaders\\basic.vert", ".\\shaders\\basic.frag");

		bgm			= new AudioClip(".\\resources\\sounds\\bgm.wav");
		shipshoot	= new AudioClip(".\\resources\\sounds\\laser8.wav");
		shipmove	= new AudioClip(".\\resources\\sounds\\shipmove.wav");
		shiphit		= new AudioClip(".\\resources\\sounds\\shiphit.wav");
		rockDestroy = new AudioClip(".\\resources\\sounds\\rockdestroy.wav");

		Font fontBig(".\\resources\\fonts\\SpaceQuest.ttf", 40);
		Font font(".\\resources\\fonts\\SpaceQuest.ttf", 20);
		Font fontSmall(".\\resources\\fonts\\SpaceQuest.ttf", 12);

		Texture* shipTex	= new Texture(".\\resources\\spaceship.png");
		bulletTex			= new Texture(".\\resources\\test3.png");
		rocksTex			= new Texture(".\\resources\\asteroid.png");

#elif(__APPLE__)
        Shader* basicShader = new Shader("shaders/basic.vert", "shaders/basic.frag");

		bgm			= new AudioClip("resources/sounds/bgm.wav");
		shipshoot	= new AudioClip("resources/sounds/laser8.wav");
		shipmove	= new AudioClip("resources/sounds/shipmove.wav");
		shiphit		= new AudioClip("resources/sounds/shiphit.wav");
		rockDestroy = new AudioClip("resources/sounds/rockdestroy.wav");

		Font fontBig("resources/fonts/SpaceQuest.ttf", 40);
		Font font("resources/fonts/SpaceQuest.ttf", 20);
		Font fontSmall("resources/fonts/SpaceQuest.ttf", 12);

		Texture* shipTex	= new Texture("resources/spaceship.png");
		bulletTex			= new Texture("resources/test3.png");
		rocksTex			= new Texture("resources/asteroid.png");
#endif

        BatchRenderer2D* batchRenderer = new BatchRenderer2D(camera, basicShader);
        defaultLayer = new Layer(batchRenderer);

		spaceShip = new Sprite(vec3(-2, -10, 0), vec2(4, 4), shipTex);

		gamenamelbl = new Label("Zapper", vec3(150, 580, 0), vec3(0, 0, 0), font);
		FPSlbl		= new Label("", vec3(20, 580, 0), vec3(1, 1, 1), fontSmall);
		scorelbl	= new Label("", vec3(25, 550, 0), vec3((float)22 / 255, (float)151 / 255, (float)205 / 255), font);
		healthlbl	= new Label("", vec3(150, 520, 0), vec3((float)255 / 255, (float)82 / 255, (float)82 / 255), font);
		pauselbl	= new Label("Paused", vec3(130, 300, 0), vec3 (0, 0, 0), fontBig);
		gameoverlbl = new Label("Game Over!", vec3(90, 300, 0), vec3(1, 0.2, 0.2), fontBig);

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
		if (isGamePaused || isGameOver)
			return;
		spawnRocks();
	}

	// Runs 60 times per second
	void update() override
	{
		if (isGamePaused || isGameOver)
			return;

		if (playerScored())
			playerScore ++;
		playerDamage();
		spaceShipMovement();
		spaceShipShoot();
		moveRocks();
	}

	// Runs as fast as possible
	void render() override
	{
		if (playerHealth <= 0)
			isGameOver = true;

		if (isGameOver)
		{
			gameoverlbl->renderText();

			if (gameoverTimer > 15000)
				glfwSetWindowShouldClose(window->getGLFWwindow(), GLFW_TRUE);

			gameoverTimer += glfwGetTime();
			return;
		}

		defaultLayer->render();
		gamenamelbl->renderText();
		FPSlbl->renderText();
		scorelbl->renderText();
		healthlbl->renderText();
		FPSlbl->text = "FPS : " + std::to_string(getFPS());
		scorelbl->text = "Score : " + std::to_string(playerScore);
		healthlbl->text = "Player Health : " + std::to_string(playerHealth);
		bgm->Loop();

		if(isGamePaused)
			pauselbl->renderText();

		if (window->isKeyPressed(GLFW_KEY_SPACE))
		{
			isGamePaused = !isGamePaused;
		}

		cameraShake();
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
		{
			spaceShip->position.x += 0.02f * spaceshipSpeed;
			//shipmove->Loop();
		}
		else if (window->isKeyHeld(GLFW_KEY_LEFT))
			spaceShip->position.x -= 0.02f * spaceshipSpeed;
	}

	void spaceShipShoot()
	{
		// spaceship shoot
		if ((window->isKeyPressed(GLFW_KEY_UP) || window->isKeyPressed(GLFW_KEY_ENTER)) && !shipshoot->isPlaying())
		{
			shipshoot->PlayOnce();
			bullets.push_back(new Sprite(spaceShip->position + vec3(2, 0, 0), vec2(1, 1), bulletTex));
			defaultLayer->add(bullets[bullets.size() - 1]);
		}

		// Instantiate and delete bullets after going out of the bounds of the screen
		for (int i = 0; i < bullets.size(); i++)
		{
			bullets[i]->position.y += 2.0f;

			if (bullets[i]->position.y > 18)
			{
				for (int j = 0; j < defaultLayer->m_Renderables.size(); j++)
				{
					if (bullets[i] == defaultLayer->m_Renderables[j])
					{
						defaultLayer->m_Renderables.erase(defaultLayer->m_Renderables.begin() + j);
					}
				}
				bullets.erase(bullets.begin() + i);
			}
		}
	}

	void spawnRocks()
	{
		rocks.push_back(new Sprite(vec3(getRandomValue(-10, 10), 16, 0), vec2(2, 2), rocksTex));
		if (rocks.size() >= 0)
		{
			defaultLayer->add(rocks[rocks.size() - 1]);
		}
	}

	void moveRocks()
	{
		for (int i = 0; i < rocks.size(); i++)
		{
			rocks[i]->position.y -= 0.2f;

			if (rocks[i]->position.y < -18)
			{
				for (int j = 0; j < defaultLayer->m_Renderables.size(); j++)
				{
					if (rocks[i] == defaultLayer->m_Renderables[j])
					{
						defaultLayer->m_Renderables.erase(defaultLayer->m_Renderables.begin() + j);
					}
				}
				rocks.erase(rocks.begin() + i);
			}

		}
	}

	bool playerScored()
	{
		//  check the collision between the bullet and they rock and add score to the player
		for (int b = 0; b < bullets.size(); b++)
		{
			for (int r = 0; r < rocks.size(); r++)
			{
				if (!(rocks.size() > 0 && bullets.size() > 0))
					return false;

				if (OnCollisionEnter(*bullets[b], *rocks[r]))
				{
					rockDestroy->Play();
					// erase that bullet and rock upon collision
					for (int j = 0; j < defaultLayer->m_Renderables.size(); j++)
					{
						if (bullets[b] == defaultLayer->m_Renderables[j])
						{
							defaultLayer->m_Renderables.erase(defaultLayer->m_Renderables.begin() + j);
						}
					}
					for (int j = 0; j < defaultLayer->m_Renderables.size(); j++)
					{
						if (rocks[r] == defaultLayer->m_Renderables[j])
						{
							defaultLayer->m_Renderables.erase(defaultLayer->m_Renderables.begin() + j);
						}
					}

					bullets.erase(bullets.begin() + b);
					rocks.erase(rocks.begin() + r);

					return true;
				}
			}
		}
		return false;
	}

	void playerDamage()
	{
		for (int ro = 0; ro < rocks.size(); ro++)
		{
			if (OnCollisionEnter(*spaceShip, *rocks[ro]))
			{
				playerScore--;
				playerHealth -= 10;
				shakefrequency = 2000;
				shiphit->Play();
			}
		}
	}

	void cameraShake()
	{
		if(shakefrequency > 0)
		{
			camera->setPosition(vec3(getRandomValue(-20, 20) / 100.0f, 0, 0));
		}

		shakefrequency -= glfwGetTime();
	}

	bool OnCollisionEnter(Sprite& gameObject_1, Sprite& gameObject_2)
	{

 		static std::uint32_t o1 = 0;
		static std::uint32_t o2 = 0;


		if (o1 == gameObject_1.objectID && o2 == gameObject_2.objectID)
			return false;
		else
		{
			bool collisionX = gameObject_1.position.x + gameObject_1.size.x >= gameObject_2.position.x && gameObject_2.position.x + gameObject_2.size.x >= gameObject_1.position.x;
			bool collisionY = gameObject_1.position.y + gameObject_1.size.y >= gameObject_2.position.y && gameObject_2.position.y + gameObject_2.size.y >= gameObject_1.position.y;

			bool result = collisionX && collisionY;
			if (result)
			{
				o1 = gameObject_1.objectID;
				o2 = gameObject_2.objectID;
			}
			return result;
		}
	}
};
