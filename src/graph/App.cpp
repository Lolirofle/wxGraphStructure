#include "App.hpp"

#include "Frame.hpp"
#include "NodeVisualizer.hpp"
#include "NodeProperties.hpp"

wxIMPLEMENT_APP(GraphStructure::App);

namespace GraphStructure{
	bool App::OnInit(){
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

	bool App::isModified()const{
		return modified;
	}

	void App::selectNode(Node& node){
		views.nodeProperties->showNode(node);
		NodeStatus::selectNode(node);
		views.nodeVisualizer->Refresh();
	}

	void App::deselectNodes(){
		NodeStatus::deselectNodes();
		views.nodeVisualizer->Refresh();
	}

	void App::addNode(Node node){
		modified = true;
		NodeStatus::addNode(node);
		views.nodeVisualizer->Refresh();
	}

	void App::removeNode(const Node* node){
		modified = true;
		NodeStatus::removeNode(node);
		views.nodeVisualizer->Refresh();
	}

	void App::removeAllNodes(){
		modified = true;
		NodeStatus::removeAllNodes();
		views.nodeVisualizer->Refresh();
	}

	void App::connect(Node& from,Node& to){
		NodeStatus::connect(from,to);
		views.nodeVisualizer->Refresh();
	}
}
