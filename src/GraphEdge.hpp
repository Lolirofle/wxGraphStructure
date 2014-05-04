#ifndef __LOLIROFLE_WXGRAPHSTRUCTURE_GRAPHEDGE_HPP_INCLUDED__
#define __LOLIROFLE_WXGRAPHSTRUCTURE_GRAPHEDGE_HPP_INCLUDED__

#include <string>

class GraphNode;

class GraphEdge{
protected:
	GraphNode& to;
	std::string label;
	float weight;

public:
	GraphEdge(GraphNode& to,std::string label,float weight=0.0f);

	void render(wxPaintEvent& event);
};

#endif
