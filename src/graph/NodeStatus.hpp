#ifndef __LOLIROFLE_WXGRAPHSTRUCTURE_GRAPH_NODESTATUS_HPP_INCLUDED__
#define __LOLIROFLE_WXGRAPHSTRUCTURE_GRAPH_NODESTATUS_HPP_INCLUDED__

#include <list>
#include "../wx.hpp"

namespace GraphStructure{
	class Node;
	
	class NodeStatus{
	protected:
		std::list<Node*> nodes;
		std::list<Node*> selectedNodes;//Must be non empty when mouseClickType==NODE

	public:
		const std::list<Node*>& getNodes()const;
		const std::list<Node*>& getSelectedNodes()const;
		
		virtual void selectNode(Node& node);
		virtual void deselectNodes();

		virtual void addNode(Node* node);
		virtual void removeNode(Node* node);
		virtual void removeAllNodesApply(void(*func)(Node*));

		Node* getNodeAt(wxPoint pos);
		bool isNodeSelected(Node* node)const;
		bool isNodeSelected()const;
	};
}

#endif
