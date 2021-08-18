#ifndef NEURON_H
#define NEURON_H

#include "Globals.h"

class Neuron 
{
public:

	Neuron(usint neuronID,usint neuronLayer);
	~Neuron();

	float inputWeight;

	float inputValue;
	int inputID;
	float outputValue;
	int outputID;

	void modifyNeuronInputInformation(float newInput);
	usint getNeuronID();

	void displayGui();

	bool checkbox = false;

	void Destroy();
	float floata =0.4;
private:

	usint p_neuronLayerID;
	usint p_neuronID;

};




#endif NEURON_H