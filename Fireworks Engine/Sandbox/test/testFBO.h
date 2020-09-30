/*
 *  A simple test showing the usage of FrameBuffers
 */
#include <fireworks.h>

// ImGUI
#include "../Test Dependencies/imgui-docking/imgui.h"
#include "../Test Dependencies/imgui-docking/imgui_impl_glfw.h"
#include "../Test Dependencies/imgui-docking/imgui_impl_opengl3.h"

using namespace fireworks;

class TestFBOGUI : public Fireworks
{
private:
    Window* window;
    Layer* layer;
    FrameBuffer* frameBuffer;
public:
    TestFBOGUI() { }

    ~TestFBOGUI()
    {
        delete layer;
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    // Runs once per initialization
    void init() override
    {
        window = createWindow("Simple Box Example : Fireworks Engine", 1200, 800);
        frameBuffer = new FrameBuffer(window->getWidth(), window->getHeight());
        layer = new Layer(new BatchRenderer2D(),
                new Shader(".\\shaders\\basic.vert",
                           ".\\shaders\\basic.frag"),
                mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f));

        glClearColor(0.5f, 0.1f, 0.2f, 1.0f);

        Sprite* box = new Sprite(4.0f, 4.0f, 4.0f, 4.0f, vec4(1.0f, 1.0f, 0.0f, 1.0f));
        layer->add(box);


        // ImGUI Initialization

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        ImGui::StyleColorsDark();

        const char* glsl_version = "#version 410";
        ImGui_ImplGlfw_InitForOpenGL(window->getGLFWwindow(), true);
        ImGui_ImplOpenGL3_Init(glsl_version);

    }

    // Runs once per second
    void tick() override { }

    // Runs 60 times per second
    void update() override
    {
        layer->m_Shader->setUniformMat4("model", mat4::translation(vec3(sin(glfwGetTime()) * 2, 2.0f, 0.0f)));
    }

    // Runs as fast as possible
    void render() override
    {
        frameBuffer->bind();

		glEnable(GL_DEPTH_TEST);
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        layer->render();
        frameBuffer->unbind();

        // Render ImGui

		glDisable(GL_DEPTH_TEST);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::ShowDemoWindow();

        ImGui::SetNextWindowSize(ImVec2(600, 400), ImGuiCond_Once);
	    ImGui::Begin("Scene View");
	    {
            ImGui::BeginChild("Game Render");
		    ImVec2 window_size = ImGui::GetWindowSize();
		    ImGui::Image((ImTextureID)(size_t)frameBuffer->getRenderTexture(), ImVec2(window_size.x, window_size.y), ImVec2(0, 1), ImVec2(1, 0));
            ImGui::EndChild();
	    }
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
};
