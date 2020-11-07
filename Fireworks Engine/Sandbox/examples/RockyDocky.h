#include <fireworks.h>

using namespace fireworks;

#include "../test/EditorGUI.h"

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
	RigidBody2D*	platformRB;
	Sprite*			rocky;

	float			playerVelocity;
	float			jumpImpulse;
	float			jumpTime;
	float			currentJumpTime;
	Timer*			timer;
private:
	friend void ImGuiEnableDocking(bool* p_open);
public:
	RockyDocky() : playerVelocity(3.4f), jumpImpulse(30.0f), jumpTime(50.0f), currentJumpTime(0.0f), EditorGUI()
	{
		window = createWindow(" Example", 800, 600);
		camera = new Camera2D(mat4::orthographic(-160.0f, 160.0f, -120.0f, 120.0f, -1.0f, 1.0f));
		InitGUI(window);
#if(_WIN32)
		Shader* basicShader = new Shader(".\\shaders\\basic.vert", ".\\shaders\\basic.frag");
		Shader* playerShader = new Shader(".\\shaders\\basic.vert", ".\\shaders\\basic.frag");
		Shader* sickShader = new Shader(".\\shaders\\basic.vert", ".\\shaders\\sick.frag");


		InstanceRenderer2D* instancer = new InstanceRenderer2D(camera);
		BatchRenderer2D* batcher = new BatchRenderer2D(camera, basicShader);
		BatchRenderer2D* platform_batcher = new BatchRenderer2D(camera, sickShader);

		defaultLayer = new Layer(batcher);
		platformLayer = new Layer(platform_batcher);
		playerLayer = new Layer(instancer);

		Texture* bgTex = new Texture(".\\resources\\rockydocky\\bg.png");
		Sprite* bg = new Sprite(vec3(0, 0, 0), vec2(400, 260), bgTex);

		Texture* idleTex = new Texture(".\\resources\\rockydocky\\idle.png");
		Texture* jumpTex= new Texture(".\\resources\\rockydocky\\jump.png");
		rocky = new Sprite(vec3(-20, 40, 0), vec2(20, 20), playerShader, idleTex, vec2(2, 1));
		rockyRB = new RigidBody2D(1.0f, 0.2f, RigidBodyType::Dynamic);
		rockyRB->gravityScale = 1.0f;
		rocky->AddComponent<RigidBody2D>(rockyRB);


		Texture* platformTexture = new Texture(".\\resources\\rockydocky\\Design 2r.png");
		Sprite* platform = new Sprite(vec3(-30, -60, 0), vec2(80, 10), platformTexture);
		platformRB = new RigidBody2D(1.0f, 0.2f, RigidBodyType::Static);
		platformRB->gravityScale = 0;
		platformRB->fixedRotation = true;
		platform->AddComponent<RigidBody2D>(platformRB);

		Font* font = new Font(".\\resources\\fonts\\SpaceQuest.ttf", 24);
		fpsLabel = new Label(" ", vec3(20, 550, 0.5), vec3(1, 1, 1), *font);
#elif(__APPLE__)
        Shader* basicShader = new Shader("./shaders/basic.vert", "./shaders/basic.frag");
        Shader* playerShader = new Shader("./shaders/basic.vert", "./shaders/basic.frag");
        Shader* sickShader = new Shader("./shaders/basic.vert", "./shaders/sick.frag");


        InstanceRenderer2D* instancer = new InstanceRenderer2D(camera);
        BatchRenderer2D* batcher = new BatchRenderer2D(camera, basicShader);
        BatchRenderer2D* platform_batcher = new BatchRenderer2D(camera, sickShader);

        defaultLayer = new Layer(batcher);
        platformLayer = new Layer(platform_batcher);
        playerLayer = new Layer(instancer);

        Texture* bgTex = new Texture("./resources/rockydocky/bg.png");
        Sprite* bg = new Sprite(vec3(0, 0, 0), vec2(400, 260), bgTex);

        Texture* idleTex = new Texture("./resources/rockydocky/idle.png");
        Texture* jumpTex= new Texture("./resources/rockydocky/jump.png");
        rocky = new Sprite(vec3(-20, 40, 0), vec2(20, 20), playerShader, idleTex, vec2(2, 1));
        rockyRB = new RigidBody2D(1.0f, 0.2f, RigidBodyType::Dynamic);
        rockyRB->gravityScale = 1.0f;
        rocky->AddComponent<RigidBody2D>(rockyRB);


        Texture* platformTexture = new Texture("./resources/rockydocky/Design 2r.png");
        Sprite* platform = new Sprite(vec3(-30, -60, 0), vec2(80, 10), platformTexture);
        platformRB = new RigidBody2D(1.0f, 0.2f, RigidBodyType::Static);
        platformRB->gravityScale = 0;
        platformRB->fixedRotation = true;
        platform->AddComponent<RigidBody2D>(platformRB);

        Font* font = new Font("./resources/fonts/SpaceQuest.ttf", 24);
        fpsLabel = new Label(" ", vec3(20, 550, 0.5), vec3(1, 1, 1), *font);

#endif


		defaultLayer->add(bg);
		playerLayer->add(rocky);
		platformLayer->add(platform);

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

		camera->setPosition(vec3(-2.0f, 0.0f, 0.0f));
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
		std::cout << "Current Jump Time is : " << currentJumpTime << " [Player Velocity is : " << vec2(rockyRB->GetBody()->GetLinearVelocity().x, rockyRB->GetBody()->GetLinearVelocity().y) << std::endl;
		if (window->isKeyHeld(Keys::SPACE) && currentJumpTime < jumpTime)
		{
			rockyRB->SetVelocity(maths::vec2(0, jumpImpulse * currentJumpTime * 0.02));
			currentJumpTime += timer->deltaTime() * 0.5;
		}
		if (rockyRB->GetBody()->GetLinearVelocity().y == 0 && window->isKeyReleased(Keys::SPACE))
			currentJumpTime = 0;
	}
};
