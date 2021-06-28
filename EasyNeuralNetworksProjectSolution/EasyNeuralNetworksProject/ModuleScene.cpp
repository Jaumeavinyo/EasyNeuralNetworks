#include "ModuleScene.h"

#include "App.h"


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
	printf(" ---> creating new neural network...");

	p_neuralNet = new NeuralNetwork();

	int count = p_neuralNet->p2list_Layers.count();
	
	printf(" ------> count of layers is %i", &count);

	return ret;

}

update_status ModuleScene::PreUpdate(float dt) {

	update_status ret = update_status::UPDATE_CONTINUE;


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