#ifndef MODULE_NEURAL_NETWORK_H
#define MODULE_NEURAL_NETWORK_H

#include "Globals.h"
#include "Module.h"

#include "Layer.h"
#include "Neuron.h"

class ModuleNeuralNetwork : public Module
{
public:
	ModuleNeuralNetwork();
	~ModuleNeuralNetwork();

	p2List<Layer*> p2list_Layers; //ALL LAYERS

private:
	p2List<Neuron*> p_p2list_Neurons; //ALL NEURONS
};






#endif MODULE_NEURAL_NETWORK_H
