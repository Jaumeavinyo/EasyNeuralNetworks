#include "Layer.h"


Layer::Layer(usint layerID):p_layerID(layerID) {

}

Layer::~Layer() {

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