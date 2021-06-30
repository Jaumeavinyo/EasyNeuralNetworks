#ifndef NEURON_H
#define NEURON_H

#include "Globals.h"

class Neuron
{
public:
	Neuron(usint neuronID);
	~Neuron();

	float inputWeight;

	float input;
	float output;

	void modifyNeuronInputInformation(float newInput);
	usint getNeuronID();

private:

	
	usint p_NeuronID;
};




#endif NEURON_H