#include "Layer.h"


Layer::Layer(usint layerID):p_layerID(layerID) {

}

Layer::~Layer() {
	p2list_LayerNeurons.clear();
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

void Layer::addNeuron(usint neuronID) {
	Neuron* tmpNeuron = new Neuron(neuronID);
	p2list_LayerNeurons.add(tmpNeuron);
}

void Layer::removeNeuron(usint neuronID) {
	usint size = p2list_LayerNeurons.count();
	p2List_item<Neuron*>* data;
	data = p2list_LayerNeurons.getFirst();

	for (int i = 0; i < size; i++) {
		if (data->data->getNeuronID() == neuronID) {
			data->prev->next = data->next;
			data->next->prev = data->prev;
			p2list_LayerNeurons.del(data);
			break;
		}
		data = data->next;
	}
}

void Layer::deleteNeuronList() {
	p2list_LayerNeurons.clear();
}