#include "NodeStatus.hpp"

#include <algorithm>
#include "Node.hpp"
#include "Edge.hpp"

namespace GraphStructure{
	const std::list<Node>& NodeStatus::getNodes()const{
		return nodes;
	}

	const std::list<Node*>& NodeStatus::getSelectedNodes()const{
		return selectedNodes;
	}

	void NodeStatus::selectNode(Node& node){
		if(!isNodeSelected(&node))
			selectedNodes.push_back(&node);
	}

	void NodeStatus::selectNodes(){
		deselectNodes();
		for(auto node=nodes.begin(); node!=nodes.end(); ++node){
			selectedNodes.push_back(&*node);
		}
	}

	void NodeStatus::deselectNodes(){
		selectedNodes.clear();
	}
	
	Node* NodeStatus::getNodeAt(wxPoint pos){
		for(auto node=nodes.begin(); node!=nodes.end(); ++node){
			if(hypot(node->pos.x - pos.x,node->pos.y - pos.y) < node->radius){
				return &*node;
			}
		}
		return NULL;
	}

	void NodeStatus::addNode(Node node){
		nodes.push_back(node);
	}

	void NodeStatus::removeNode(const Node* node){
		nodes.remove_if([node](const Node& i){
			return &i == node;
		});
	}

	bool NodeStatus::isNodeSelected(const Node* node)const{
		return std::find(std::begin(getSelectedNodes()),std::end(getSelectedNodes()),node) != std::end(getSelectedNodes());
	}

	bool NodeStatus::hasNodeSelected()const{
		return !getSelectedNodes().empty();
	}

	void NodeStatus::removeAllNodes(){
		nodes.clear();
	}

	void NodeStatus::connect(Node& from,Edge edge){
		from.connections.push_back(edge);
	}
}
