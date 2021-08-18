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
		ImNodes::Link(link.id, link.input_attr, link.output_attr);
	}
	
	ImNodes::EndNodeEditor();
	
	ImNodesManagement();

	ImGui::End();

}


void NeuralNetwork::ImNodesManagement() {

	bool ret = true;

	Link link;
	ImNodesEditorContext& editor = ImNodes::EditorContextGet();
	if (ImNodes::IsLinkCreated(&link.input_attr, &link.output_attr)){
		link.id = link.input_attr;
		links.push_back(link);

		
		
		

	}
	//ids de editor.Links.Pool[i].EndPinIdx y editor.Links.Pool[i].StartPinIdx no son los mismos que los que se asignan a los link en la lista links
	for (Link& linksIter : links) {//my list
		for (int i = 0; i < editor.Links.Pool.Size; i++) {//internal ImNodes list
			if (linksIter.input_attr == editor.Links.Pool[i].StartPinIdx && linksIter.output_attr == editor.Links.Pool[i].EndPinIdx) {//if a link between my list[i] and internat ImNodes list[i2] match
				for (int j = 0; i < editor.Pins.Pool.Size; j++) {
					linksIter.input_node = editor.Pins.Pool[linksIter.input_attr].ParentNodeIdx;
					linksIter.output_node = editor.Pins.Pool[linksIter.output_attr].ParentNodeIdx;
				}
			}
		}

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

