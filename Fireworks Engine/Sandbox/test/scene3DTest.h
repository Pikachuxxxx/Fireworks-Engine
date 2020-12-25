#include <fireworks.h>

using namespace fireworks;

class Scene3DTest : public Fireworks
{
private:
    Window* window;
    Scene3D* scene;
    FreeFlyCamera* camera3D;
    Shader* meshShader;
    Label* fpsLabel;
    Model* model;
    double deltaTime;
    bool firstMouse = true;
    double lastX = 400.0, lastY = 300.0;
public:
    Scene3DTest()
    {
        window = createWindow("3D Scene Testing", 800, 600);
        camera3D = new FreeFlyCamera(vec3(0, 0, -5));
        meshShader = new Shader(".\\shaders\\mesh.vert", ".\\shaders\\mesh.frag");
        ShotRenderer3D* shot3d = new ShotRenderer3D(camera3D);
        BatchRenderer3D* batch3d = new BatchRenderer3D(camera3D, meshShader);
        scene = new Scene3D(batch3d);
       
        Transform cubeTransform(vec3(0, 0, 0), vec3(0, 0, 0), vec3(2, 2, 2));
        Transform planeTransfrom(vec3(0, -2, 0), vec3(0, 0, 0), vec3(20, 20, 2));
        Transform anotherTransform(vec3(1, 2, 3), vec3(20, 0, 0));
        Texture* testTex = new Texture(".\\resources\\texture_01_red.png");
        Texture* planeTexture = new Texture(".\\resources\\orange_grid_512.png");
        Renderable3D* cube = new Renderable3D(cubeTransform, vec4(1, 0, 0, 1), Primitive3D::Cube, meshShader, testTex);

        Mesh* cubeMesh = new Mesh(cubeTransform, Primitive3D::Cube, meshShader, testTex);
        Mesh* cube_2_Mesh = new Mesh(anotherTransform, Primitive3D::Cube, meshShader, testTex);
        Mesh* planeMesh = new Mesh(planeTransfrom, Primitive3D::Plane, meshShader, planeTexture);
        Font font(".\\resources\\fonts\\FiraCode-Light.ttf", 20);

        fpsLabel = new Label("FPS : ", vec3(25, 525, 0), vec3(1, 1, 1), font);

        scene->add(planeMesh);

        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                scene->add(new Mesh(Transform(vec3(-10 + i * 2, 0, -10 + j * 2)), Primitive3D::Cube, meshShader, testTex));
            }
        }

        Texture* stTex = new Texture(".\\resources\\models\\stormtrooper\\source\\stormtrooper_D.png");

        model = new Model(std::string(".\\resources\\models\\stormtrooper\\source\\stormtrooper.obj"), cubeTransform, meshShader);
        model->getMasterMesh().m_Texture = stTex;

        scene->add(model);
    }

    ~Scene3DTest()
    {
        delete model;
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

        window->backgroundColor = vec4(0.101f, 0.101f, 0.101f, 1.0f);
        if (window->isKeyHeld(Keys::UP))
            camera3D->processKeyboardMovement(FreeFlyCameraMoveDirection::FORWARD, deltaTime);
        else if (window->isKeyHeld(Keys::DOWN))
            camera3D->processKeyboardMovement(FreeFlyCameraMoveDirection::BACKWARD, deltaTime);

        if (window->isKeyHeld(Keys::W))
            camera3D->processKeyboardMovement(FreeFlyCameraMoveDirection::UP, deltaTime);
        else if (window->isKeyHeld(Keys::S))
            camera3D->processKeyboardMovement(FreeFlyCameraMoveDirection::DOWN, deltaTime);

        if (window->isKeyHeld(Keys::A))
            camera3D->processKeyboardMovement(FreeFlyCameraMoveDirection::RIGHT, deltaTime);
        else if (window->isKeyHeld(Keys::D))
            camera3D->processKeyboardMovement(FreeFlyCameraMoveDirection::LEFT, deltaTime);

        if (window->isKeyHeld(Keys::RIGHT))
            camera3D->processKeyboardMovement(FreeFlyCameraMoveDirection::YAW_RIGHT, deltaTime);
        else if (window->isKeyHeld(Keys::LEFT))
            camera3D->processKeyboardMovement(FreeFlyCameraMoveDirection::YAW_LEFT, deltaTime);
 

        scene->render();
    }
};
