#include <fireworks.h>
#include "EditorGUI.h"

using namespace fireworks;

class Scene3DTest : public Fireworks, public EditorGUI
{
private:
    Window*         window;
    Scene3D*        scene;
    FreeFlyCamera*  camera3D;
    Shader*         meshShader;
    Label*          fpsLabel;
    Model*          model;
    double          deltaTime;
    bool            firstMouse = true;
    double          lastX = 400.0, lastY = 300.0;
    bool            enableWireFrameMode;
public:
    Scene3DTest() : EditorGUI()
    {
        window = createWindow("3D Scene Testing", 1600, 1200);
        InitGUI(window);
        camera3D = new FreeFlyCamera(vec3(-1.46, -1.34, -15));
        #if (_WIN32)
        meshShader = new Shader(".\\shaders\\mesh.vert", ".\\shaders\\mesh.frag");
        #elif (__APPLE__)
        meshShader = new Shader("./shaders/mesh.vert", "./shaders/mesh.frag");
        #endif
        ShotRenderer3D* shot3d = new ShotRenderer3D(camera3D);
        BatchRenderer3D* batch3d = new BatchRenderer3D(camera3D, meshShader);
        scene = new Scene3D(batch3d);

        Transform cubeTransform(vec3(0, 0, 0), vec3(0, 0, 0), vec3(2, 2, 2));
        Transform planeTransfrom(vec3(0, -2, 0), vec3(0, 0, 0), vec3(20, 20, 2));
        Transform anotherTransform(vec3(1, 2, 3), vec3(20, 0, 0));
        #if (_WIN32)
        Texture* testTex = new Texture(".\\resources\\texture_01_red.png");
        Texture* planeTexture = new Texture(".\\resources\\orange_grid_512.png");
        #elif (__APPLE__)
        Texture* testTex = new Texture("./resources/texture_01_red.png");
        Texture* planeTexture = new Texture("./resources/orange_grid_512.png");
        #endif
        Renderable3D* cube = new Renderable3D(cubeTransform, vec4(1, 0, 0, 1), Primitive3D::Cube, meshShader, testTex);

        Mesh* cubeMesh = new Mesh(cubeTransform, Primitive3D::Cube, meshShader, testTex);
        Mesh* cube_2_Mesh = new Mesh(anotherTransform, Primitive3D::Cube, meshShader, testTex);
        Mesh* planeMesh = new Mesh(planeTransfrom, Primitive3D::Plane, meshShader, planeTexture);
        #if (_WIN32)
        Font font(".\\resources\\fonts\\SpaceQuest.ttf", 32);
        #elif (__APPLE__)
        Font font("./resources/fonts/SpaceQuest.ttf", 32);
        #endif

        fpsLabel = new Label("FPS : ", vec3(25, 525, 0), vec3(0.8, 0.5, 0), font);

        scene->add(planeMesh);

        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                scene->add(new Mesh(Transform(vec3(-10 + i * 2, 0, -10 + j * 2)), Primitive3D::UVSphere, meshShader, testTex));
            }
        }

        //scene->add(new Mesh(Transform(vec3(0, 0, 0)), Primitive3D::UVSphere, meshShader, testTex));
        // scene->add(new Mesh(Transform(vec3(4, 0, 0)), Primitive3D::Cylinder, meshShader, testTex));

        // #if (_WIN32)
        // Texture* stTex = new Texture(".\\resources\\models\\stormtrooper\\source\\stormtrooper_D.png");
        // #elif (__APPLE__)
        // Texture* stTex = new Texture("./resources/models/stormtrooper/source/stormtrooper_D.png");
        // #endif


        // #if (_WIN32)
        // model = new Model(std::string(".\\resources\\models\\stormtrooper\\source\\stormtrooper.obj"), cubeTransform, meshShader);
        // #elif (__APPLE__)
        // model = new Model(std::string("./resources/models/stormtrooper/source/stormtrooper.obj"), cubeTransform, meshShader);
        // #endif
        // model->getMasterMesh().m_Texture = stTex;
        // scene->add(model);


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

    void RenderGUI()
    {
        ImGui::Begin("Stats");
        {
            ImGui::Text("FPS : %d", getFPS());
            ImGui::Text("Camera Positions : [%2.2f, %2.2f, %2.2f]", camera3D->position.x, camera3D->position.y, camera3D->position.z);
            ImGui::Checkbox("WireFrame mode", &enableWireFrameMode);
        }
        ImGui::End();
    }

    // Runs as fast as possible
    void render() override
    {

        glPointSize(10.0f);
        deltaTime = (1.0 / getFPS());
        fpsLabel->text = "FPS : " + std::to_string(getFPS());
        fpsLabel->renderText();

        if (enableWireFrameMode)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


        window->backgroundColor = vec4(0.9f, 0.9f, 0.9f, 1.0f);
        if (window->isKeyHeld(Keys::UP))
            camera3D->processKeyboardMovement(FreeFlyCameraMoveDirection::UP, deltaTime);
        else if (window->isKeyHeld(Keys::DOWN))
            camera3D->processKeyboardMovement(FreeFlyCameraMoveDirection::DOWN, deltaTime);

        if (window->isKeyHeld(Keys::W))
            camera3D->processKeyboardMovement(FreeFlyCameraMoveDirection::FORWARD, deltaTime);
        else if (window->isKeyHeld(Keys::S))
            camera3D->processKeyboardMovement(FreeFlyCameraMoveDirection::BACKWARD, deltaTime);

        if (window->isKeyHeld(Keys::A))
            camera3D->processKeyboardMovement(FreeFlyCameraMoveDirection::RIGHT, deltaTime);
        else if (window->isKeyHeld(Keys::D))
            camera3D->processKeyboardMovement(FreeFlyCameraMoveDirection::LEFT, deltaTime);

        if (window->isKeyHeld(Keys::RIGHT))
            camera3D->processKeyboardMovement(FreeFlyCameraMoveDirection::YAW_RIGHT, deltaTime);
        else if (window->isKeyHeld(Keys::LEFT))
            camera3D->processKeyboardMovement(FreeFlyCameraMoveDirection::YAW_LEFT, deltaTime);

         scene->render();
        InitRenderingGUI();
    }
};
