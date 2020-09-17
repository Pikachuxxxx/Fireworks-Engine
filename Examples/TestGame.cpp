#include <fireworks/fireworks.h>

// ImGui
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

using namespace fireworks;

class TestGame : public Fireworks
{
private:
    Window* window;
    Layer* layer;
public:
    TestGame() { }

    ~TestGame()
    {
        delete window;
        delete layer;

        // ImGui Cleanup
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void init() override
    {
        window = createWindow("Test Game Example : Fireworks Engine", 800, 600);
        layer = new Layer(new BatchRenderer2D(),
                          new Shader("../Fireworks-core/src/shaders/basic.vert",
                                     "../Fireworks-core/src/shaders/basic.frag"),
                          mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f , 1.0f));

        Sprite* box = new Sprite(4.0f, 4.0f, 4.0f, 4.0f, vec4(1.0f, 1.0f, 0.0f, 1.0f));
        layer->add(box);

        const char* glsl_version = "#version 410";

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window->getGLFWwindow(), true);
        ImGui_ImplOpenGL3_Init(glsl_version);
    }

    void tick() override
    {

    }

    void update() override
    {

    }

    void render() override
    {
        layer->render();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::ShowDemoWindow();

        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    }
};

int main()
{
    TestGame game;
    game.start();
    return 0;
}
