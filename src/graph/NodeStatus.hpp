#ifndef __LOLIROFLE_WXGRAPHSTRUCTURE_GRAPH_NODESTATUS_HPP_INCLUDED__
#define __LOLIROFLE_WXGRAPHSTRUCTURE_GRAPH_NODESTATUS_HPP_INCLUDED__

#include <list>
#include "../wx.hpp"

namespace GraphStructure{
	class Node;
	class Edge;
	
	class NodeStatus{
	protected:
		std::list<Node> nodes;
		std::list<Node*> selectedNodes;//Must be non empty when mouseClickType==NODE

	public:
		void init();

		const std::list<Node>& getNodes()const;
		const std::list<Node*>& getSelectedNodes()const;
		
		virtual void selectNode(Node& node);
		virtual void selectNodes();
		virtual void deselectNodes();

		virtual void addNode(Node node);
		virtual void removeNode(const Node* node);
		virtual void removeAllNodes();

		virtual void connect(Node& from,Edge edge);

		Node* getNodeAt(wxPoint pos);
		bool isNodeSelected(const Node* node)const;//Compares pointers
		bool hasNodeSelected()const;

		virtual bool isModified()const=0;
	};
}

#endif
