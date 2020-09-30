/*
 * A simple test showing the usage of FrameBuffers and ImGui to the full extent
 */
#include <fireworks.h>

 // ImGUI
#include "../Test Dependencies/imgui-docking/imgui.h"
#include "../Test Dependencies/imgui-docking/imgui_impl_glfw.h"
#include "../Test Dependencies/imgui-docking/imgui_impl_opengl3.h"

using namespace fireworks;

class TestGUI : public Fireworks
{
private:
    Window*         window;
    Layer*          layer;
    FrameBuffer*    frameBuffer;

    Sprite*         box;
    ImVec4          bg_Color;
    ImVec4          sprite_Color;
    vec2            sprite_Pos;
    vec2            sprite_Size;
    float           speed;
public:
    TestGUI() : speed(10.0f)
    { 
        sprite_Color = ImVec4(1.0f, 1.0f, 0.0f, 1.0f);
        sprite_Pos = vec2(4.0f, 4.0f);
        sprite_Size = vec2(2.0f, 2.0f);
    }

    ~TestGUI()
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

        box = new Sprite(2.0f, 4.0f, 4.0f, 4.0f, vec4(1.0f, 1.0f, 0.0f, 1.0f));
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
		box->color = vec4(sprite_Color.x, sprite_Color.y, sprite_Color.z, sprite_Color.w);

        if (window->isKeyPressed(GLFW_KEY_UP))
        {
            std::cout << speed << std::endl;
            box->position.y += 0.02f * speed;
        }
        else if (window->isKeyPressed(GLFW_KEY_DOWN))
        {
            box->position.y -= 0.02f * speed;
        }
        if (window->isKeyPressed(GLFW_KEY_RIGHT))
        {
            box->position.x += 0.02f * speed;
        }
        else if (window->isKeyPressed(GLFW_KEY_LEFT))
        {
            box->position.x -= 0.02f * speed;
        }
    }

    // Runs as fast as possible
    void render() override
    {
        frameBuffer->bind();
        glEnable(GL_DEPTH_TEST);
        glClearColor(bg_Color.x, bg_Color.y, bg_Color.z, bg_Color.w);
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

		ImGui::SetNextWindowSize(ImVec2(400, 400), ImGuiCond_Once);
        ImGui::Begin("Stats");
        {
            ImGui::Text("FPS : %d", getFPS());
			ImGui::Text("UPS : %d", getUPS());
			ImGui::Text("Renderer Draw Calls : %d", layer->m_Renderer->rendererDrawCalls);
            ImGui::Text("Renderable Objects : %d",  layer->m_Renderables.size());
        }
		ImGui::End();

		ImGui::Begin("Inspector");
        {
			ImGui::PushItemWidth(180);
            ImGui::ColorEdit4("Background color ", (float*)&bg_Color);
			ImGui::ColorEdit4("Sprite color ", (float*)&sprite_Color);
			ImGui::PushItemWidth(-1);

			if (ImGui::CollapsingHeader("Position"))
			{
				ImGui::PushItemWidth(80);
				ImGui::InputFloat("X ", &sprite_Pos.x, 0.1f, 1.0f, "%.2f");
				ImGui::SameLine();
				ImGui::InputFloat("Y ", &sprite_Pos.y, 0.1f, 1.0f, "%.2f");
				ImGui::PushItemWidth(-1);
			}
			if (ImGui::CollapsingHeader("Scale"))
			{
				ImGui::PushItemWidth(80);
				ImGui::InputFloat("X ", &sprite_Size.x, 0.1f, 1.0f, "%.2f");
				ImGui::SameLine();
				ImGui::InputFloat("Y ", &sprite_Size.y, 0.1f, 1.0f, "%.2f");
				ImGui::PushItemWidth(-1);
			}
        }
		ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
};
