#ifndef MODULE_NEURAL_NETWORK_H
#define MODULE_NEURAL_NETWORK_H


#include "Layer.h"
#include "Neuron.h"//#include "Globals.h" included in neuron
#include "Module.h"
#include "Globals.h"
#include <xutility>



struct Link {
	int id;
	int input_pin/*akka right, akka reciever_node*/, output_pin/*akka sender_node*/;
	int sender_node, reciever_node;
};

struct comunicator {//relates id from BeguinInPutAttribute and neuron ID
	int pin_ID;
	int neuron_ID;
};

class NeuralNetwork 
{
public:
	NeuralNetwork(usint layers);
	~NeuralNetwork();

	p2List<Neuron*> p2list_Neurons; //ALL NEURONS
	p2List<Layer*> p2list_Layers; //ALL LAYERS
	std::vector<Link> links;      //ALL LINKS
	std::vector<comunicator> comunicators; //All comunicators between ImNodesIDs and the program

	std::vector<unsigned> TOP;
	std::vector<double> inputVals;
	std::vector<double> targetVals;
	std::vector<double> resultVals;

	void feedForward(const std::vector<double>& inputVals);
	void backPropagation(const std::vector<double>& TargetVals);
	void getResults(std::vector<double>& resultVals);

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

	void ImNodesManagement();
	void NodeEditorManagement();
	void workStationManagement();

	void generateAutomaticNetwork(usint config);

public:
	int count = 0;
	int currentID;
	bool deleteItem;
	int pinID; //used by neurons to assign IDs to pins
	int userSelectedAmmountOfLayers;

	int train = 0;
	bool trainNow= false;
private:

	double p_netError;
	double p_netRecentAverageError;
	double p_netRecentSmoothingFactor=500;
};






#endif MODULE_NEURAL_NETWORK_H
