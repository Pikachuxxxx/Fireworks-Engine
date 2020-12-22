#include <fireworks.h>

using namespace fireworks;

class Scene3DTest : public Fireworks
{
private:
    Window* window;
    Scene* scene;
    FreeFlyCamera* camera3D;
    Shader* meshShader;
    Label* fpsLabel;
    double deltaTime;
    bool firstMouse = true;
    double lastX = 400.0, lastY = 300.0;
public:
    Scene3DTest()
    {
        window = createWindow("3D Scene Testing", 800, 600);
        camera3D = new FreeFlyCamera(vec3(0, 0, -5));
        meshShader = new Shader(".\\shaders\\mesh.vert", ".\\shaders\\mesh.frag");
        BatchRenderer3D* batch3d = new BatchRenderer3D(camera3D, meshShader);
        scene = new Scene(batch3d);

        Transform cubeTransform(vec3(0, 0, 0), vec3(0, 45, -20), vec3(2, 2, 2));
        Transform planeTransfrom(vec3(0, -2, 0), vec3(0, 0, 0), vec3(15, 15, 2));
        Texture* testTex = new Texture(".\\resources\\box.jpg");
        Texture* planeTexture = new Texture(".\\resources\\orange_grid_512.png");
        Renderable3D* cube = new Renderable3D(cubeTransform, vec4(1, 0, 0, 1), Primitive3D::Cube, meshShader, testTex);
        Renderable3D* plane = new Renderable3D(planeTransfrom, vec4(1, 0, 1, 1), Primitive3D::Plane, meshShader, planeTexture);
        Font font(".\\resources\\fonts\\FiraCode-Light.ttf", 20);

        fpsLabel = new Label("FPS : ", vec3(25, 525, 0), vec3(1, 1, 1), font);

        scene->add(cube);
        scene->add(plane);
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
        deltaTime = (1.0 / getFPS());
        fpsLabel->text = "FPS : " + std::to_string(getFPS());
        fpsLabel->renderText();
        glEnable(GL_DEPTH_TEST);
        window->backgroundColor = vec4(0.101f, 0.101f, 0.101f, 1.0f);
        if (window->isKeyHeld(Keys::UP))
            camera3D->processKeyboardMovement(FreeFlyCameraMoveDirection::FORWARD, deltaTime);
        else if (window->isKeyHeld(Keys::DOWN))
            camera3D->processKeyboardMovement(FreeFlyCameraMoveDirection::BACKWARD, deltaTime);

        if (window->isKeyHeld(Keys::W))
            camera3D->processKeyboardMovement(FreeFlyCameraMoveDirection::UP, deltaTime);
        else if (window->isKeyHeld(Keys::S))
            camera3D->processKeyboardMovement(FreeFlyCameraMoveDirection::DOWN, deltaTime);

        if (window->isKeyHeld(Keys::LEFT) || window->isKeyHeld(Keys::A))
            camera3D->processKeyboardMovement(FreeFlyCameraMoveDirection::RIGHT, deltaTime);
        else if (window->isKeyHeld(Keys::RIGHT) || window->isKeyHeld(Keys::D))
            camera3D->processKeyboardMovement(FreeFlyCameraMoveDirection::LEFT, deltaTime);
 

        scene->render();
    }
};
