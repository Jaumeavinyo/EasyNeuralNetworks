#include "Neuron.h"
#include "..\ImGUI\imgui.h"
#include "..\ImGUI\imNODES\imnodes.h"
#include "App.h"

Neuron::Neuron(usint neuronID, usint neuronLayer) : p_neuronID(neuronID), p_neuronLayerID(neuronLayer)
{
}

Neuron::~Neuron()
{
}

void Neuron::modifyNeuronInputInformation(float newInput) {
	input = newInput;
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

	ImNodes::BeginInputAttribute(1);
	ImGui::Text("input");
	ImNodes::EndInputAttribute();

	ImNodes::BeginOutputAttribute(3);
	ImGui::Indent(40);//moves atributes to the right
	ImGui::Text("output");
	ImNodes::EndOutputAttribute();

	ImNodes::EndNode();
	//ImGui::End();
}