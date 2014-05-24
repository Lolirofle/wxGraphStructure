#ifndef __LOLIROFLE_WXGRAPHSTRUCTURE_GRAPH_NODE_HPP_INCLUDED__
#define __LOLIROFLE_WXGRAPHSTRUCTURE_GRAPH_NODE_HPP_INCLUDED__

#include <list>
#include <string>
#include "../wx.hpp"
#include "Edge.hpp"

namespace GraphStructure{
	class Edge;

	class Node{
	public:
		wxPoint pos;
		std::string label;
		std::list<Edge> connections;
		unsigned int radius;
		
		Node(wxPoint pos,std::string label);

		void render(wxPaintEvent& event,bool selected=false)const;
	};
}

#endif
