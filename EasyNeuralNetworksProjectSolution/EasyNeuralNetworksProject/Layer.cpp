#include "Layer.h"
#include "..\ImGUI\imgui.h"
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
		printf("GUI- %i\n", i);
		if (i == 3) {
			printf("aaa");
		}		
		auxIterator = iterator->next;//this exists to avoid having a null next when destroying a node inside the displaygui function
		iterator->data->displayGui();
		iterator = auxIterator;
	}
	
}

void Layer::addNeuron(Neuron *neuron) {
	p2list_LayerNeurons.add(neuron);
}

void Layer::insertNeuron(uint pos, Neuron* neuron) {
	p2list_LayerNeurons.insert(pos, neuron);
}

usint Layer::getLayerID() {
	return p_layerID;
}



void Layer::setLayerID(usint layerID) {
	p_layerID = layerID;
}

void Layer::addNewNeuron(usint neuronID,usint neuronLayer) {
	Neuron* tmpNeuron = new Neuron(neuronID, neuronLayer);
	p2list_LayerNeurons.add(tmpNeuron);
}

void Layer::removeNeuron(usint neuronID) {
	usint size = p2list_LayerNeurons.count();
	p2List_item<Neuron*>* neuronItem;
	neuronItem = p2list_LayerNeurons.getFirst();

	for (int i = 0; i < size; i++) {
		if (neuronItem->data->getNeuronID() == neuronID) {
			p2list_LayerNeurons.del(neuronItem);
			break;
		}
		neuronItem = neuronItem->next;
	}
}

void Layer::deleteNeuronList() {
	p2list_LayerNeurons.clear();
}

//############  UTILITY FUNCTIONS ############