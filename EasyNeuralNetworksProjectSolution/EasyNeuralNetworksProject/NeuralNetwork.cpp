#include "NeuralNetwork.h"
#include "lib\ImGUI\imgui.h"
#include "lib\ImGUI\imNODES\imnodes.h"
#include "lib\ImGUI\imNODES\imnodes_internal.h"
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

	//destroy layer if empty
	p2List_item<Layer*>* layerIterator;
	layerIterator = p2list_Layers.getFirst();
	for (int i = 0; i < p2list_Layers.count(); i++) {
		if (layerIterator->data->p2list_LayerNeurons.count() == 0) {
			p2List_item<Layer*>* tmpLayerIter = layerIterator;
			layerIterator = layerIterator->next;
			p2list_Layers.del(tmpLayerIter);
		}
		else {
			layerIterator = layerIterator->next;
		}	
	}

	return ret;
}

void NeuralNetwork::displayGui() {


	ImGui::Begin("Neural Network");//##################__________BEGIN_____________###########################
	
	ImNodes::BeginNodeEditor();
	NodeEditorManagement();
	ImNodes::EndNodeEditor();

	ImNodesManagement();

	ImGui::End();//##################__________END_____________###########################
	

	ImGui::Begin("Net configuration");//##################__________BEGIN_____________###########################
	workStationManagement();
	ImGui::End();//##################__________END_____________###########################
}


void NeuralNetwork::ImNodesManagement() {

	bool ret = true;

	Link link;
	ImNodesEditorContext& editor = ImNodes::EditorContextGet();
	if (ImNodes::IsLinkCreated(&link.input_pin, &link.output_pin)){
		//link.id = links.size();//this can be done if when deleting a link, all links reorder(erase should reorder automaticly) | (old code)/*(link.input_pin);*/
		
		//buscar el comunicator con pinID == output_pin y en el reciever node pasarle el id del nodo guardado en comunicator
		int tmpNodeID;
		int tmpPrevNodeID;
		for (int i = 0; i < comunicators.size(); i++) {
			if (comunicators[i].pin_ID == link.output_pin) {
				tmpNodeID = comunicators[i].neuron_ID;
			}
			if (comunicators[i].pin_ID == link.input_pin) {
				tmpPrevNodeID = comunicators[i].neuron_ID;
			}
		}

		link.reciever_node = (tmpNodeID/*link.output_pin >> 8*/);
		link.sender_node = (tmpPrevNodeID/*link.input_pin >> 16*/);//left part of the link starts in the output_pin from node "n". this way we know: n.ID = n>>16 because output_pin id is "BeginOutputAttribute(node_id << 16)"

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

void NeuralNetwork::NodeEditorManagement() {
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
}

void NeuralNetwork::workStationManagement() {

	if (ImGui::CollapsingHeader("predefined models")) {
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Select one of the sugested architectures");
		ImGui::Spacing();
		const char* items[] = { "1x2x1", "2x3x1", "2x3x3x1", "3x3x3x1" };
		static int item_current = 0;
		ImGui::Combo("Predefined configurations", &item_current, items, IM_ARRAYSIZE(items));
		ImGui::Spacing();

		ImGui::PushID(3);
		ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(3 / 7.0f, 0.6f, 0.6f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(3 / 7.0f, 0.7f, 0.7f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(3 / 7.0f, 0.8f, 0.8f));
		if (ImGui::Button("Generate selected Neural Network")) {
			if (p2list_Layers.count() == 0) {
				generateAutomaticNetwork(item_current);
			}
			else {
				ShowError2 = true;
			}
			
		}
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::PopStyleColor(3);
		ImGui::PopID();
		ImGui::AlignTextToFramePadding();


		if (ShowError2) {
			ImGui::Begin("ERROR 01");
			ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "You can only use one neural net at a time!");
			
			if (ImGui::Button("ok")) {
				ShowError2 = false;
			}
			ImGui::End();
		}
		ImGui::Spacing();
	}
	if (ImGui::CollapsingHeader("Configuration")) {
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Select your Net ammount of Layers");
		ImGui::Spacing();
		//######################################################
		static int layerCounter = 8;
		float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
		ImGui::PushButtonRepeat(true);
		if (ImGui::ArrowButton("##left", ImGuiDir_Left)) { layerCounter <= 3 ? layerCounter = layerCounter : layerCounter--; }
		ImGui::SameLine(0.0f, spacing);
		if (ImGui::ArrowButton("##right", ImGuiDir_Right)) { layerCounter >= 16 ? layerCounter = layerCounter : layerCounter++; }
		ImGui::PopButtonRepeat();
		ImGui::SameLine();
		ImGui::Text("max layers: %d", layerCounter);

		static int LayerAmmount = 0;
		ImGui::SliderInt("Layers", &LayerAmmount, 0, layerCounter);

		//######################################################
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "For each layer, select an ammount of neurons");
		ImGui::Spacing();

		static int SelectedLayer = 0;
		ImGui::SliderInt("Selected Layer", &SelectedLayer, 0, LayerAmmount);
		int* a = &SelectedLayer;
	
		ImGui::Spacing();
		if (SelectedLayer != NULL) {
			ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Neurons inside: %i", neuronsInside[SelectedLayer]);
		}
		static int NeuronsPerLayer;
		ImGui::InputInt("insert a number", &NeuronsPerLayer, 1, 2);
	
		if (neuronsInside.size() != 16) {
			for (int i = 0; i < 16; i++) {
				neuronsInside.push_back(0);
			}
		}


		if (ImGui::Button("Save value")) {
			if (NeuronsPerLayer > 16 || NeuronsPerLayer < 1) {
				ShowError1 = true;
			}
			else {
				neuronsInside[SelectedLayer] = NeuronsPerLayer;
			}

		}
		if (ShowError1) {
			ImGui::Begin("ERROR 01");
			ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Max neurons per layer: 16");
			ImGui::SameLine();
			if (ImGui::Button("ok")) {
				ShowError1 = false;
			}
			ImGui::End();
		}

		ImGui::SameLine();
		ImGui::Text("%i", NeuronsPerLayer);

		//######################################################aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
		
		
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Text("Neurons in first layer: %i",inputCounter );
		ImGui::Text("inputs in first layer: %i", inputVals.size());
		ImGui::Spacing();

		//#######################################################aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa

		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "click the button to generate your network");
		ImGui::Spacing();
		
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::SameLine();
		ImGui::PushID(3);
		ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(3 / 7.0f, 0.6f, 0.6f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(3 / 7.0f, 0.7f, 0.7f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(3 / 7.0f, 0.8f, 0.8f));
		if (ImGui::Button("Generate Neural Net")) {
			if (neuronsInside[0] != 0 ) {
				generateAutomaticNetwork(neuronsInside);
			}	
		}
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::PopStyleColor(3);
		ImGui::PopID();
		ImGui::AlignTextToFramePadding();
		

	}	// CONFIG END
	if (ImGui::CollapsingHeader("Neural Network training ")) {
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		if (p2list_Layers.count() > 1) {

			static float vec4a[1] = { 0.0 };//INPUT VALUES
			ImGui::InputFloat("input values from 0.0 to 1.0", vec4a, 0.1);
			if (ImGui::Button("Save Input") && inputVals.size() < p2list_Layers.getFirst()->data->p2list_LayerNeurons.count()) {
				inputVals.push_back(vec4a[0]);
			}
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Spacing();
			if (p2list_Layers.getFirst() != nullptr)
				ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "input values: %i, input Layer Neurons: %i", inputVals.size(), p2list_Layers.getFirst()->data->p2list_LayerNeurons.count());
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Spacing();
			
			static float vec4b[1] = { 0.0 };//TARGET VALUES
			ImGui::InputFloat("target Values from 0 to 1", vec4b, 0.1);
			if (ImGui::Button("Save output") && targetVals.size() < p2list_Layers.getLast()->data->p2list_LayerNeurons.count()) {
				targetVals.push_back(vec4b[0]);
			}
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Spacing();
			if (p2list_Layers.getFirst() != nullptr)
				ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "target values: %i, output Layer Neurons: %i", targetVals.size(), p2list_Layers.getLast()->data->p2list_LayerNeurons.count());
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Spacing();

			if (ImGui::Button("train Net")) {
				/*printf("\n \n \n input values: %f %f %f \n", inputVals[0], inputVals[1], inputVals[2]);*/
				TrainNet = true;
			}

			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Spacing();

			if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {//DO ITERATION
				iterateNow = true;
			}
			if (iterateNow && inputVals.size() > 0) {//ITERATE NET STEP BY STEP
				iterateNow = false;
				feedForward(inputVals);
				getResults(resultVals);
				printf("\n \n result values: %f  \n", resultVals[0]);
				printf("target values: --------> %f \n", targetVals[0]);
				backPropagation(targetVals);
				if (firstIteration) {
					firstIteration = false;
					difference = targetVals[0] - resultVals[0];
				}
			}
			if (resultVals.size() > 0)
				ImGui::TextColored(ImVec4(0.0f, 1.0f, 1.0f, 1.0f), "output value: %f", resultVals[0]);
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::TextColored(ImVec4(0.0f, 1.0f, 1.0f, 1.0f), "Net error: %f", p_netError);
			ImGui::TextColored(ImVec4(0.0f, 1.0f, 1.0f, 1.0f), "Net recent average error: %f", p_netRecentAverageError);
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Spacing();

			static int i0 = 0;
			if (TrainNet) { //TRAIN ENTIRE NET
				for (int i = 0; i < i0; i++) {
					ImGui::Spacing();
					ImGui::Spacing();
					ImGui::Spacing();
					feedForward(inputVals);
					getResults(resultVals);
					printf("\n \n result values: %f  \n", resultVals[0]);
					printf("target values: --------> %f \n", targetVals[0]);
					backPropagation(targetVals);
					if (firstIteration) {
						firstIteration = false;
						difference = targetVals[0] - resultVals[0];
					}
				}
				TrainNet = false;
			}ImGui::SameLine();

			ImGui::InputInt("training iterations", &i0);

			ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "if your neural network is trained, you can use it");

			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Spacing(); 
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Spacing();
			if (ImGui::Button("use neural network")) {
				feedForward(inputVals);
			}
		}
		else {
			ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "You need to generate a network in order to train it");
		}
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();		
	}	
	if (firstIteration == false) {
		paintNodes();
	}


}


void NeuralNetwork::paintNodes() {
	red = targetVals[0] - resultVals[0];
	green = 1.0 - red;
	
}

void NeuralNetwork::trainNeuralNetwork() {

}

void NeuralNetwork::generateAutomaticNetwork(std::vector<int> config) {

	for (usint i = 0; i < config.size(); i++) {
		Layer* tmpL = new Layer(p2list_Layers.count());
		p2list_Layers.add(tmpL);
		printf("created a new layer: %d \n", i);
		printf("Layer ID: %i \n", tmpL->getLayerID());
		//we have new layer now we add neurons inside
		for (int j = 0; j < config[i]; j++) {
			if (i != config.size() - 1) {//first or hidden layer = output weights
				usint nextLayerNeurons = config[i + 1];
				Neuron* tmpN = new Neuron(p2list_Neurons.count(), i, j, nextLayerNeurons);
				tmpL->addNeuron(tmpN, nextLayerNeurons);
				printf("addNeuron(tmpN) with id: %i\n", tmpN->getNeuronID());
			}
			else if (i == config.size() - 1) {//last layer = no output weights
				Neuron* tmpN = new Neuron(p2list_Neurons.count(), i, j, 0); //new neuron inside layer i
				tmpL->addNeuron(tmpN, 0/*hardcoded next layer neurons num*/);
				printf("addNeuron(tmpN)-last \n");
			}
		}
	}
}

void NeuralNetwork::generateAutomaticNetwork(usint LayerNum) { //check

	usint numLayers = LayerNum;
	std::vector<usint> neuronsPerLayer;
	switch (LayerNum)
	{
	case 0://1x2x1
		numLayers = 3;
		neuronsPerLayer.clear();
		neuronsPerLayer.push_back(1);
		neuronsPerLayer.push_back(2);
		neuronsPerLayer.push_back(1);
	
		break;
	case 1://2x3x1
		numLayers = 3;
		neuronsPerLayer.clear();
		neuronsPerLayer.push_back(2);
		neuronsPerLayer.push_back(3);
		neuronsPerLayer.push_back(1);
		break;
	case 2://2x3x3x1
		numLayers = 4;
		neuronsPerLayer.clear();
		neuronsPerLayer.push_back(2);
		neuronsPerLayer.push_back(3);
		neuronsPerLayer.push_back(3);
		neuronsPerLayer.push_back(1);
		break;
	case 3://3x6x6x1
		numLayers = 4;
		neuronsPerLayer.clear();
		neuronsPerLayer.push_back(3);
		neuronsPerLayer.push_back(3);
		neuronsPerLayer.push_back(3);
		neuronsPerLayer.push_back(1);
		break;	
	}

	for (usint i = 0; i < numLayers; i++) {
		Layer* tmpL = new Layer(p2list_Layers.count());
		p2list_Layers.add(tmpL);
		printf("created a new layer: %d \n",i);
		printf("Layer ID: %i \n", tmpL->getLayerID());
		//we have new layer now we add neurons inside
		for (int j = 0; j < neuronsPerLayer[i]; j++) {
			if ( i != numLayers-1 ) {//first or hidden layer = output weights
				usint nextLayerNeurons = neuronsPerLayer[i + 1];
				Neuron* tmpN = new Neuron(p2list_Neurons.count(), i, j, nextLayerNeurons);
				tmpL->addNeuron(tmpN, nextLayerNeurons);
				printf("addNeuron(tmpN) with id: %i\n",tmpN->getNeuronID());
			}
			else if (i == numLayers-1 ) {//last layer = no output weights
				Neuron* tmpN = new Neuron(p2list_Neurons.count(), i,j, 0); //new neuron inside layer i
				tmpL->addNeuron(tmpN, 0/*hardcoded next layer neurons num*/);
				printf("addNeuron(tmpN)-last \n");
			}	
		}
	}
}

void NeuralNetwork::feedForward(const std::vector<double> &inputVals) { //check
	printf("\n FEEDFORWARD MAIN");
	assert(inputVals.size() == p2list_Layers.getFirst()->data->p2list_LayerNeurons.count());
	
	//assign input values to the neurons in first layer
	p2List_item<Layer*>* layerIterator;
	layerIterator = p2list_Layers.getFirst();

	p2List_item<Neuron*>* neuronIterator;
	neuronIterator = layerIterator->data->p2list_LayerNeurons.getFirst();
	for (int i = 0; i < inputVals.size(); i++) {
		neuronIterator->data->outputValue = inputVals[i];
		printf("\ninputValue: %f", inputVals[i]);
		//neuronIterator->data->inputValues.push_back(inputVals[i]);
		neuronIterator = neuronIterator->next;
	}

	//forward propagate
	for (int i = 1; i < p2list_Layers.count(); i++) {//iterate layers
		Layer* tmpL;
		p2list_Layers.at(i, tmpL);
		p2List_item<Neuron*>* neuronIterator = tmpL->p2list_LayerNeurons.getFirst();
		Layer* tmpLprev;
		p2list_Layers.at(i - 1, tmpLprev);
		printf("\n ---feedforward neurons from Layer: %i", tmpLprev->getLayerID());
		for (int n = 0; n < tmpL->p2list_LayerNeurons.count(); n++) {//iterate neurons in layer
			neuronIterator->data->feedForward(*tmpLprev);
			/*printf("\n Layer: %i", tmpLprev->getLayerID());
			printf("\n ---NeuronID: %i", neuronIterator->data->getNeuronID());*/
			if (tmpL->getLayerID() != p2list_Layers.count()-1) {
				/*printf("\n ------Neuron Weight: %f", neuronIterator->data->outputWeights[neuronIterator->data->p_myIndexInTheList].weight);
				printf("\n ---------Neuron output: %f", neuronIterator->data->outputValue);*/
			}
			
			neuronIterator = neuronIterator->next;
		}
	}
	
}

void NeuralNetwork::backPropagation(const std::vector<double>& _targetVals) {
	printf("\n BACKPROPAGATION MAIN");
	//Calculate RMS "Root Mean Square Error" also known as overall net error
	
	/*Layer& outputLayer = p2list_Layers.getLast();*/
	p_netError = 0.0;
	Layer* tmpL; //output layer
	p2list_Layers.at(p2list_Layers.count() - 1, tmpL);
	
	for (int n = 0; n < tmpL->p2list_LayerNeurons.count(); n++) {
		Neuron* tmpN;
		tmpL->p2list_LayerNeurons.at(n, tmpN);

		double delta = _targetVals[n] - tmpN->outputValue;
		p_netError += delta * delta;
	}
	float a = tmpL->p2list_LayerNeurons.count();
	p_netError /= a; //average error sqrted
	p_netError = sqrt(p_netError); //RMS
	p_netRecentAverageError = (p_netRecentAverageError * p_netRecentSmoothingFactor + p_netError)
		/ (p_netRecentSmoothingFactor + 1);
	printf("\n p_netRecentAverageError  ------------------------%f", p_netRecentAverageError);
	printf("\n p_netError  ------------------------%f", p_netError);
	//calculate output layer gradients
	p2List_item<Neuron*>* neuronIterator;
	neuronIterator = tmpL->p2list_LayerNeurons.getFirst();//output layer neuron iterator
	for (int n = 0; n <= tmpL->p2list_LayerNeurons.count() - 1 ; n++) {
		neuronIterator->data->calculateOutputGradients(targetVals[n]);	
		neuronIterator = neuronIterator->next;
	}

	//calculate hidden layer gradients
	Layer* tmpL2;
	p2list_Layers.at(p2list_Layers.count() - 2, tmpL2);

	p2List_item<Layer*>* layerIterator;
	layerIterator = p2list_Layers.getLast();
	layerIterator = layerIterator->prev; //first hidden layer before last layer
	for (int l = p2list_Layers.count() - 2; l>0	; l--) {//-1 is the last, -2 is the first hidden starting from the back
		Layer* nextL;
		nextL = layerIterator->next->data;
		
		p2List_item<Neuron*>* neuronIterator;
		neuronIterator = layerIterator->data->p2list_LayerNeurons.getFirst();
		for (int i = 0; i < layerIterator->data->p2list_LayerNeurons.count(); i++) {//calls calchuddengradients of all layer neurons
			
			neuronIterator->data->calculateHiddenGradients(*nextL);
			neuronIterator = neuronIterator->next;
		}
		layerIterator = layerIterator->prev;
	}

	//from all layers, from output layer to first hidden layer update all weights
	layerIterator = p2list_Layers.getLast();
	//layerIterator = layerIterator->prev; //first hidden layer before last layer	
	for (int i = p2list_Layers.count() - 1; i > 0; i--) {
		Layer* prevL;
		prevL = layerIterator->prev->data;
		
		p2List_item<Neuron*>* neuronIterator;
		neuronIterator = layerIterator->data->p2list_LayerNeurons.getFirst();
		for (int n = 0; n < layerIterator->data->p2list_LayerNeurons.count(); n++) {
			neuronIterator->data->updateInputWeights(*prevL);
			
			neuronIterator = neuronIterator->next;
		}

		layerIterator = layerIterator->prev;
	}

}

void NeuralNetwork::getResults(std::vector<double>& resultVals) {
	resultVals.clear();
	p2List_item<Neuron*>* neuronIterator;
	neuronIterator = p2list_Layers.getLast()->data->p2list_LayerNeurons.getFirst();
	
	for (int n = 0; n < p2list_Layers.getLast()->data->p2list_LayerNeurons.count(); n++) {	
		resultVals.push_back(neuronIterator->data->outputValue);
		neuronIterator = neuronIterator->next;
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

