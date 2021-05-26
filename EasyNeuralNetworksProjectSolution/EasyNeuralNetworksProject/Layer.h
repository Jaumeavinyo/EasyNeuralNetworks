#ifndef LAYER_H
#define LAYER_H

class Layer
{
public:
	Layer();
	~Layer();

	p2List<Neuron*> p2list_LayerNeurons; //ALL NEURONS INSIDE THIS LAYER

private:

};

Layer::Layer()
{
}

Layer::~Layer()
{
}

#endif LAYER_H
