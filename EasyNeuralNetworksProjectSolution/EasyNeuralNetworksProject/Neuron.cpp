#include "Neuron.h"
#include "NeuralNetwork.h"
#include "..\ImGUI\imgui.h"
#include "..\ImGUI\imNODES\imnodes.h"
#include "App.h"

struct Link;

Neuron::Neuron(usint neuronID, usint neuronLayer) : p_neuronID(neuronID), p_neuronLayerID(neuronLayer)
{
	Link link;
	inputCount = 0;
	outputCount = 0;
	inputPinExists = false;
	outputPinExists = false;
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
	
	//ImNodes::BeginInputAttribute(App->scene->getNeuralNetwork()->pinID);
	//if (!inputPinExists) {//if don't do this, pinID grows every frame for the standard input and output pins
	//	inputPinExists = true;
	//	addPin();
	//}
	//ImGui::Text("input attr:%i", App->scene->getNeuralNetwork()->pinID);
	//ImNodes::EndInputAttribute();

	if (ImGui::Button("Add input")) {
		addNewInputPin();
	}

	if (inputCount > 0) { //if there should be more inputs
		for (int i = 1; i < inputCount; i++) {//paint all inputs
			int tmpPinID;
			for (int n = 0; n < pinSavers.size(); n++) {//find the unique pinID saved in pinSavers allong with the count in where they where saved
				if (i == pinSavers[n].pin_count) {
					tmpPinID = pinSavers[n].pin_ID;
				}
			}

			ImNodes::BeginInputAttribute(tmpPinID);

			ImGui::Text("input attr:%i", tmpPinID );//to obtain the node id, just do inputPinID >> 8
			ImNodes::EndInputAttribute();
		}
	}

	ImNodes::BeginOutputAttribute(p_neuronID <<16);
	ImGui::Indent(40);//moves atributes to the right
	ImGui::Text("output attr:%i",p_neuronID << 16);//to obtain the node id, just do outputPinID >> 16
	ImNodes::EndOutputAttribute();

	ImNodes::EndNode();
	//ImGui::End();
}


void Neuron::addPin() {
	comunicator tmpComunicator;
	tmpComunicator.neuron_ID = p_neuronID;
	tmpComunicator.pin_ID = App->scene->getNeuralNetwork()->pinID;

	App->scene->getNeuralNetwork()->comunicators.push_back(tmpComunicator);

	App->scene->getNeuralNetwork()->pinID++;
}


void Neuron::addNewInputPin() {
	inputCount++;

	pinSaver saver;
	saver.pin_count = inputCount;
	saver.pin_ID = App->scene->getNeuralNetwork()->pinID;

	pinSavers.push_back(saver);

	App->scene->getNeuralNetwork()->pinID++;
}

void Neuron::addNewOutputPin() {
	outputCount++;

	pinSaver saver;
	saver.pin_count = outputCount;
	saver.pin_ID = App->scene->getNeuralNetwork()->pinID;

	pinSavers.push_back(saver);

	App->scene->getNeuralNetwork()->pinID++;
}