#include "Neuron.h"


Neuron::Neuron(usint neuronID):p_NeuronID(neuronID)
{
}

Neuron::~Neuron()
{
}

void Neuron::modifyNeuronInputInformation(float newInput) {
	input = newInput;
}

usint Neuron::getNeuronID() {
	return p_NeuronID;
}