#include "Neuron.h"
#include "..\ImGUI\imgui.h"
#include "..\ImGUI\imNODES\imnodes.h"
#include "App.h"

struct Link;

Neuron::Neuron(usint neuronID, usint neuronLayer) : p_neuronID(neuronID), p_neuronLayerID(neuronLayer)
{
	Link link;

}

Neuron::~Neuron()
{
}

void Neuron::modifyNeuronInputInformation(float newInput) {
	inputValue = newInput;
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
	if (!((nextNeuronID || previousNeuronID) == NULL)){
		ImGui::Text("prevNode: %i nextNode:%i", previousNeuronID, nextNeuronID);
	}
	if (ImGui::Button("x")) {
		Destroy();
	}
	ImNodes::EndNodeTitleBar();
	
	ImNodes::BeginInputAttribute(p_neuronID <<8);
	ImGui::Text("input attr:%i",p_neuronID << 8);//to obtain the node id, just do inputPinID >> 8
	ImNodes::EndInputAttribute();

	ImNodes::BeginOutputAttribute(p_neuronID <<16);
	ImGui::Indent(40);//moves atributes to the right
	ImGui::Text("output attr:%i",p_neuronID << 16);//to obtain the node id, just do outputPinID >> 16
	ImNodes::EndOutputAttribute();

	ImNodes::EndNode();
	//ImGui::End();
}