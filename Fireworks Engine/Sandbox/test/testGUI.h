/*
 * A simple test showing the usage of FrameBuffers and ImGui to the full extent
 */
#include <fireworks.h>

 // ImGUI
#include "../Test Dependencies/imgui-docking/imgui.h"
#include "../Test Dependencies/imgui-docking/imgui_impl_glfw.h"
#include "../Test Dependencies/imgui-docking/imgui_impl_opengl3.h"

using namespace fireworks;

enum CamerType
{
    Orthographic = 0,
    Perspective = 1
};

// Forward Declarations
void ImGuiEnableDocking(bool* p_open);

class TestGUI : public Fireworks
{
private:
    Window*         window;
	Camera2D*       camera;
	Layer*          layer;
    FrameBuffer*    frameBuffer;

    Shader*         basicShader;
	Sprite*         box;
	ImVec4          bg_Color;
	ImVec4          sprite_Color;
	vec2            sprite_Pos;
	vec2            sprite_Size;
	float           speed;
    bool            enableDocking;
    CamerType       cameraType;
    float           nearPlaneNDCRange;
    float           farPlaneNDCRange;
    float           orthoPlaneXmin;
    float           orthoPlaneYmin;
	float           orthoPlaneXmax;
	float           orthoPlaneYmax;

private:
    friend void ImGuiEnableDocking(bool* p_open);
public:
    TestGUI() 
		: speed(10.0f), enableDocking(true), cameraType(CamerType::Orthographic)
    { 
        window      = createWindow("Simple Box Example : Fireworks Engine", 1200, 800);
        frameBuffer = new FrameBuffer(window->getWidth(), window->getHeight());
		camera = new Camera2D(mat4::orthographic(-16.0f, 16.0f, -12.0f, 12.0f, -1.0f, 1.0f));

		basicShader = new Shader(".\\shaders\\basic.vert", ".\\shaders\\basic.frag");
		BatchRenderer2D* batchRenderer = new BatchRenderer2D(camera, basicShader);

		layer = new Layer(batchRenderer);

        box = new Sprite(vec3(2.0f, 4.0f, 0.0f), vec2(4.0f, 4.0f), vec4(1.0f, 1.0f, 0.0f, 1.0f));
        layer->add(box);

        sprite_Color = ImVec4(1.0f, 1.0f, 0.0f, 1.0f);
        sprite_Pos   = vec2(4.0f, 4.0f);
        sprite_Size  = vec2(2.0f, 2.0f);

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
        glClearColor(0.5f, 0.1f, 0.2f, 1.0f);

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

        //layer->m_Shader->setUniformMat4("model", mat4::scale(vec3(0.2f, 0.2f, 0.0f)));
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

		ImGuiEnableDocking(&enableDocking);
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

        ImGui::Begin("Camera 2D");
        {
            const char* cam_type = cameraType ? "Perspective" : "Orthographic";
            ImGui::Text("Camera Type : %s", cam_type);
            if (cameraType == CamerType::Orthographic)
            {
                if(ImGui::CollapsingHeader("Orthographic Properties"))
                {
				    ImGui::PushItemWidth(80);
                    ImGui::InputFloat("Near Plane NDC Range", &nearPlaneNDCRange, -1.0f, 0.0f, "%.2f");
					ImGui::InputFloat("Far Plane NDC Range", &farPlaneNDCRange, 0.0f, 1.0f, "%.2f");

                    ImGui::Text("Camera Orthographic Plane Boundaries");
					ImGui::InputFloat("X min", &orthoPlaneXmin, -20.0f, 20.0f, "%.2f");
					ImGui::SameLine();                           
					ImGui::InputFloat("X max", &orthoPlaneXmax, -20.0f, 20.0f, "%.2f");
                                                                 
					ImGui::InputFloat("Y min", &orthoPlaneYmin, -20.0f, 20.0f, "%.2f");
					ImGui::SameLine();                           
					ImGui::InputFloat("Y max", &orthoPlaneYmax, -20.0f, 20.0f, "%.2f");
				    ImGui::PushItemWidth(-1);
                }
            }
        }
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
};

void ImGuiEnableDocking(bool* p_open)
{
	static bool opt_fullscreen = true;
	static bool opt_padding = false;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
	// because it would be confusing to have two docking targets within each others.
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	if (opt_fullscreen)
	{
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->GetWorkPos());
		ImGui::SetNextWindowSize(viewport->GetWorkSize());
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}
	else
	{
		dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
	}

	// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
	// and handle the pass-thru hole, so we ask Begin() to not render a background.
	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		window_flags |= ImGuiWindowFlags_NoBackground;

	// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
	// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
	// all active windows docked into it will lose their parent and become undocked.
	// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
	// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
	if (!opt_padding)
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("DockSpace Demo", p_open, window_flags);
	if (!opt_padding)
		ImGui::PopStyleVar();

	if (opt_fullscreen)
		ImGui::PopStyleVar(2);

	// DockSpace
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	}
	else
	{
		std::cerr << "ERROR::ImGui::Cannot Dock Windows" << '\n';
	}

	ImGui::End();
}