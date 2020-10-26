#include <fireworks.h>

using namespace fireworks;

class TextGuru : public Fireworks
{
private:
	Window* window;
	Label* helloLbl;
	Label* fpsLabel;
	Label* randomText;
	Label* colouredText;

public:
	TextGuru()
	{
		window = createWindow(" Example", 800, 600);
	}

	~TextGuru()
	{
	}

	// Runs once per initialization
	void init() override
	{
		Font font(".\\resources\\fonts\\FiraCode-Light.ttf", 24);
		Font fontBig(".\\resources\\fonts\\FiraCode-Light.ttf", 48);

		helloLbl = new Label("Hello World!", vec3(400, 300, 0), vec3(0, 0, 0), font);
		fpsLabel = new Label("FPS : ", vec3(25, 500, 0), vec3(1, 1, 1), font);
		randomText = new Label("Random Text!! @@ ## $$ ^^ && () ** 9823692863410", vec3(20, 200, 0), vec3(0.2, 0.6, 0.8), font);
		colouredText = new Label("Yeey Colors", vec3(200, 150, 0), vec3(0.8, 0.2, 0.88), fontBig);
	}

	// Runs once per second
	void tick() override
	{
	}

	// Runs 60 times per second
	void update() override
	{
		colouredText->color = vec3(getRandomValue(0, 255) / 255.0f, getRandomValue(0, 255) / 255.0f, getRandomValue(0, 255) / 255.0f);

	}

	// Runs as fast as possible
	void render() override
	{
		glClearColor((float)243 / 255, (float)146 / 255, (float)51 / 255, 1.0f);

		fpsLabel->text = "FPS : " + std::to_string(getFPS());
		helloLbl->position.x = 20 + (300 * abs(cos(glfwGetTime())));

		helloLbl->renderText();
		fpsLabel->renderText();
		randomText->renderText();
		colouredText->renderText();
	}
};

