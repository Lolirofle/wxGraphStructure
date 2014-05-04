#ifndef __LOLIROFLE_WXGRAPHSTRUCTURE_GRAPH_NODE_HPP_INCLUDED__
#define __LOLIROFLE_WXGRAPHSTRUCTURE_GRAPH_NODE_HPP_INCLUDED__

#include <list>
#include <string>
#include "Renderable.hpp"

namespace GraphStructure{
	class GraphEdge;

	class Node : public Renderable{
	public:
		float x,y;
		std::string label;
		std::list<GraphEdge*> connections;
		
		Node(float x,float y,std::string label);

		void render(wxPaintEvent& event);
	};
}

#endif
