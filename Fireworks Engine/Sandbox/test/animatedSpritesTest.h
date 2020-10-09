#include <fireworks.h>

using namespace fireworks;

class AnimSprites : public Fireworks
{
private:
	Window*		window;
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
		defaultLayer =	new Layer(new BatchRenderer2D(), 
						new Shader(	".\\shaders\\basic.vert", 
									".\\shaders\\basic.frag"),
						mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f));

		piggySpriteSheet = new Texture(".\\resources\\piggy_spritesheet.png");
		piggy = new Sprite(vec3(8.0f, 4.0f, 0.0f), vec2(2.0f, 2.0f), piggySpriteSheet, vec2(12, 1));
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
		piggy->animateSprite(8, graphics::SpriteAnimationType::PING_PONG);

		defaultLayer->render();
	}
};

