#include <fireworks.h>

using namespace fireworks;

class RockyDocky : public Fireworks
{
private:
	Window*		window;
	Camera2D*	camera;
	Layer*		defaultLayer;
public:
	RockyDocky()
	{
		window = createWindow(" Example", 800, 600);
		camera = new Camera2D(mat4::orthographic())
	}

	~RockyDocky()
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

	}
};

