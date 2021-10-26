/*
 * A simple example to control a simple sprite using keyboard input
 * Use the Arrow keys to move the hungry player and feed him the food
 * every time you catch a food block you change into the collected food item color
 */
#include <fireworks.h>
#include <iostream>

#include "falken/actions.h"
#include "falken/brain.h"
#include "falken/episode.h"
#include "falken/observations.h"
#include "falken/service.h"
#include "falken/session.h"

#include "../examples/falkengame/ship.h"
#include "../test/EditorGUI.h"

using namespace fireworks;
using namespace falken;

struct MyActions : public falken::ActionsBase
{
    MyActions()
        : FALKEN_NUMBER(throttle, 0.0f, 50.0f),
        FALKEN_JOYSTICK_DELTA_PITCH_YAW(joystick,
        falken::kControlledEntityPlayer) {}

    falken::NumberAttribute<float> throttle;
    falken::JoystickAttribute joystick;
};

struct MyObservations : public falken::ObservationsBase
{
    MyObservations() : FALKEN_ENTITY(goal) {}

    falken::EntityBase goal;
};

using MyBrainSpec = falken::BrainSpec<MyObservations, MyActions>;

class HungryBox : public Fireworks, public EditorGUI
{
private:
    Window*     window;
    Camera2D*   camera;
    Layer*      layer;
    Sprite*     playerBox;
    Sprite*     food;
    float       speed;
    vec4        prevColor;
    Shader*     basicShader;

    Ship        ship;

private:
    std::shared_ptr<falken::Service> service;
    std::shared_ptr<falken::Brain<MyBrainSpec>> brain;
    std::shared_ptr<falken::Session> session;
    std::shared_ptr<falken::Episode> episode = nullptr;

    //! Max steps allowed per episode
    const int kMaxSteps = 10000;

    //! Falken Control variables
    bool human_control = true;
    bool force_evaluation = false;
    bool space_was_pressed = false;
    bool reset_was_pressed = false;
public:
    HungryBox() : speed(10.0f), prevColor(vec4(1, 0, 0, 1)) { }

    ~HungryBox() { 
        StopSession();
    }

    // Runs once per initialization
    void init() override
    {
        window = createWindow("Hungry Box : Keyboard Input Example", 800, 600);
        InitGUI(window);
        camera = new Camera2D(mat4::orthographic(-64.0f, 64.0f, -48.0f, 48.0f, -1.0f, 1.0f));

        #if(_WIN32)
		    basicShader = new Shader(".\\shaders\\basic.vert", ".\\shaders\\basic.frag");
        #elif(__APPLE__)
            basicShader = new Shader("shaders/basic.vert", "shaders/basic.frag");
        #endif
		BatchRenderer2D* batchRenderer = new BatchRenderer2D(camera, basicShader);

		layer = new Layer(batchRenderer);

        food = new Sprite(vec3(4.0f, 2.5f, 0.0f), vec2(8.5f, 8.5f), vec4(1.0f, 0.0f, 0.0f, 1.0f));

        // Now create and add the renderables to the layer
        Texture* playerTex = new Texture("./resources/diamond.png");
        playerBox = new Sprite(vec3(0, 0, 0), vec2(8, 8), basicShader, playerTex, Primitive2D::Quad);
        playerBox->rotation = -120.0f;

        layer->add(playerBox);
        layer->add(food);

        srand(time(0));

        //! Start the Falken service
        service = falken::Service::Connect( nullptr, nullptr, nullptr);

        //! Create a brain with the specified action and observation
        static const char* kBrainName = "HF_Brain";
        brain = service->CreateBrain<MyBrainSpec>(kBrainName);
        // Log the brain ID
        std::cout << "Created Brain : " << brain->id();

        //! Start a session to teach Falken how to play the game
        session = brain->StartSession(falken::Session::kTypeInteractiveTraining, kMaxSteps);
        // Log the session ID
        std::cout << "Created Session : " << session->id();
           
        //! Reset the game state
        Reset(false);
    } 

    // Runs once per second
    void tick() override { }

    // Runs 60 times per second
    void update() override
    {
   
        //! Process the Input
        PlayerInput();

        //! Update the Falken Player
        FalkenUpdate();

        //! Update Physics and Goal achievement
        UpdatePhysics();
    }

    void RenderGUI()
    {
        ImGui::Begin("Stats");
        {
            ImGui::Text("FPS : %d", getFPS());
            ImGui::Text("Ship Steering : %f", ship.GetSteering());
            ImGui::Text("Ship Throttle : %f", ship.GetThrottle());
            ImGui::Text("Ship Position : %f, %f", ship.position.x, ship.position.y);
            ImGui::Text("Ship Rotation : %f", ship.rotation);
        }
        ImGui::End();
    }

    // Runs as fast as possible
    void render() override
    {
        // Render the Layer
        layer->render();
        InitRenderingGUI();
    }

    void PlayerInput()
    {
        if (window->isKeyPressed(GLFW_KEY_SPACE)) {
            human_control = !human_control;
            std::cout << "Switching control! to : " << (human_control ? "Human" : "Falken") << std::endl;
        }

        if (window->isKeyPressed(GLFW_KEY_R)) {
            reset_was_pressed = !reset_was_pressed;
            Reset(false);
        }

        if (window->isKeyPressed(GLFW_KEY_E))
            force_evaluation = !force_evaluation;

        if (human_control) {
            float steering = 0.f;
            float throttle = 0.f;
            if (window->isKeyHeld(GLFW_KEY_UP)) {
                throttle += 1.f;
            }
            else if (window->isKeyHeld(GLFW_KEY_DOWN)) {
                throttle -= 1.f;
            }
            if (window->isKeyHeld(GLFW_KEY_RIGHT)) {
                steering -= 1.f;
            }
            else if (window->isKeyHeld(GLFW_KEY_LEFT)) {
                steering += 1.f;
            }

            ship.SetControls(steering, throttle);

            // Update the ship 
            double deltaTime = 1.0 / (double) getFPS();
            std::cout << "deltaTime : " << deltaTime << std::endl;
            if (getFPS() != 0)
                ship.Update(deltaTime * 10.0f);

            // Update the player
            playerBox->position = vec3(ship.position.x, ship.position.y, 0.0f);
            playerBox->rotation = ship.rotation;
        }
    }

    void FalkenUpdate()
    {
        if (episode != nullptr) {
            // Change session type when training is complete or the player requests an evaluation session
            bool training_complete = session->training_state() == falken::Session::kTrainingStateComplete;
            switch (session->type()) {
                case falken::Session::kTypeInteractiveTraining:
                    if (training_complete || force_evaluation) {
                        StartEvaluationSession();
                    }
                    break;
                case falken::Session::kTypeEvaluation:
                    if (training_complete)
                        StartInferenceSession();
                        break;
                default:
                    break;
            }

            //! Get the brain and Train it!
            auto& brain_spec = brain->brain_spec();

            float playerx = 0.0f, playery = 0.0f;
            if (window->isKeyHeld(GLFW_KEY_LEFT))
                playerx = -1.0f;
            if (window->isKeyHeld(GLFW_KEY_RIGHT))
                playerx = 1.0f;
            if (window->isKeyHeld(GLFW_KEY_UP))
                playery = 1.0f;
            if (window->isKeyHeld(GLFW_KEY_DOWN))
                playery = -1.0f;

            // observe the player position
            brain_spec.observations.position.set_value(falken::Position({ playerBox->position.x, playerBox->position.y, 0}));
            brain_spec.observations.rotation.set_value(falken::Rotation(0.0f, 0.0f, 0.0f, 0.0f));
            // observe the food position
            brain_spec.observations.goal.position.set_value(falken::Position({ food->position.x, food->position.y, 0 }));
            brain_spec.observations.goal.rotation.set_value(falken::Rotation(0.0f, 0.0f, 0.0f, 0.0f));

            // If being controlled by human, then teach the actions to it
            if (human_control) {
                // Set action source as human demonstration
                brain_spec.actions.set_source(ActionsBase::kSourceHumanDemonstration);

                // feed the human control input to falken brain //clamp(playerBox->getPosition().x, -1.0f, 1.0f, -16.0f, 16.0f);
                //auto playery = clamp(playerBox->getPosition().y, -1.0f, 1.0f, -12.0f, 12.0f);
                brain_spec.actions.joystick.set_x_axis(playerx);
                brain_spec.actions.joystick.set_y_axis(playery);

                brain_spec.actions.throttle = speed;
            }
            else {
                brain_spec.actions.set_source(falken::ActionsBase::kSourceNone);
            }

            episode->Step(0.0f);

            if (episode->completed()) {
                episode = nullptr;
            }
            else if (!human_control) {
                brain_spec.actions.set_source(falken::ActionsBase::kSourceBrainAction);
                //std::cout << "Falken X - Axis Joystick : " << brain_spec.actions.joystick.x_axis() << std::endl;
                //std::cout << "Falken Y - Axis Joystick : " << brain_spec.actions.joystick.y_axis() << std::endl;
                //std::cout << "Falken Throttle : " << brain_spec.actions.throttle << std::endl;
                playerBox->position.x = brain_spec.actions.joystick.x_axis() * brain_spec.actions.throttle.value();
                playerBox->position.y = brain_spec.actions.joystick.y_axis() * brain_spec.actions.throttle.value();
            }
        }
    }

    void UpdatePhysics()
    {
        //! Check if the player consumed the food or not
        float squaredDistance = abs(pow(playerBox->position.x - food->position.x, 2) +
            pow(playerBox->position.y - food->position.y, 2) +
            pow(playerBox->position.z - food->position.z, 2));

        //! If Goal is reached reset the game for another round
        if (squaredDistance <= 0.6f) {
            std::cout << "Goal Reached!" << std::endl;
            Reset(true);
        }
    }

    void StartEvaluationSession()
    {
        if (force_evaluation) {
            std::cout << "User triggered evaluation mode.\n";
        }
        else {
            std::cout << "Training complete.\n";
        }
        StopSession();
        session = brain->StartSession(falken::Session::kTypeEvaluation, kMaxSteps);
        if (session == nullptr) {
            std::cout << "Could not start evaluation session.\n";
            return;
        }
        std::cout << "Started eval session: %s\n", session->id();
        episode = session->StartEpisode();
    }

    void Reset(bool success)
    {
        //! Reset the player
        playerBox->position = vec3(getRandomValue<float>(-7, 7), getRandomValue<float>(-5, 5), 0.0f);;

        //! Reset the goal
        ResetGoal();

        //! Reset Falken Episode
        ResetFalken(success);
    }

    void ResetGoal()
    {
        vec3 randPos = vec3(getRandomValue<float>(-7, 7), getRandomValue<float>(-5, 5), 0.0f);
        vec4 randColor = vec4(getRandomValue<float>(0.0f, 1.0f), getRandomValue<float>(0.0f, 1.0f), getRandomValue<float>(0.0f, 1.0f), 1.0f);
        food->position = randPos;
        food->color = randColor;
        playerBox->color = prevColor;
        prevColor = randColor;
    }

    void ResetFalken(bool success)
    {
        if (episode != nullptr && !episode->completed()) {
            episode->Complete(success ? falken::Episode::kCompletionStateSuccess : falken::Episode::kCompletionStateFailure);
        }

        if (session != nullptr) {
            //! Start your first Episode at the start of the game
            episode = session->StartEpisode();
        }
    }

    void StopSession()
    {
        if (episode != nullptr) {
            episode->Complete(falken::Episode::kCompletionStateAborted);
            episode = nullptr;
        }
        if (session != nullptr) {
            auto snapshot_id = session->Stop();
            std::cout << "Stopped session with snapshot ID : " << snapshot_id.c_str() << std::endl;
            session = nullptr;
        }
    }

    void StartInferenceSession()
    {
        // Because the episode was started at Reset, Step the episode before stopping
        // with an empty episode.
        episode->Step(0.f);
        StopSession();

        session = brain->StartSession(falken::Session::kTypeInference, kMaxSteps);
        if (session == nullptr) {
            std::cout << "Could not start inference session." << std::endl;
            return;
        }
        std::cout << "Started inference session: " << session->id() << std::endl;
        episode = session->StartEpisode();
    }
};
