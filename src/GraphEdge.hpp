#ifndef __LOLIROFLE_WXGRAPHSTRUCTURE_GRAPHEDGE_HPP_INCLUDED__
#define __LOLIROFLE_WXGRAPHSTRUCTURE_GRAPHEDGE_HPP_INCLUDED__

#include <string>
#include "Renderable.hpp"

class GraphNode;

class GraphEdge : public Renderable{
protected:
	GraphNode& to;
	std::string label;
	float weight;

public:
	GraphEdge(GraphNode& to,std::string label,float weight=0.0f);

	void render(wxPaintEvent& event);
};

#endif
