#ifndef NEURON_H
#define NEURON_H

#include "Globals.h"

class Neuron 
{
public:

	Neuron(usint neuronID,usint neuronLayer);
	~Neuron();

	float inputWeight;

	float input;
	float output;

	void modifyNeuronInputInformation(float newInput);
	usint getNeuronID();

	void displayGui();

	bool checkbox = false;

	void Destroy();

private:

	usint p_neuronLayerID;
	usint p_neuronID;

};




#endif NEURON_H