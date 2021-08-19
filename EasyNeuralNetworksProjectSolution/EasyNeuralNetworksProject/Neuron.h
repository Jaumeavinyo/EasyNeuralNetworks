#ifndef NEURON_H
#define NEURON_H

#include "Globals.h"
#include "StandartLibraries.h"
class Neuron 
{
public:

	Neuron(usint neuronID,usint neuronLayer);
	~Neuron();

	float inputWeight;

	float inputValue;//value that enters untouched from last neuron
	float outputValue;//value after operating
	
	std::vector<int> previousNeuronsIDs = {  };
	std::vector<int> nextNeuronsIDs = {  };

	int previousNeuronID;//delete this two variables
	int nextNeuronID;

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