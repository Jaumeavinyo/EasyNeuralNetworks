#ifndef MODULE_NEURAL_NETWORK_H
#define MODULE_NEURAL_NETWORK_H


#include "Layer.h"
#include "Neuron.h"//#include "Globals.h" included in neuron
#include "Module.h"
#include <vector>
#include <xutility>
struct Link {
	int id;
	int input_attr, output_attr;
};

class NeuralNetwork 
{
public:
	NeuralNetwork(usint layers);
	~NeuralNetwork();

	p2List<Neuron*> p2list_Neurons; //ALL NEURONS
	p2List<Layer*> p2list_Layers; //ALL LAYERS
	std::vector<Link> links;      //ALL LINKS

	void displayGui();

	bool updateNeuralNetwork();

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
	void createLink(int input_attr, int output_attr, int ID);

public:

	int currentID;

private:

	

};






#endif MODULE_NEURAL_NETWORK_H
