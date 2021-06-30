#ifndef MODULE_NEURAL_NETWORK_H
#define MODULE_NEURAL_NETWORK_H




#include "Layer.h"
#include "Neuron.h"//#include "Globals.h" included in neuron

class NeuralNetwork 
{
public:
	NeuralNetwork(usint layers);
	~NeuralNetwork();

	p2List<Layer*> p2list_Layers; //ALL LAYERS

	void addLayer( usint layerID);
	/*ths function adds a Layer in the list. 
	Layer ID should be written automatically to avoid repeated IDs.
	*/
	void removeLayer(usint layerID);
	/*This function removes a Layer, erases all its neurons and data and 
	free the LayerID to be used again and deletes the layer from the LAyerList
	*/
	void deleteLayerList();
	/*this functions deletes and free all space for the list p2list_Layers*/
private:

	p2List<Neuron*> p_p2list_Neurons; //ALL NEURONS

};






#endif MODULE_NEURAL_NETWORK_H
