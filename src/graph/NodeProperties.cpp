#include "NodeProperties.hpp"

#include <sstream>
#include "Node.hpp"

namespace GraphStructure{
	NodeProperties::NodeProperties(wxFrame* parent) : wxDataViewListCtrl(parent,wxID_ANY){
		AppendTextColumn("Field");
		AppendTextColumn("Value");
	}

	NodeProperties::~NodeProperties(){}

	void NodeProperties::showNode(const Node& node){
		DeleteAllItems();

		std::stringstream strStream;

		wxVector<wxVariant> data;
			data.push_back(wxVariant("Type"));
			data.push_back(wxVariant("Node"));
		AppendItem(data);
		data.clear();
			data.push_back(wxVariant("Label"));
			data.push_back(wxVariant(node.label));
		AppendItem(data);
		data.clear();
			data.push_back(wxVariant("Value"));
			data.push_back(wxVariant("5"));
		AppendItem(data);
		data.clear();
			data.push_back(wxVariant("x"));
			strStream.str("");
			strStream << node.pos.x;
			data.push_back(wxVariant(strStream.str()));
		AppendItem(data);
		data.clear();
			data.push_back(wxVariant("y"));
			strStream.str("");
			strStream << node.pos.y;
			data.push_back(wxVariant(strStream.str()));
		AppendItem(data);
	}

	void NodeProperties::showEdge(const Edge& edge){}
	void NodeProperties::showNone(){
		DeleteAllItems();
	}
}
