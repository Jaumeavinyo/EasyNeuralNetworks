#include "Layer.h"
#include "lib\ImGUI\imgui.h"
#include "App.h"
//############  CONSTRUCTORS ############

Layer::Layer(usint layerID):p_layerID(layerID) {
	
}

Layer::~Layer() {
	p2list_LayerNeurons.clear();
}


//############  MAIN Module FUNCTIONS ############

void Layer::displayGui() {
	
	p2List_item<Neuron*>* iterator;
	p2List_item<Neuron*>* auxIterator;
	iterator = p2list_LayerNeurons.getFirst();


	for (int i = 0; i < p2list_LayerNeurons.count(); i++) {
		auxIterator = iterator->next;//this exists to avoid having a null next when destroying a node inside the displaygui function
		iterator->data->displayGui();
		iterator = auxIterator;
	}
	
}
/*Add a neuron to Layer and Network lists*/
void Layer::addNeuron(Neuron *neuron) {
	p2list_LayerNeurons.add(neuron);
	App->scene->getNeuralNetwork()->p2list_Neurons.add(neuron);
}

void Layer::addNeuron(Neuron* neuron, usint nextLayerNeurons) {
	neuron->_nextLayerNeurons = nextLayerNeurons;
	p2list_LayerNeurons.add(neuron);
	App->scene->getNeuralNetwork()->p2list_Neurons.add(neuron);
}

usint Layer::getLayerID() {
	return p_layerID;
}



void Layer::setLayerID(usint layerID) {
	p_layerID = layerID;
}



void Layer::removeNeuron(usint neuronID) {
	usint size1 = p2list_LayerNeurons.count();
	p2List_item<Neuron*>* neuronItem1;
	neuronItem1 = p2list_LayerNeurons.getFirst();

	usint size2 = App->scene->getNeuralNetwork()->p2list_Neurons.count();
	p2List_item<Neuron*>* neuronItem2;
	neuronItem2 = App->scene->getNeuralNetwork()->p2list_Neurons.getFirst();

	for (int i = 0; i < size1; i++) {//delete from Layer list
		if (neuronItem1->data->getNeuronID() == neuronID) {
			p2list_LayerNeurons.del(neuronItem1);
			
			break;
		}
		neuronItem1 = neuronItem1->next;
	}
	for (int i = 0; i < size2; i++) {//delete from Neural Network list
		if (neuronItem2->data->getNeuronID() == neuronID) {
			App->scene->getNeuralNetwork()->p2list_Neurons.del(neuronItem2);

			break;
		}
		neuronItem2 = neuronItem2->next;
	}
}

void Layer::deleteNeuronList() {
	p2list_LayerNeurons.clear();
}

//############  UTILITY FUNCTIONS ############