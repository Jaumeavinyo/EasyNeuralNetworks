#ifndef NEURON_H
#define NEURON_H

#include "Globals.h"
#include "StandartLibraries.h"
class Neuron 
{
public:

	Neuron(usint neuronID,usint neuronLayer);
	~Neuron();

	std::vector<float> inputWeights = {};
	std::vector<float>inputValues = {};
	std::vector<float> bias = {};
		
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
	int inputCount;
private:

	usint p_neuronLayerID;
	usint p_neuronID;

};




#endif NEURON_H