#ifndef NEURON_H
#define NEURON_H

#include "Globals.h"
#include "StandartLibraries.h"

struct pinSaver {
	int pin_ID;
	int pin_count;
	
};

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

	std::vector<pinSaver> pinSavers;
	int previousNeuronID;//delete this two variables
	int nextNeuronID;

	void modifyNeuronInputInformation(float newInput);
	usint getNeuronID();

	void displayGui();

	void Destroy();


	void addPin();
	void addNewInputPin();
	void addNewOutputPin();


	int inputCount;
	int outputCount;
	bool inputPinExists;
	bool outputPinExists;

private:

	usint p_neuronLayerID;
	usint p_neuronID;

};




#endif NEURON_H