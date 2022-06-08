#ifndef MODULE_SCENE_H
#define MODULE_SCENE_H

#include "Globals.h"
#include "Module.h"

#include "NeuralNetwork.h"
class debugging {
	debugging() {}
	~debugging(){}
};

class ModuleScene :public Module
{
public:

	 ModuleScene(Application* app, const char* moduleName, bool start_enabled = true);
	~ ModuleScene();


	bool Init(/*pugi::xml_node&*/);

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);

	// Called before quitting
	bool CleanUp();


	NeuralNetwork createNeuralnetwork(int layers);

	NeuralNetwork* getNeuralNetwork();

private:

	NeuralNetwork* p_neuralNet;

	bool displayNeuralNetworkGui = false;

};



#endif MODULE_SCENE_H