#include <fireworks.h>

using namespace fireworks;

#include "../test/EditorGUI.h"

#define MAX_PLATFORMS 20
#define MAX_SLURPS 4

// Forward Declarations
void ImGuiEnableDocking(bool* p_open);

class RockyDocky : public Fireworks, public EditorGUI
{
private:
	Window*							window;
	Camera2D*						camera;
	Layer*							defaultLayer;
	Layer*							platformLayer;
	Layer*							playerLayer;
	Layer*							slurpsLayer;
	Label*							fpsLabel;
	Label*							colorLeftLbl;
	Label*							gameStatusLbl;
	RigidBody2D*					rockyRB;
	RigidBody2D*					platformRBs[MAX_PLATFORMS];
	Sprite*							rocky;
    Sprite*							platforms[MAX_PLATFORMS];
	std::vector<Sprite*>			slurps;
	Shader*							playerShader;
	float							colorLeft;
	int								slurpscount;
	float							playerVelocity;
	float							jumpImpulse;
	float							jumpTime;
	float							currentJumpTime;
	bool							cameraPanMode;
	bool							isGamePaused;
	bool							gameOver;
	bool							didWin;
	bool							isDead;
	Timer*							timer;
private:
	friend void ImGuiEnableDocking(bool* p_open);
public:
	RockyDocky() : playerVelocity(0.4f), jumpImpulse(3.0f), jumpTime(15.0f), currentJumpTime(0.0f), EditorGUI(), cameraPanMode(false), colorLeft(100), slurpscount(0), isGamePaused(false), isDead(false), didWin(false), gameOver(false)
	{
		window = createWindow("Physics Example", 800, 600);
		window->backgroundColor = vec4(0.2, 0.2, 0.2, 1.0);
		camera = new Camera2D(mat4::orthographic(-160.0f, 160.0f, -120.0f, 120.0f, -1.0f, 1.0f));
		InitGUI(window);

#if(_WIN32)
		Shader* basicShader = new Shader(".\\shaders\\basic.vert", ".\\shaders\\basic.frag");
		playerShader = new Shader(".\\shaders\\basic.vert", ".\\shaders\\fade.frag");
		Shader* sickShader = new Shader(".\\shaders\\basic.vert", ".\\shaders\\sick.frag");
		Texture* bgTex = new Texture(".\\resources\\rockydocky\\bg.png");
		Texture* bg2Tex = new Texture(".\\resources\\rockydocky\\bg2.png");
		Texture* bg3Tex = new Texture(".\\resources\\rockydocky\\bg3.png");

		Texture* idleTex = new Texture(".\\resources\\rockydocky\\idle.png");
		Texture* jumpTex = new Texture(".\\resources\\rockydocky\\jump.png");
		Texture* rockyTex = new Texture(".\\resources\\rockydocky\\Rocky.png");
		Texture* platformTexture = new Texture(".\\resources\\rockydocky\\Design 2r.png");
		Texture* slurpTexture = new Texture(".\\resources\\rockydocky\\slurp.png");

		Font* font = new Font(".\\resources\\fonts\\SpaceQuest.ttf", 24);
		Font* fontBig = new Font(".\\resources\\fonts\\SpaceQuest.ttf", 36);
#elif(__APPLE__)
        Shader* basicShader = new Shader("./shaders/basic.vert", "./shaders/basic.frag");
        playerShader = new Shader("./shaders/basic.vert", "./shaders/fade.frag");
        Shader* sickShader = new Shader("./shaders/basic.vert", "./shaders/sick.frag");

		Texture* bgTex = new Texture("./resources/rockydocky/bg.png");
		Texture* bg2Tex = new Texture("./resources/rockydocky/bg2.png");
		Texture* bg3Tex = new Texture("./resources/rockydocky/bg3.png");
		Texture* idleTex = new Texture("./resources/rockydocky/idle.png");
		Texture* jumpTex = new Texture("./resources/rockydocky/jump.png");
		Texture* rockyTex = new Texture("./resources/rockydocky/Rocky.png");
		Texture* platformTexture = new Texture("./resources/rockydocky/Design 2r.png");
		Texture* slurpTexture = new Texture("./resources/rockydocky/slurp.png");

		Font* font = new Font("./resources/fonts/SpaceQuest.ttf", 24);
		Font* fontBig = new Font("./resources/fonts/SpaceQuest.ttf", 36);
#endif

		ShotRenderer2D* instancer = new ShotRenderer2D(camera);
		BatchRenderer2D* batcher = new BatchRenderer2D(camera, basicShader);
		BatchRenderer2D* platform_batcher = new BatchRenderer2D(camera, sickShader);

		defaultLayer = new Layer(batcher);
		slurpsLayer = new Layer(batcher);
		platformLayer = new Layer(platform_batcher);
		playerLayer = new Layer(instancer);

		Sprite* bg = new Sprite(vec3(0, 0, 0), vec2(600, 260), bgTex);
		Sprite* bg2 = new Sprite(vec3(600, 0, 0), vec2(800, 260), bg2Tex);
		Sprite* bg3 = new Sprite(vec3(1400, 0, 0), vec2(800, 260), bg3Tex);
		rocky = new Sprite(vec3(-20, 40, 0), vec2(15, 15), playerShader, rockyTex);
		rockyRB = new RigidBody2D(0.7f, 0.2f, RigidBodyType::Dynamic);
		rockyRB->gravityScale = 0.1f;
		rockyRB->fixedRotation = true;
		rocky->AddComponent<RigidBody2D>(rockyRB);

		vec3 platformsPositions[MAX_PLATFORMS] = {
			   vec3(-30, -60, 0),
			   vec3(90,  -40, 0),
			   vec3(200, -20, 0),
			   vec3(300, -50, 0),
			   vec3(390, -20, 0),
			   vec3(480,  20, 0),
			   vec3(580, -10, 0),
			   vec3(660, -40, 0),
			   vec3(740,   0, 0),
			   vec3(810,  40, 0),
			   vec3(940, -60, 0),
			   vec3(1060,-40, 0),
			   vec3(1120,  0, 0),
			   vec3(1190,-30, 0),
			   vec3(1310,-20, 0),
			   vec3(1360, 20, 0),
			   vec3(1430,-10, 0),
			   vec3(1510,-40, 0),
			   vec3(1560,  0, 0),
			   vec3(1610, 40, 0)
		};

		vec3 slurpPositions[MAX_SLURPS] = {
				vec3(300, -30, 0),
				vec3(660, -20, 0),
				vec3(1060,-20, 0),
				vec3(1610, 60, 0)
		};

		for (int i = 0; i < MAX_PLATFORMS; i++)
		{
			platforms[i] = new Sprite(platformsPositions[i], vec2(80, 10), platformTexture);
			platformRBs[i] = new RigidBody2D(1.0f, 0.2f, RigidBodyType::Static);
			platformRBs[i]->gravityScale = 0;
			platformRBs[i]->fixedRotation = true;
			platforms[i]->AddComponent<RigidBody2D>(platformRBs[i]);
			platformLayer->add(platforms[i]);
		}

		for (int i = 0; i < MAX_SLURPS; i++)
		{
			slurps.push_back(new Sprite(slurpPositions[i], vec2(10, 20), slurpTexture));
			slurpsLayer->add(slurps[i]);
		}


		defaultLayer->add(bg);


		defaultLayer->add(bg2);
		defaultLayer->add(bg3);
		playerLayer->add(rocky);

		fpsLabel = new Label(" ", vec3(20, 550, 0.5), vec3(1, 1, 1), *font);
		colorLeftLbl = new Label("", vec3(20, 500, 0.6), vec3(0, 1, 1), *fontBig);
		gameStatusLbl = new Label("", vec3(320, 300, 0.7), vec3(0, 0, 0), *fontBig);
		timer = new Timer();
	}

	~RockyDocky()
	{
		delete defaultLayer;
		delete platformLayer;
		delete playerLayer;
		delete timer;
	}

	// Runs once per initialization
	void init() override
	{

	}

	// Runs once per second
	void tick() override
	{
		if(!isGamePaused || !gameOver)
			colorLeft -= 5.0f;
	}

	// Runs 60 times per second
	void update() override
	{

	}

	// Runs as fast as possible
	void render() override
	{
		if (window->isKeyPressed(Keys::P))
			isGamePaused = !isGamePaused;

		if (isGamePaused)
		{
			gameStatusLbl->renderText();
			gameStatusLbl->text = "Paused";
			return;
		}
		else if(gameOver)
		{
			gameStatusLbl->renderText();
			gameStatusLbl->text = "Game Over!";
			return;
		}
		else if(didWin)
		{
			gameStatusLbl->renderText();
			gameStatusLbl->text = "You Win!";
			return;
		}
		else if(isDead)
		{
			gameStatusLbl->renderText();
			gameStatusLbl->text = "You Died";
			return;
		}

		if (colorLeft <= 0)
			gameOver = true;

		if (slurpscount == 4)
			didWin = true;

		if (rocky->position.y < -200)
			isDead = true;

		static float camera_position = 0;

		playerShader->setUniform1f("mixPercentage", 1.0f - (colorLeft / 100.0f));

		if (cameraPanMode)
		{
			if (window->isKeyHeld(Keys::RIGHT))
			{
				camera_position += 0.5f;
				camera->setPosition(vec3(camera_position, 0, 0));
			}
			else if (window->isKeyHeld(Keys::LEFT))
			{
				camera_position -= 0.5f;
				camera->setPosition(vec3(camera_position, 0, 0));
			}
		}
		else
		{
			camera->setPosition(vec3(rocky->position.x, 0, 0) + vec3(-2.0f, 0.0f, 0.0f));
			movePlayer();
		}

		checkCollisionsWithSlurps();

		fpsLabel->renderText();
		fpsLabel->text = "FPS : " + std::to_string(getFPS());
		colorLeftLbl->renderText();
		colorLeftLbl->text = "Color Left : " + std::to_string((int)colorLeft);
		jump();
		platformLayer->render();
		slurpsLayer->render();
		playerLayer->render();
		defaultLayer->render();

		InitRenderingGUI();
	}

	void RenderGUI()
	{
		ImGui::Begin("Inspector");
		{
			ImGui::DragFloat("Jump Velocity", &jumpImpulse);
			ImGui::DragFloat("Jump time", &jumpTime);
			ImGui::DragFloat("Player Speed", &playerVelocity);
			ImGui::Text("Player velocity (Y) : %4.2f", &rockyRB->GetBody()->GetLinearVelocity().y);
			ImGui::Text("Player Position (Y) : %4.2f", &rocky->position.y);
			ImGui::Checkbox("Camera Fly Mode", &cameraPanMode);
		}
		ImGui::End();
	}

	void movePlayer()
	{
		if (window->isKeyHeld(Keys::RIGHT))
		{
			rockyRB->SetVelocity(maths::vec2(playerVelocity, rockyRB->GetBody()->GetLinearVelocity().y));
			rocky->unflipX();
		}
		else if (window->isKeyHeld(Keys::LEFT))
		{
			rockyRB->SetVelocity(maths::vec2(-playerVelocity, rockyRB->GetBody()->GetLinearVelocity().y));
			rocky->flipX();
		}
	}

	void jump()
	{
        if (window->isKeyHeld(Keys::SPACE) && currentJumpTime < jumpTime)
		{
			rockyRB->SetVelocity(maths::vec2(0, jumpImpulse));
			currentJumpTime += timer->deltaTime() * 0.5;
		}
		if (rockyRB->GetBody()->GetLinearVelocity().y == 0 && window->isKeyReleased(Keys::SPACE))
			currentJumpTime = 0;
	}

	void checkCollisionsWithSlurps()
	{
		std::int32_t idx = -1;
		for (int i = 0; i < slurps.size(); i++)
		{
			if (OnCollisionEnter(*rocky, *slurps[i]))
			{
				colorLeft += 20;
				slurpscount++;
				idx = i;
				break;
			}
		}
		if (idx >= 0)
		{
			slurps.erase(slurps.begin() + idx);
 			slurpsLayer->m_Renderables.erase(slurpsLayer->m_Renderables.begin() + idx);
			idx = -1;
		}
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
