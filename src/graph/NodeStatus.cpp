#include "NodeStatus.hpp"

#include <algorithm>
#include "Node.hpp"

namespace GraphStructure{
	const std::list<Node*>& NodeStatus::getNodes()const{
		return nodes;
	}

	const std::list<Node*>& NodeStatus::getSelectedNodes()const{
		return selectedNodes;
	}

	void NodeStatus::selectNode(Node& node){
		if(!isNodeSelected(&node))
			selectedNodes.push_back(&node);
	}

	void NodeStatus::deselectNodes(){
		selectedNodes.clear();
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
			nodes.push_back(node);
	}

	void NodeStatus::removeNode(Node* node){
		if(node)
			nodes.remove(node);
	}

	bool NodeStatus::isNodeSelected(Node* node)const{
		return std::find(std::begin(getSelectedNodes()),std::end(getSelectedNodes()),node) != std::end(getSelectedNodes());
	}

	bool NodeStatus::isNodeSelected()const{
		return !getSelectedNodes().empty();
	}

	void NodeStatus::removeAllNodesApply(void(*func)(Node*)){
		while(!nodes.empty()){
			func(nodes.front());
			nodes.pop_front();
		}
	}
}
