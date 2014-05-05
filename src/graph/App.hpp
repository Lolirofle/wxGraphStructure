#ifndef __LOLIROFLE_WXGRAPHSTRUCTURE_GRAPH_APP_HPP_INCLUDED__
#define __LOLIROFLE_WXGRAPHSTRUCTURE_GRAPH_APP_HPP_INCLUDED__

#include "../wx.hpp"
#include <list>
#include "NodeStatus.hpp"
#include "WindowViews.hpp"

namespace GraphStructure{
	class Node;

	class App : public wxApp , public NodeStatus{
	public:
		WindowViewContainer views;

		virtual bool OnInit();

		std::list<Node*>& getNodes();
		Node* getSelectedNode();
		
		virtual void selectNode(Node& node);
		virtual void deselectNodes();

		virtual void addNode(Node* node);
		virtual void removeNode(Node* node);
	
		virtual void removeAllNodesApply(void(*func)(Node*));
	};
}

#endif
