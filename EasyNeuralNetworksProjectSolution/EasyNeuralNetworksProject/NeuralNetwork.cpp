#include "NeuralNetwork.h"
#include "..\ImGUI\imgui.h"
#include "..\ImGUI\imNODES\imnodes.h"
#include "..\ImGUI\imNODES\imnodes_internal.h"
#include "App.h"
//############  CONSTRUCTORS ############

NeuralNetwork::NeuralNetwork(usint layers){

	for (int i = 0; i < layers; i++) {
		p2list_Layers.add(new Layer(i));
	}
	currentID = 0;
	deleteItem = false;
	pinID = 0;
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
				int newID = p2list_Neurons.count();
				Neuron* tmpN = new Neuron(p2list_Neurons.count(), selectedLayer);
				tmpL->addNeuron(tmpN);
			}
			ImGui::Text("Total Neurons: %d", p2list_Neurons.count());
			ImGui::Text("Neurons inside Layer: %d", tmpL->p2list_LayerNeurons.count());
		}
		
		if ((App->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT)) {	
			deleteItem = true;
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
		ImNodes::Link(link.id, link.input_pin, link.output_pin);
	}
	
	ImNodes::EndNodeEditor();
	
	ImNodesManagement();

	ImGui::End();

}


void NeuralNetwork::ImNodesManagement() {

	bool ret = true;

	Link link;
	ImNodesEditorContext& editor = ImNodes::EditorContextGet();
	if (ImNodes::IsLinkCreated(&link.input_pin, &link.output_pin)){
		//link.id = links.size();//this can be done if when deleting a link, all links reorder(erase should reorder automaticly) | (old code)/*(link.input_pin);*/
		
		//buscar el comunicator con pinID == output_pin y en el reciever node pasarle el id del nodo guardado en comunicator
		int tmpNodeID;
		for (int i = 0; i < comunicators.size(); i++) {
			if (comunicators[i].pin_ID == link.output_pin) {
				tmpNodeID = comunicators[i].neuron_ID;
			}
		}

		link.reciever_node = (link.output_pin >> 8);
		link.sender_node = (link.input_pin >> 16);//left part of the link starts in the output_pin from node "n". this way we know: n.ID = n>>16 because output_pin id is "BeginOutputAttribute(node_id << 16)"

		//link id will be the concatenation of 2 integers that will be "sender_node ID + reciever_node ID"
		int prevID = link.sender_node;
		int nextID = link.reciever_node;

		int times = 1;
		while (times <= nextID)
			times *= 10;
		
		link.id = prevID * times + nextID;; //this way prevneuronId is the sender and next uis the
		links.push_back(link);

		Neuron* tmpNeuron;
		Neuron* tmpPrevNeuron;
		p2list_Neurons.at(link.sender_node, tmpPrevNeuron);
		p2list_Neurons.at(link.reciever_node, tmpNeuron);

		int prevNeuronID = link.sender_node;
		
		tmpNeuron->previousNeuronsIDs.push_back(prevNeuronID);
		tmpPrevNeuron->nextNeuronsIDs.push_back(tmpNeuron->getNeuronID());
	}

	

	int link_id;//Destroy links when they are called to be destroyed
	if (ImNodes::IsLinkDestroyed(&link_id)){
		auto iter = std::find_if(
			links.begin(), links.end(), [link_id](const Link& link) -> bool {
				return link.id == link_id;
			});
		assert(iter != links.end());
		links.erase(iter);
	}
	
	int itemHovered;//Destroy selected link
	if (ImGui::GetIO().MouseClicked[2] && ImNodes::IsLinkHovered(&itemHovered)) {
		usint counter = 0;
		//std::vector<int>::iterator it = myvector.begin()
		std::vector<Link>::iterator iter = links.begin();
		for ( Link& link : links) {
			if (link.id == itemHovered) {

				Link* tmp = &link;
				links.erase(iter);
				
				break;
			}
			if (links.size() > counter ) {
				iter++;
				counter++;
			}
				
		}
	}

	
}
//############  UTILITY FUNCTIONS ############

void NeuralNetwork::createLink(int inputL, int outputL, int ID) {
	Link link;
	link.input_pin = inputL;
	link.output_pin = outputL;
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

