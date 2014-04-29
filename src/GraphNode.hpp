#ifndef __LOLIROFLE_WXGRAPHSTRUCTURE_GRAPHNODE_HPP_INCLUDED__
#define __LOLIROFLE_WXGRAPHSTRUCTURE_GRAPHNODE_HPP_INCLUDED__

#include <list>
#include <string>
#include "Renderable.hpp"

class GraphEdge;

class GraphNode : public Renderable{
public:
	float x,y;
	std::string label;
	std::list<GraphEdge*> connections;
	
	GraphNode(float x,float y,std::string label);

	void render(wxPaintEvent& event);
};
#endif
