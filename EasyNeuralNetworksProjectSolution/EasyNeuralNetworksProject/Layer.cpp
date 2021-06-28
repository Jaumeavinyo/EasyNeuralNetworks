#include "Layer.h"


Layer::Layer() {

}

Layer::~Layer() {

}

void Layer::addNeuron(Neuron *neuron) {
	p2list_LayerNeurons.add(neuron);
}

void Layer::insertNeuron(unsigned int pos, Neuron* neuron) {
	p2list_LayerNeurons.insert(pos, neuron);
}

