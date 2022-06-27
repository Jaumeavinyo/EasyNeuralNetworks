#include "ModuleScene.h"
#include "lib\ImGUI\imgui.h"
#include "App.h"
#include "DynamicArray.h"


//############  CONSTRUCTORS ############


ModuleScene::ModuleScene(Application* app, const char* moduleName, bool start_enabled) : Module(app, start_enabled, moduleName){
}

ModuleScene::~ModuleScene()
{
}


//############  MAIN APP FUNCTIONS ############


bool ModuleScene::Init() {

	bool ret = true;

	printf("ModuleScene Init()\n");

	return ret;

}

bool ModuleScene::Start() {

	bool ret = true;
	printf("ModuleScene Start()\n");
	printf(" ---> creating new neural network program,...");

	

	return ret;

}

update_status ModuleScene::PreUpdate(float dt) {

	update_status ret = update_status::UPDATE_CONTINUE;

	SDL_Texture* tex = App->sdlManager->load("..\imgs\panda.png",App->render->renderer);
	SDL_Rect* rect = nullptr;
	rect->x = 0;
	rect->y = 0;
	rect->w = 100;
	rect->h = 100;
	App->render->Blit(tex, 100, 100, rect);

	/*ImGui::BeginMainMenuBar();
	if (ImGui::BeginMenu("File"))
	{
		if (ImGui::MenuItem("New Neural Scenario"))
		{
			p_neuralNet = new NeuralNetwork(0);
			displayNeuralNetworkGui = true;
		}
		ImGui::EndMenu();
	}

	ImGui::EndMainMenuBar();
	
	if (displayNeuralNetworkGui) {
		p_neuralNet->displayGui();	
		p_neuralNet->updateNeuralNetwork();
	}*/
	

	return ret;
}

update_status  ModuleScene::Update(float dt) {

	update_status ret = update_status::UPDATE_CONTINUE;

	return ret;
}

update_status  ModuleScene::PostUpdate(float dt) {

	update_status ret = update_status::UPDATE_CONTINUE;



	return ret;
}


bool ModuleScene::CleanUp() {

	bool ret = true;


	return ret;

}


//############  UTILITY FUNCTIONS ############

NeuralNetwork* ModuleScene::getNeuralNetwork() {
	if (p_neuralNet != NULL) {
		return p_neuralNet;
	}

	return nullptr;
}