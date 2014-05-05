#ifndef __LOLIROFLE_WXGRAPHSTRUCTURE_GRAPH_NODEPROPERTIES_HPP_INCLUDED__
#define __LOLIROFLE_WXGRAPHSTRUCTURE_GRAPH_NODEPROPERTIES_HPP_INCLUDED__

#include "../wx.hpp"

namespace GraphStructure{
	class Node;
	class Edge;

	class NodeProperties : public wxDataViewListCtrl{
	public:
		NodeProperties(wxFrame* parent);
		virtual ~NodeProperties();

		void showNode(const Node& node);
		void showEdge(const Edge& edge);
		void showNone();
	};
}

#endif
