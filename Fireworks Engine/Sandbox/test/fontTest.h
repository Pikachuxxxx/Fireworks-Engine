#include <fireworks.h>

using namespace fireworks;

class FontTest : public Fireworks
{
private:
	Window* window;
	Shader* fontShader;
	Label* lbl;
	Label* fpsLabel;
	Label* randomText;

public:
	FontTest()
	{
		window = createWindow(" Example", 800, 600);
	}

	~FontTest()
	{
	}

	// Runs once per initialization
	void init() override
	{
		Font font(".\\resources\\fonts\\FiraCode-Light.ttf", 20);
		Font chinese_font(".\\resources\\fonts\\chinese-font-light.TTF", 20);

		lbl = new Label("中", vec3(25, 25, 0), vec3(1, 0, 0), chinese_font);
		fpsLabel = new Label("FPS : ", vec3(25, 500, 0), vec3(1, 1, 1), font);
		randomText = new Label("Random Text!! @@ ## $$ ^^ && () ** 9823692863410", vec3(20, 200, 0), vec3(0, 1, 1), font);
	}

	// Runs once per second
	void tick() override
	{

	}

	// Runs 60 times per second
	void update() override
	{
		fpsLabel->text = "FPS : " + std::to_string(getFPS());
		
	}

	// Runs as fast as possible
	void render() override
	{
		glClearColor((float)243 / 255, (float)146 / 255, (float)51 / 255, 1.0f);

		lbl->renderText();
		fpsLabel->renderText();
		randomText->renderText();
	}
};
