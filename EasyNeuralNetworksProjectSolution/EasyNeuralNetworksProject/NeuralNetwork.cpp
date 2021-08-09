#include "NeuralNetwork.h"
#include "..\ImGUI\imgui.h"
#include "..\ImGUI\imNODES\imnodes.h"
#include "App.h"
//############  CONSTRUCTORS ############

NeuralNetwork::NeuralNetwork(usint layers){

	for (int i = 0; i < layers; i++) {
		p2list_Layers.add(new Layer(i));
	}
	currentID = 0;
} 

NeuralNetwork::~NeuralNetwork()
{
	deleteLayerList();
}
//############  MAIN NEURAL NETWORK FUNCTIONS ############

bool NeuralNetwork::updateNeuralNetwork() {
	bool ret = true;
	return ret;
}

void NeuralNetwork::displayGui() {


	ImGui::Begin("Neural Network");

	if (ImGui::CollapsingHeader("Working Station")) {

		//LAYER CONFIG START
		if (ImGui::Button("Add Layer")) {
			Layer* tmp = new Layer(p2list_Layers.count());
			p2list_Layers.add(tmp);
		}
		static int selectedLayer = 0;
		ImGui::SliderInt("Active Layer", &selectedLayer, 0, p2list_Layers.count() - 1);

		//LAYER CONFIG END

		//NEURON CONFIG START
		{
			Layer* tmpL;
			p2list_Layers.at(selectedLayer, tmpL);
			if (ImGui::Button("Add Neuron")) {	
				Neuron* tmpN = new Neuron(p2list_Neurons.count(), selectedLayer);
				tmpL->addNeuron(tmpN);//add neuron to Layer list
			}
			ImGui::Text("Total Neurons: %d", p2list_Neurons.count());
			ImGui::Text("Neurons inside Layer: %d", tmpL->p2list_LayerNeurons.count());
		}
		
		//NEURON CONFIG END
	}
	
	//NEURON DISPLAYGUI START
	ImNodes::BeginNodeEditor();

	if (p2list_Layers.count() > 0) {
		p2List_item<Layer*>* layerIterator;
		layerIterator = p2list_Layers.getFirst();
		if (p2list_Neurons.count() > 0) {
			for (int i = 0; i < p2list_Layers.count(); i++) {
				layerIterator->data->displayGui();
				layerIterator = layerIterator->next;
			}
		}
		
	}

	for (const Link& link : links) {
		ImNodes::Link(link.id, link.input_attr, link.output_attr);
	}
	
	ImNodes::EndNodeEditor();
	
	{
		Link link;
		if (ImNodes::IsLinkCreated(&link.input_attr, &link.output_attr))
		{
			link.id = ++currentID;
			links.push_back(link);
		}
	}

	{
		int link_id;
		if (ImNodes::IsLinkDestroyed(&link_id))
		{
			auto iter = std::find_if(
				links.begin(), links.end(), [link_id](const Link& link) -> bool {
					return link.id == link_id;
				});
			assert(iter != links.end());
			links.erase(iter);
		}
	}

	ImGui::End();

}

//############  UTILITY FUNCTIONS ############

void NeuralNetwork::createLink(int inputL, int outputL, int ID) {
	Link link;
	link.input_attr = inputL;
	link.output_attr = outputL;
	link.id = ID;

}

void NeuralNetwork::addLayer(usint layerID) {
	
	Layer* tmpLayer = new Layer(layerID);
	//tmpLayer->setLayerID(layerID);literal lo hago encima
	
	p2list_Layers.add(tmpLayer);
}

void NeuralNetwork::removeLayer(usint LayerID) {

	usint size = p2list_Layers.count();
	p2List_item<Layer*>* data;
	data = p2list_Layers.getFirst();

	for (int i = 0; i < size; i++) {
		if (data->data->getLayerID() == LayerID) {
			data->prev->next = data->next;
			data->next->prev = data->prev;
			p2list_Layers.del(data);
			break;
		}
		data = data->next;
	}
}

void NeuralNetwork::deleteLayerList() {
	p2List_item<Layer*>* iterator;
	iterator = p2list_Layers.getFirst();
	for (int i = 0; i < p2list_Layers.count(); i++) {
		iterator->data->p2list_LayerNeurons.clear();
	}
	p2list_Layers.clear();
}

