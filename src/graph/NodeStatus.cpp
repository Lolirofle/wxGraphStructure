#include "NodeStatus.hpp"

#include "Node.hpp"

namespace GraphStructure{
	std::list<Node*>& NodeStatus::getNodes(){
		return nodes;
	}

	Node* NodeStatus::getSelectedNode(){
		return selectedNode;
	}

	void NodeStatus::selectNode(Node& node){
		selectedNode = &node;
	}

	void NodeStatus::deselectNodes(){
		selectedNode = NULL;
	}
	
	Node* NodeStatus::getNodeAt(wxPoint pos){
		for(auto node=getNodes().begin(); node!=getNodes().end(); ++node){
			if(hypot((*node)->pos.x - pos.x,(*node)->pos.y - pos.y) < (*node)->radius){
				return *node;
			}
		}
		return NULL;
	}

	void NodeStatus::addNode(Node* node){
		if(node)
			getNodes().push_back(node);
	}

	void NodeStatus::removeNode(Node* node){
		if(node)
			getNodes().remove(node);
	}

	bool NodeStatus::isNodeSelected(Node* node)const{
		return node == selectedNode;
	}

	void NodeStatus::removeAllNodesApply(void(*func)(Node*)){
		while(!getNodes().empty()){
			func(getNodes().front());
			getNodes().pop_front();
		}
	}
}
