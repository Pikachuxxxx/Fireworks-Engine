#include <fireworks.h>

using namespace fireworks;

class AnimSprites : public Fireworks
{
private:
	Window*		window;
	Camera2D*	camera;
	Layer*		defaultLayer;
	Texture*	piggySpriteSheet; 
	Sprite*		piggy;
	Timer       timer;
	double		currentTime;
	double		targetTime;
public:
	AnimSprites()
		:currentTime(0.0), targetTime(4.0)
	{
		window = createWindow("Animated Sprites Test", 800, 600);
		camera = new Camera2D(mat4::orthographic(-8.0f, 8.0f, -6.0f, 6.0f, -1.0f, 1.0f));

		Shader* basicShader = new Shader(".\\shaders\\basic.vert", ".\\shaders\\basic.frag");
		BatchRenderer2D* batchRenderer = new BatchRenderer2D(camera, basicShader);

		defaultLayer = new Layer(batchRenderer);

		piggySpriteSheet = new Texture(".\\resources\\piggy_spritesheet.png");
		piggy = new Sprite(vec3(0.0f, 0.0f, 0.0f), vec2(2.0f, 2.0f), piggySpriteSheet, vec2(12, 1));
	}

	~AnimSprites()
	{
		delete defaultLayer;
	}

	// Runs once per initialization
	void init() override
	{
		defaultLayer->add(piggy);
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
		piggy->animateSprite(12, SpriteAnimationType::PING_PONG);

		defaultLayer->render();
	}
};

