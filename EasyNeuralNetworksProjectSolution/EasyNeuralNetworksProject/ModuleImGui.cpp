//#include "ModuleImGui.h"
//#include "..\imgui-1.83\imgui.h"
//#include "..\imgui-1.83\backends\imgui_impl_opengl2.h"
//#include "..\imgui-1.83\backends\imgui_impl_sdl.h"
//#include <SDL.h>
//#include <SDL_opengl.h>
//#include "App.h"
////############  CONSTRUCTORS ############
//
//
//ModuleImGui::ModuleImGui(Application* app, const char* moduleName, bool start_enabled) : Module(app, start_enabled, moduleName) {
//
//}
//
//ModuleImGui::~ModuleImGui() {
//
//}
//
//
////############  MAIN APP FUNCTIONS ############
//
//
//bool ModuleImGui::Init() {
//
//	bool ret = true;
//	printf("ModuleImGui Init()\n");
//	
//	// Setup Dear ImGui context
//	IMGUI_CHECKVERSION();
//	ImGui::CreateContext();//1
//	
//	
//	ImGuiIO& io = ImGui::GetIO(); (void)io;
//	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
//	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
//
//	// Setup Dear ImGui style
//	ImGui::StyleColorsDark();
//	////ImGui::StyleColorsClassic();
//
//	// Setup Platform/Renderer backends
//	ImGui_ImplSDL2_InitForOpenGL(App->window->window,App->window->gl_context);
//	ImGui_ImplOpenGL2_Init();
//
//	
//
//	return ret;
//
//}
//
//
//bool ModuleImGui::Start() {
//
//	bool ret = true;
//
//	return ret;
//}
//
//
//update_status ModuleImGui::PreUpdate(float dt) {
//
//	update_status ret = update_status::UPDATE_CONTINUE;
//
//	// Start the Dear ImGui frame
//	//ImGui_ImplOpenGL2_NewFrame();
//	//ImGui_ImplSDL2_NewFrame(App->window->window);
//	ImGui::NewFrame();
//
//	return ret;
//
//}
//
//update_status ModuleImGui::Update(float dt) {
//
//	update_status ret = update_status::UPDATE_CONTINUE;
//
//	//static float f = 0.0f;
//	//static int counter = 0;
//
//	//bool show_another_window;
//	//ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
//
//	//ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
//
//	//ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
//	//ImGui::Checkbox("Another Window", &show_another_window);
//
//	//ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
//	//ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
//
//	//if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
//	//	counter++;
//	//ImGui::SameLine();
//	//ImGui::Text("counter = %d", counter);
//
//	//ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
//	//ImGui::End();
//
//
//	//if (show_another_window)
//	//{
//	//	ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
//	//	ImGui::Text("Hello from another window!");
//	//	if (ImGui::Button("Close Me"))
//	//		show_another_window = false;
//	//	ImGui::End();
//	//}
//
//
//
//
//
//
//	return ret;
//
//}
//
//update_status ModuleImGui::PostUpdate(float dt) {
//
//	update_status ret = update_status::UPDATE_CONTINUE;
//	//// Rendering
//	//ImGui::Render();
//	//glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
//	//glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
//	//glClear(GL_COLOR_BUFFER_BIT);
//	////glUseProgram(0); // You may want this if using this code in an OpenGL 3+ context where shaders may be bound
//	//ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
//	//SDL_GL_SwapWindow(App->window->window);
//	return ret;
//
//}
//
//
//bool ModuleImGui::CleanUp() {
//
//	bool ret = true;
//
//	//// Cleanup
//	//ImGui_ImplOpenGL2_Shutdown();
//	//ImGui_ImplSDL2_Shutdown();
//	//ImGui::DestroyContext();
//
//	return ret;
//
//}
//
////############  UTILITY FUNCTIONS ############