#include <fireworks.h>

using namespace fireworks;

class Scene3DTest : public Fireworks
{
private:
    Window* window;
    Scene* scene;
    PerspectiveCamera* camera3D;
    Shader* meshShader;
public:
    Scene3DTest()
    {
        window = createWindow("3D Scene Testing", 800, 600);
        camera3D = new PerspectiveCamera();
        meshShader = new Shader(".\\shaders\\mesh.vert", ".\\shaders\\mesh.frag");
        BatchRenderer3D* batch3d = new BatchRenderer3D(camera3D, meshShader);
        scene = new Scene(batch3d);

        Transform cubeTransform(vec3(0, 0, -5), vec3(0, 45, -20), vec3(5, 2, 2));
        Renderable3D* cube = new Renderable3D(cubeTransform, vec4(1, 0, 0, 1), Primitive3D::Cube);

        scene->add(cube);
    }

    ~Scene3DTest()
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
        scene->render();
    }
};
