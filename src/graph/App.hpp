#ifndef __LOLIROFLE_WXGRAPHSTRUCTURE_GRAPH_APP_HPP_INCLUDED__
#define __LOLIROFLE_WXGRAPHSTRUCTURE_GRAPH_APP_HPP_INCLUDED__

#include "../wx.hpp"
#include <list>
#include "NodeStatus.hpp"
#include "WindowViews.hpp"

namespace GraphStructure{
	class Node;
	class Edge;

	class App : public wxApp , public NodeStatus{
	public:
		WindowViewContainer views;
		bool modified;

		virtual bool OnInit();
		
		virtual bool isModified()const;
	
		virtual void selectNode(Node& node);
		virtual void deselectNodes();
		virtual void addNode(Node node);
		virtual void removeNode(const Node* node);
		virtual void removeAllNodes();
		virtual void connect(Node& from,Edge edge);
	};
}

#endif
