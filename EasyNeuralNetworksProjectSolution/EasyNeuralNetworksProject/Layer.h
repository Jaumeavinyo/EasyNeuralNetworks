#ifndef LAYER_H
#define LAYER_H

#include "Neuron.h"
#include "Globals.h"

class Layer
{
public:
	Layer(usint layerID);
	~Layer();

	p2List<Neuron*> p2list_LayerNeurons;           //ALL NEURONS INSIDE THIS LAYER

	double bias;

	void addNeuron(Neuron *neuron);                //adds neuron at the end of the list
	void addNeuron(Neuron* neuron, usint nextLayerNeurons);
	void insertNeuron(uint pos, Neuron* neuron);   //insert neuron at the desired position

	usint getLayerID();
	
	void setLayerID(usint layerID);

	
	void removeNeuron(usint neuronID);
	void deleteNeuronList();
	
	void displayGui();

	bool deletingItem = false;
private:

	usint p_layerID;
	
};



#endif LAYER_H
