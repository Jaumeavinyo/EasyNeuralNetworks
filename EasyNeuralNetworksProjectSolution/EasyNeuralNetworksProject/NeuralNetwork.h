#ifndef MODULE_NEURAL_NETWORK_H
#define MODULE_NEURAL_NETWORK_H




#include "Layer.h"
#include "Neuron.h"//#include "Globals.h" included in neuron

class NeuralNetwork 
{
public:
	NeuralNetwork();
	~NeuralNetwork();

	p2List<Layer*> p2list_Layers; //ALL LAYERS

private:

	p2List<Neuron*> p_p2list_Neurons; //ALL NEURONS

};






#endif MODULE_NEURAL_NETWORK_H
