#ifndef NEURON_H
#define NEURON_H

#include "Globals.h"
#include "StandartLibraries.h"


class Layer;

struct inputPinSaver {
	int pin_ID;
	int pin_count;
	
};

struct outputPinSaver {
	int pin_ID;
	int pin_count;
};

struct weight {
	
	float deltaWeight;
	float weight;
};

class Neuron 
{
public:

	
	Neuron(usint neuronID, usint neuronLayer, usint myIndexInTheList, usint nextLayerNeurons = 0);
	~Neuron();

	std::vector<weight> outputWeights = {};//store all input weights from other neurons
	double outputValue;//value after operating
	std::vector<double> inputValues = {};

	std::vector<float> bias = {};
		
	

	std::vector<int> previousNeuronsIDs = {  };
	std::vector<int> nextNeuronsIDs = {  };

	std::vector<inputPinSaver>  inputPinSavers;
	std::vector<outputPinSaver>  outputPinSavers;
	int previousNeuronID;//delete this two variables
	int nextNeuronID;

	void modifyNeuronInputInformation(float newInput);
	usint getNeuronID();
	
	void displayGui();

	void Destroy();

	void addNewInputPin();
	void addNewOutputPin();

	void displayInputPins();
	void displayOutputPins();

	void setOutputVal(double outputVal) { outputValue = outputVal; }
	void feedForward( Layer &prevLayer);
	double transferFunction(double num);
	double transferFunctionDerivative(double num);

	void calculateOutputGradients(double targetVal);
	void calculateHiddenGradients(const Layer &nextL);
	void updateInputWeights(Layer &prevL);

	double sumDOW(const Layer& nextL)const;

	int inputCount;
	int increaseInputs;
	int outputCount;
	int increaseOutputs;
	bool inputPinExists;
	bool outputPinExists;
	bool inputCountPrevAssignation; //true if before creating the neuron we already know prev layer config
	bool outputCountPrevAssignation; //true if before creating the neuron we already know next layer config
private:

	usint p_neuronLayerID;
	usint p_neuronID;
	double p_gradient;
	usint p_myIndexInTheList;
public:

	usint _nextLayerNeurons;

public:

	double ETA = 0.15; //0.0-1.0 net training rate
	double ALPHA = 0.5;//0.0-...multiplier of the last weight change


};




#endif NEURON_H