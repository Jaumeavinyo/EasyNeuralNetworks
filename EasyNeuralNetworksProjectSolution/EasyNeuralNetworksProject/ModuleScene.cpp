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

	p_neuralNet = new NeuralNetwork(0);

	
	printf("\n ---> NOW LETS ADD A LAYER AND THEN DELETE THE FIRST ONE");

	p_neuralNet->addLayer(0);
	p_neuralNet->addLayer(1);
	p_neuralNet->addLayer(2);
	printf("\n -------> layer added with id %i", p_neuralNet->p2list_Layers.getLast()->data->getLayerID());

	
	//p_neuralNet->deleteLayerList();

	//printf("\n --------> layer list deleted. now size is: %i", p_neuralNet->p2list_Layers.count());

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