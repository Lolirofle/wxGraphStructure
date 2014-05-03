#ifndef __LOLIROFLE_WXGRAPHSTRUCTURE_GRAPH_EDGE_HPP_INCLUDED__
#define __LOLIROFLE_WXGRAPHSTRUCTURE_GRAPH_EDGE_HPP_INCLUDED__

#include <string>
#include "Renderable.hpp"

namespace GraphStructure{
	class Node;

	class GraphEdge : public Renderable{
	protected:
		Node& to;
		std::string label;
		float weight;

	public:
		GraphEdge(Node& to,std::string label,float weight=0.0f);

		void render(wxPaintEvent& event);
	};
}

#endif
