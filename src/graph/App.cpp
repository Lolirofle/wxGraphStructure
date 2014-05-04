#include "App.hpp"

#include "Frame.hpp"
#include "NodeVisualizer.hpp"

wxIMPLEMENT_APP(GraphStructure::App);

namespace GraphStructure{
	bool App::OnInit(){
		//Prepare nodes
		selectedNode = NULL;

		//Creates the frame
		Frame *frame = new Frame(wxSize(450,340),*this);

		//Prepare views
		setView(WindowViews::NodeVisualizer,new NodeVisualizer(frame,*this));
		wxDataViewListCtrl *listctrl = new wxDataViewListCtrl(frame,wxID_ANY);
			listctrl->AppendTextColumn("Field");
			listctrl->AppendTextColumn("Value");
			wxVector<wxVariant> data;
				data.push_back(wxVariant("Name"));
				data.push_back(wxVariant("Test"));
			listctrl->AppendItem(data);
			data.clear();
				data.push_back(wxVariant("Value"));
				data.push_back(wxVariant("5"));
			listctrl->AppendItem(data);
			data.clear();
				data.push_back(wxVariant("x"));
				data.push_back(wxVariant("29"));
			listctrl->AppendItem(data);
			data.clear();
				data.push_back(wxVariant("y"));
				data.push_back(wxVariant("46"));
			listctrl->AppendItem(data);
		setView(WindowViews::NodeProperties,listctrl);
		setView(WindowViews::Information   ,new wxTextCtrl(frame,wxID_ANY,wxT("Initial text"),wxDefaultPosition,wxSize(100,60),wxTE_MULTILINE));

		frame->setupLayout(*this);

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
		NodeStatus::selectNode(node);
	}

	void App::deselectNodes(){
		NodeStatus::deselectNodes();
	}

	void App::removeAllNodesApply(void(*func)(Node*)){
		NodeStatus::removeAllNodesApply(func);
	}
}
