#ifndef __LOLIROFLE_WXGRAPHSTRUCTURE_GRAPHNODEPANE_HPP_INCLUDED__
#define __LOLIROFLE_WXGRAPHSTRUCTURE_GRAPHNODEPANE_HPP_INCLUDED__

#include "wx.hpp"
#include "GLPane.hpp"
#include <list>

class GraphNode;

enum class GraphNodePane_MouseClickType{
	NONE,
	NODE,
	SELECTED,
	SELECTIONS,
	EMPTYSPACE
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
	std::list<GraphNode*> nodes;

	wxDECLARE_EVENT_TABLE();
	
public:
	GraphNodePane(wxFrame* parent);

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
};
#endif
