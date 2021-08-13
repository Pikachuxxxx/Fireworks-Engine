#include <fireworks.h>

using namespace fireworks;

class PhyTest : public Fireworks
{
private:
	Window* window;
	Camera2D* camera;
	Layer* layer;
	RigidBody2D* rb;
	Sprite* sprite;
public:
	PhyTest()
	{
		window = createWindow("Physics Test", 1000, 600);
		camera = new Camera2D(ortho(-125.0f, 125.0f, -75.0f, 75.0f, -1.0f, 1.0f));
		Shader* basicShader = new Shader(".\\shaders\\basic.vert", ".\\shaders\\basic.frag");
		ShotRenderer2D* instancer = new ShotRenderer2D(camera);

		layer = new Layer(instancer);
		sprite = new Sprite(vec3(5, 80, 0), vec2(20, 20), vec4(1, 1, 0, 1), basicShader);
   		rb = new RigidBody2D(1.0f, 0.1f, Dynamic);
		sprite->AddComponent<RigidBody2D>(rb);

		Sprite* plank = new Sprite(vec3(40, -60, 0), vec2(120, 10), vec4(1, 0, 0, 1), basicShader);
		RigidBody2D* plankRB = new RigidBody2D(1.0f, 0.1f, Static);
		plank->AddComponent<RigidBody2D>(plankRB);

		Sprite* box = new Sprite(vec3(10, 80, 0), vec2(20, 20), vec4(0, 0, 1, 1), basicShader, Primitive2D::Triangle);
		RigidBody2D* boxRB = new RigidBody2D(1.0f, 0.1, Dynamic);
		box->AddComponent<RigidBody2D>(boxRB);

		Sprite* greenBox = new Sprite(vec3(40, -50, 0), vec2(20, 20), vec4(0, 1, 0, 1), basicShader);
		RigidBody2D* greenboxRB = new RigidBody2D(1.0f, 0.1, Dynamic);
		greenBox->AddComponent<RigidBody2D>(greenboxRB);
			
		layer->add(sprite);
		layer->add(plank);
		layer->add(box);
		layer->add(greenBox);
	}

	~PhyTest()
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
		
	}

	// Runs as fast as possible
	void render() override
	{

		if (window->isKeyHeld(GLFW_KEY_SPACE))
			rb->AddForce(vec2(0, 3), 1.3f);
		if (window->isKeyHeld(GLFW_KEY_RIGHT))
			rb->SetVelocity(vec2(0.2, 0));
		if (window->isKeyHeld(GLFW_KEY_LEFT))
			rb->SetVelocity(vec2(-1, 0));
		layer->render();
 	}
};

