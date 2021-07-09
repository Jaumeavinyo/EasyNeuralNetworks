#include "ModuleImGui.h"
#include "glad/glad.h"
#include "..\ImGUI\imgui.h"
#include "..\ImGUI\backends\imgui_impl_opengl3.h"
#include "..\ImGUI\backends\imgui_impl_sdl.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include "App.h"
//############  CONSTRUCTORS ############


ModuleImGui::ModuleImGui(Application* app, const char* moduleName, bool start_enabled) : Module(app, start_enabled, moduleName) {

}

ModuleImGui::~ModuleImGui() {

}


//############  MAIN APP FUNCTIONS ############


bool ModuleImGui::Init() {

	bool ret = true;
	printf("ModuleImGui Init()\n");
	
	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		std::cerr << "[ERROR] Couldn't initialize glad" << std::endl;
	}
	else
	{
		std::cout << "[INFO] glad initialized\n";
	}
	std::string glsl_version = "";
	glsl_version = "#version 130";

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	
	ImGui::StyleColorsDark();

	ImGui_ImplSDL2_InitForOpenGL(App->window->window,App->window->gl_context);
	ImGui_ImplOpenGL3_Init(glsl_version.c_str());

	

	return ret;

}


bool ModuleImGui::Start() {

	bool ret = true;
	
	ImVec4 background = ImVec4(35 / 255.0f, 35 / 255.0f, 35 / 255.0f, 1.00f);
	glClearColor(background.x, background.y, background.z, background.w);

	show_demo_window = true;
	show_another_window = false;

	return ret;
}


update_status ModuleImGui::PreUpdate(float dt) {

	update_status ret = update_status::UPDATE_CONTINUE;

	 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	 // Start the Dear ImGui frame
	 ImGui_ImplOpenGL3_NewFrame();
	 ImGui_ImplSDL2_NewFrame(App->window->window);
	 ImGui::NewFrame();

	 

	return ret;

}

update_status ModuleImGui::Update(float dt) {

	update_status ret = update_status::UPDATE_CONTINUE;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	
	static float f = 0.0f;
	static int counter = 0;

	ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

	ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
	ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
	ImGui::Checkbox("Another Window", &show_another_window);

	ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
	ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

	if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
		counter++;
	ImGui::SameLine();
	ImGui::Text("counter = %d", counter);

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();

	return ret;

}

update_status ModuleImGui::PostUpdate(float dt) {

	update_status ret = update_status::UPDATE_CONTINUE;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	// Rendering
	ImGui::Render();
	glViewport(0, 0, (int)SCREEN_WIDTH, (int)SCREEN_HEIGHT);
	glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	SDL_GL_SwapWindow(App->window->window);
	return ret;

}


bool ModuleImGui::CleanUp() {

	bool ret = true;

	// Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
	return ret;

}

//############  UTILITY FUNCTIONS ############