#ifndef __LOLIROFLE_WXGRAPHSTRUCTURE_GRAPHNODEPANE_HPP_INCLUDED__
#define __LOLIROFLE_WXGRAPHSTRUCTURE_GRAPHNODEPANE_HPP_INCLUDED__

#include "wx.hpp"
#include "GLPane.hpp"

class GraphNodePane : public GLPane{
private:
	wxPoint mousePreviousPos;
	float x,y;

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
};
#endif
