#ifndef __LOLIROFLE_WXGRAPHSTRUCTURE_GRAPHAPP_HPP_INCLUDED__
#define __LOLIROFLE_WXGRAPHSTRUCTURE_GRAPHAPP_HPP_INCLUDED__

#include "wx.hpp"
#include <list>

class GraphNode;

class GraphApp : public wxApp{
public:
	std::list<GraphNode*> nodes;
	GraphNode* selectedNode;//Must be non NULL when mouseClickType==NODE

	virtual bool OnInit();
};

#endif
