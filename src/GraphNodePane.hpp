#ifndef __LOLIROFLE_WXGRAPHSTRUCTURE_GRAPHNODEPANE_HPP_INCLUDED__
#define __LOLIROFLE_WXGRAPHSTRUCTURE_GRAPHNODEPANE_HPP_INCLUDED__

#include "wx.hpp"
#include "GLPane.hpp"
#include <list>

class GraphNode;

enum class GraphNodePane_MouseClickType{
	/**
	 * When no mouse click happened
	 */
	NONE,

	/**
	 * When selecting a node
	 */
	SELECT_NODE,

	/**
	 * When selecting multiple nodes
	 */
	SELECT_NODES,
	
	/**
	 * When reselecting the same node as the one already selected
	 */
	RESELECT_NODE,


	/**
	 * When selecting an edge
	 */
	SELECT_EDGE,

	/**
	 * When selecting multiple edges
	 */
	SELECT_EDGES,

	/**
	 * When clicked on empty space
	 */
	EMPTYSPACE
};

enum class GraphNodePane_MouseReleaseType{
	/**
	 * When deselecting a node
	 */
	DESELECT_NODE,

	/**
	 * When deselecting multiple selected nodes
	 */
	DESELECT_NODES,

	/**
	 * When deselecting an edge
	 */
	DESELECT_EDGE,

	/**
	 * When deselecting multiple selected edges
	 */
	DESELECT_EDGES
};

class GraphNodePane : public GLPane{
private:
	//Mouse control
	wxPoint mouseClickAbsolutePos,
	        mousePreviousAbsolutePos;
	GraphNodePane_MouseClickType mouseClickType;
	bool mouseDrag;
	unsigned short mouseDragInitiationDistance;

	//View
	float x,y;
	float scale;
	float minScale;
	float maxScale;

	//Data
	std::list<GraphNode*>& nodes;
	GraphNode*& selectedNode;//Must be non NULL when mouseClickType==NODE

	wxDECLARE_EVENT_TABLE();
	
protected:
	GraphNode* getNodeAt(wxPoint pos);

public:
	GraphNodePane(wxFrame* parent,std::list<GraphNode*>& nodes,GraphNode*& selectedNode);
	virtual ~GraphNodePane();

	void render(wxPaintEvent& event);
	
	void onMouseMove(wxMouseEvent& event);
	void onMouseLeftDown(wxMouseEvent& event);
	void onMouseLeftUp(wxMouseEvent& event);
	void onMouseRightDown(wxMouseEvent& event);
	void onMouseRightUp(wxMouseEvent& event);
	void onMouseWheel(wxMouseEvent& event);
	void onMouseLeaveWindow(wxMouseEvent& event);
	void onKeyDown(wxKeyEvent& event);
	void onKeyUp(wxKeyEvent& event);

	void moveView(float x,float y);

	wxPoint getMouseEventPosition(wxMouseEvent& event);
	wxPoint getMouseEventAbsolutePosition(wxMouseEvent& event);

	void zoomIn(float scaling,wxPoint center);
	void zoomOut(float scaling,wxPoint center);
};
#endif
