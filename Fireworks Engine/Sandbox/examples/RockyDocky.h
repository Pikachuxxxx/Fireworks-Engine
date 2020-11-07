#include <fireworks.h>

using namespace fireworks;

#include "../test/EditorGUI.h"

#define MAX_PLATFORMS 20
// Forward Declarations
void ImGuiEnableDocking(bool* p_open);

class RockyDocky : public Fireworks, public EditorGUI
{
private:
	Window*			window;
	Camera2D*		camera;
	Layer*			defaultLayer;
	Layer*			platformLayer;
	Layer*			playerLayer;

	Label*			fpsLabel;
	RigidBody2D*	rockyRB;
	RigidBody2D*	platformRBs[MAX_PLATFORMS];
    Sprite*         platforms[MAX_PLATFORMS];
	Sprite*			rocky;

	float			playerVelocity;
	float			jumpImpulse;
	float			jumpTime;
	float			currentJumpTime;
	Timer*			timer;
private:
	friend void ImGuiEnableDocking(bool* p_open);
public:
	RockyDocky() : playerVelocity(0.4f), jumpImpulse(3.0f), jumpTime(15.0f), currentJumpTime(0.0f), EditorGUI()
	{
		window = createWindow(" Example", 800, 600);
		window->backgroundColor = vec4(0.2, 0.2, 0.2, 1.0);
		camera = new Camera2D(mat4::orthographic(-160.0f, 160.0f, -120.0f, 120.0f, -1.0f, 1.0f));
		InitGUI(window);

#if(_WIN32)
		Shader* basicShader = new Shader(".\\shaders\\basic.vert", ".\\shaders\\basic.frag");
		Shader* playerShader = new Shader(".\\shaders\\basic.vert", ".\\shaders\\basic.frag");
		Shader* sickShader = new Shader(".\\shaders\\basic.vert", ".\\shaders\\sick.frag");
		Texture* bgTex = new Texture(".\\resources\\rockydocky\\bg.png");

		Texture* idleTex = new Texture(".\\resources\\rockydocky\\idle.png");
		Texture* jumpTex = new Texture(".\\resources\\rockydocky\\jump.png");
		Texture* platformTexture = new Texture(".\\resources\\rockydocky\\Design 2r.png");

		Font* font = new Font(".\\resources\\fonts\\SpaceQuest.ttf", 24);
#elif(__APPLE__)
        Shader* basicShader = new Shader("./shaders/basic.vert", "./shaders/basic.frag");
        Shader* playerShader = new Shader("./shaders/basic.vert", "./shaders/basic.frag");
        Shader* sickShader = new Shader("./shaders/basic.vert", "./shaders/sick.frag");

        Texture* bgTex = new Texture("./resources/rockydocky/bg.png");
		Texture* idleTex = new Texture("./resources/rockydocky/idle.png");
		Texture* jumpTex = new Texture("./resources/rockydocky/jump.png");
		Texture* platformTexture = new Texture("./resources/rockydocky/Design 2r.png");

		Font* font = new Font("./resources/fonts/SpaceQuest.ttf", 24);
#endif

		InstanceRenderer2D* instancer = new InstanceRenderer2D(camera);
		BatchRenderer2D* batcher = new BatchRenderer2D(camera, basicShader);
		BatchRenderer2D* platform_batcher = new BatchRenderer2D(camera, sickShader);

		defaultLayer = new Layer(batcher);
		platformLayer = new Layer(platform_batcher);
		playerLayer = new Layer(instancer);

		Sprite* bg = new Sprite(vec3(0, 0, 0), vec2(600, 260), bgTex);
		rocky = new Sprite(vec3(-20, 40, 0), vec2(20, 20), playerShader, idleTex, vec2(2, 1));
		rockyRB = new RigidBody2D(1.0f, 0.2f, RigidBodyType::Dynamic);
		rockyRB->gravityScale = 0.1f;
		rockyRB->fixedRotation = true;
		rocky->AddComponent<RigidBody2D>(rockyRB);

		vec3 platformsPositions[MAX_PLATFORMS] = {
			   vec3(-30, -60, 0),
			   vec3(50,  -40, 0),
			   vec3(120, -20, 0),
			   vec3(200, -50, 0),
			   vec3(250, -20, 0),
			   vec3(320,  20, 0),
			   vec3(380, -10, 0),


			   vec3(550, -20, 0),
			   vec3(510,   0, 0),
			   vec3(540,  20, 0)
		};

		for (int i = 0; i < MAX_PLATFORMS / 2; i++)
		{
			platforms[i] = new Sprite(platformsPositions[i], vec2(80, 10), platformTexture);
			platformRBs[i] = new RigidBody2D(1.0f, 0.2f, RigidBodyType::Static);
			platformRBs[i]->gravityScale = 0;
			platformRBs[i]->fixedRotation = true;
			platforms[i]->AddComponent<RigidBody2D>(platformRBs[i]);
			platformLayer->add(platforms[i]);
		}

		defaultLayer->add(bg);
		playerLayer->add(rocky);

		fpsLabel = new Label(" ", vec3(20, 550, 0.5), vec3(1, 1, 1), *font);
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

	}

	// Runs 60 times per second
	void update() override
	{

	}

	// Runs as fast as possible
	void render() override
	{
		camera->setPosition(vec3(rockyRB->GetPositionInPixels().x, 0, 0) + vec3(-2.0f, 0.0f, 0.0f));

		fpsLabel->renderText();
		fpsLabel->text = "FPS : " + std::to_string(getFPS());
		rocky->animateSprite(6, SpriteAnimationType::LOOP);
		movePlayer();
		jump();
		platformLayer->render();
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
		}
		ImGui::End();
	}

	void movePlayer()
	{
		if (window->isKeyHeld(Keys::RIGHT))
		{
			rockyRB->SetVelocity(maths::vec2(playerVelocity, rockyRB->GetBody()->GetLinearVelocity().y));
			rocky->flipX();
		}
		else if (window->isKeyHeld(Keys::LEFT))
		{
			rockyRB->SetVelocity(maths::vec2(-playerVelocity, rockyRB->GetBody()->GetLinearVelocity().y));
			rocky->unflipX();
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
};
