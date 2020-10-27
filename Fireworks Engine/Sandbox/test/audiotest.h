#include <fireworks.h>

using namespace fireworks;

class AudioTest : public Fireworks
{
private:
	Window* window;
	AudioClip* zapclip;
	Label* clipState;
public:
	AudioTest()
	{
		window = createWindow(" Example", 800, 600);
		zapclip = new AudioClip(".\\resources\\sounds\\zap.wav");

		Font fontBig(".\\resources\\fonts\\FiraCode-Light.ttf", 28);
		clipState = new Label("Audio State : ", vec3(25, 500, 0), vec3(1, 1, 1), fontBig);
	}

	~AudioTest()
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
		glClearColor((float)243 / 255, (float)146 / 255, (float)51 / 255, 1.0f);

		zapclip->Loop();

		clipState->text = "State : " + std::string ((zapclip->isLooping() ? "looping" : "Not playing"));

		clipState->renderText();
	}
};

