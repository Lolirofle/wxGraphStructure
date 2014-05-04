#ifndef __LOLIROFLE_WXGRAPHSTRUCTURE_GRAPHNODE_HPP_INCLUDED__
#define __LOLIROFLE_WXGRAPHSTRUCTURE_GRAPHNODE_HPP_INCLUDED__

#include <list>
#include <string>
#include "wx.hpp"

class GraphEdge;

class GraphNode{
public:
	wxPoint pos;
	std::string label;
	std::list<GraphEdge*> connections;
	unsigned int radius;
	
	GraphNode(wxPoint pos,std::string label);

	void render(wxPaintEvent& event,bool selected=false);
};
#endif
