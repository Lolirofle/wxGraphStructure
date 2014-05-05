#include "App.hpp"

#include "Frame.hpp"
#include "NodeVisualizer.hpp"
#include "NodeProperties.hpp"

wxIMPLEMENT_APP(GraphStructure::App);

namespace GraphStructure{
	bool App::OnInit(){
		//Prepare nodes
		selectedNode = NULL;

		//Creates the frame
		Frame *frame = new Frame(wxSize(450,340),*this);

		//Prepare views
		views.nodeVisualizer = new NodeVisualizer(frame,*this);
		views.nodeProperties = new NodeProperties(frame);
		views.information    = new wxTextCtrl(frame,wxID_ANY,wxT("Initial text"),wxDefaultPosition,wxSize(100,60),wxTE_MULTILINE);

		frame->setupLayout(views);

		//Show the frame
		frame->Show(true);

		return true;
	}

	void App::addNode(Node* node){
		NodeStatus::addNode(node);
	}

	void App::removeNode(Node* node){
		NodeStatus::removeNode(node);
	}

	void App::selectNode(Node& node){
		views.nodeProperties->showNode(node);
		NodeStatus::selectNode(node);
	}

	void App::deselectNodes(){
		NodeStatus::deselectNodes();
	}

	void App::removeAllNodesApply(void(*func)(Node*)){
		NodeStatus::removeAllNodesApply(func);
	}
}
