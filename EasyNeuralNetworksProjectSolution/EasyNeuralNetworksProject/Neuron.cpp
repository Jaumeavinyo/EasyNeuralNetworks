#include "Neuron.h"
#include "NeuralNetwork.h"
#include "..\ImGUI\imgui.h"
#include "..\ImGUI\imNODES\imnodes.h"
#include "App.h"

struct Link;



Neuron::Neuron(usint neuronID, usint neuronLayer, usint myIndexInTheList, usint nextLayerNeurons ) : p_neuronID(neuronID), p_neuronLayerID(neuronLayer), p_myIndexInTheList(myIndexInTheList), _nextLayerNeurons(nextLayerNeurons)
{
	Link link;
	inputCount = 0;
	outputCount = 0;
	increaseInputs = increaseOutputs = nextLayerNeurons;
	increaseOutputs = _nextLayerNeurons;

	inputPinExists = false;
	outputPinExists = false;
	
	for (int w = 0; w < nextLayerNeurons; w++) {
		weight tmpW;
		tmpW.weight = rand() / double(RAND_MAX);
		//tmpW.deltaWeight = rand() / double(RAND_MAX); no es el problema de la repeticion de output values
		outputWeights.push_back(tmpW);

	}
}

Neuron::~Neuron()
{
}

void Neuron::modifyNeuronInputInformation(float newInput) {
	//inputValue = newInput;
}

usint Neuron::getNeuronID() {
	return p_neuronID;
}

void Neuron::Destroy() {
	NeuralNetwork* tmpNeuralNet = App->scene->getNeuralNetwork();
	Layer* tmpLayer;
	tmpNeuralNet->p2list_Layers.at(p_neuronLayerID, tmpLayer);//COPY A POINTER TO THE LAYER WHERE THE NEURON EXISTS
	if (tmpLayer->getLayerID() == p_neuronLayerID) {
		tmpLayer->deletingItem = true;
		tmpLayer->removeNeuron(p_neuronID);//REMOVES NEURON FROM LAYER NEURONS LIST
		
	}
}

void Neuron::displayGui() {
	//ImGui::Begin("Neuron");
	
	
	ImNodes::BeginNode(p_neuronID);
	
	ImNodes::BeginNodeTitleBar();
	ImGui::Text("ID: %i Layer:%i",p_neuronID, p_neuronLayerID);
	if (ImGui::Button("x")) {
		Destroy();
	}
	ImNodes::EndNodeTitleBar();

	if (ImGui::Button("Add input")||increaseInputs != 0) {
		if (increaseInputs > 0) {
			increaseInputs--;
		}
		addNewInputPin();
	}

	if (inputCount > 0) { //if there should be more inputs
		displayInputPins();
	}
	if (ImGui::Button("Add output") || increaseOutputs != 0) {
		if(increaseOutputs > 0) {
			increaseOutputs--;
		}
		addNewOutputPin();
	}

	if (outputCount > 0) { //if there should be more inputs
		displayOutputPins();
	}

	

	ImNodes::EndNode();
	//ImGui::End();
}

void Neuron::addNewInputPin() {
	
	inputPinSaver saver;
	saver.pin_count = inputCount;
	saver.pin_ID = App->scene->getNeuralNetwork()->pinID;
	inputPinSavers.push_back(saver);

	comunicator tmpComunicator;
	tmpComunicator.neuron_ID = p_neuronID;
	tmpComunicator.pin_ID = App->scene->getNeuralNetwork()->pinID;
	App->scene->getNeuralNetwork()->comunicators.push_back(tmpComunicator);


	App->scene->getNeuralNetwork()->pinID++;
	inputCount++;
}

void Neuron::addNewOutputPin() {
	

	outputPinSaver saver;
	saver.pin_count = outputCount;
	saver.pin_ID = App->scene->getNeuralNetwork()->pinID;
	outputPinSavers.push_back(saver);

	comunicator tmpComunicator;
	tmpComunicator.neuron_ID = p_neuronID;
	tmpComunicator.pin_ID = App->scene->getNeuralNetwork()->pinID;
	App->scene->getNeuralNetwork()->comunicators.push_back(tmpComunicator);

	App->scene->getNeuralNetwork()->pinID++;
	outputCount++;
}

void Neuron::displayInputPins() {
	for (int i = 0; i < inputCount; i++) {//paint all inputs
		int tmpPinID;
		for (int n = 0; n < inputPinSavers.size(); n++) {//find the unique pinID saved in pinSavers allong with the count in where they where saved
			if (i == inputPinSavers[n].pin_count) {
				tmpPinID = inputPinSavers[n].pin_ID;
			}
		}

		ImNodes::BeginInputAttribute(tmpPinID);

		ImGui::Text("input attr:%i", tmpPinID);//to obtain the node id, just do inputPinID >> 8
		ImNodes::EndInputAttribute();
	}
}

void Neuron::displayOutputPins() {
	for (int i = 0; i < outputCount; i++) {//paint all inputs
		int tmpPinID;
		for (int n = 0; n < outputPinSavers.size(); n++) {//find the unique pinID saved in pinSavers allong with the count in where they where saved
			if (i == outputPinSavers[n].pin_count) {
				tmpPinID = outputPinSavers[n].pin_ID;
			}
		}

		ImNodes::BeginOutputAttribute(tmpPinID);

		ImGui::Text("output attr:%i", tmpPinID);
		ImNodes::EndOutputAttribute();
	}
}

void Neuron::feedForward(Layer &prevLayer) {
	double sum = 0.0;

	p2List_item<Neuron*>* neuronIterator2;
	neuronIterator2 = prevLayer.p2list_LayerNeurons.getFirst();
	for (int n = 0; n < prevLayer.p2list_LayerNeurons.count(); n++) {
		sum = sum + neuronIterator2->data->outputValue * neuronIterator2->data->outputWeights[p_myIndexInTheList].weight;
		neuronIterator2->next;
	}

	//PC
	//to add a BIAS neuron virtually:
	
	//END PC
	outputValue = transferFunction(sum);//also called activation function
}

double Neuron::transferFunction(double x) {

	// tanh    the output range is [-1.0...1.0]
	return tanh(x);
}

double Neuron::transferFunctionDerivative(double x) {
	return 1.0 - x * x;
}

void Neuron::calculateOutputGradients(double targetVal) {
	double delta = targetVal - outputValue;
	p_gradient = delta * Neuron::transferFunctionDerivative(outputValue);
}

void Neuron::calculateHiddenGradients(const Layer& nextL) {
	double dow = sumDOW(nextL);
	p_gradient = dow * Neuron::transferFunctionDerivative(outputValue);
	printf("·");
}

double Neuron::sumDOW(const Layer& nextL)const {
	double sum = 0.0;

	p2List_item<Neuron*>* neuronIterator;
	neuronIterator = nextL.p2list_LayerNeurons.getFirst();
	for (int i = 0; i < nextL.p2list_LayerNeurons.count(); i++) {
		sum += outputWeights[i].weight * neuronIterator->data->p_gradient;

		neuronIterator->next;
	}
	return sum; 
}

void Neuron::updateInputWeights(Layer& prevL) {//weights to update are inside weighs type list of neurons from prev layer that are our inputweights

	p2List_item<Neuron*>* neuronIterator;
	neuronIterator = prevL.p2list_LayerNeurons.getFirst();
	for (int n = 0; n < prevL.p2list_LayerNeurons.count(); n++) {
		double oldDeltaWeight = neuronIterator->data->outputWeights[n].deltaWeight;

		double newDeltaWeight = ETA * neuronIterator->data->outputValue * p_gradient + ALPHA * oldDeltaWeight;
		
		neuronIterator->data->outputWeights[p_myIndexInTheList].deltaWeight = newDeltaWeight;
		neuronIterator->data->outputWeights[p_myIndexInTheList].weight += newDeltaWeight;
		neuronIterator->next;
	}
}