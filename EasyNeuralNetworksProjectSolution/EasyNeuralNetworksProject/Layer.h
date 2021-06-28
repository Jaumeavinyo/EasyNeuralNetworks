#ifndef LAYER_H
#define LAYER_H

#include "Neuron.h"
#include "Globals.h"

class Layer
{
public:
	Layer();
	~Layer();

	p2List<Neuron*> p2list_LayerNeurons; //ALL NEURONS INSIDE THIS LAYER

	void addNeuron(Neuron *neuron);
	void insertNeuron(unsigned int pos, Neuron* neuron);

private:

};



#endif LAYER_H
