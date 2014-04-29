#include "GraphNodePane.hpp"

#include "gl.hpp"
#include <GraphNode.hpp>
#include <GraphEdge.hpp>

static bool position_inside(wxPoint a,wxPoint b,float radius){
	return a.x > b.x-radius && a.x < b.x+radius && a.y > b.y-radius && a.y < b.y+radius;
}

wxBEGIN_EVENT_TABLE(GraphNodePane,GLPane)
	EVT_MOTION      (GraphNodePane::onMouseMove)
	EVT_LEFT_DOWN   (GraphNodePane::onMouseLeftDown)
	EVT_LEFT_UP     (GraphNodePane::onMouseLeftUp)
	EVT_RIGHT_DOWN  (GraphNodePane::onMouseRightDown)
	EVT_RIGHT_UP    (GraphNodePane::onMouseRightUp)
	EVT_LEAVE_WINDOW(GraphNodePane::onMouseLeaveWindow)
	EVT_KEY_DOWN    (GraphNodePane::onKeyDown)
	EVT_KEY_UP      (GraphNodePane::onKeyUp)
	EVT_MOUSEWHEEL  (GraphNodePane::onMouseWheel)
wxEND_EVENT_TABLE()

GraphNodePane::GraphNodePane(wxFrame* parent) : GLPane(parent),mouseDrag(false),mouseDragInitiationDistance(8),x(0.0f),y(0.0f),scale(1),minScale(1/16),maxScale(128){
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);
}

void GraphNodePane::onMouseLeftDown(wxMouseEvent& event){
	mouseClickAbsolutePos = getMouseEventAbsolutePosition(event);
	mouseClickType = GraphNodePane_MouseClickType::EMPTYSPACE;
}

void GraphNodePane::onMouseLeftUp(wxMouseEvent& event){
	if(mouseClickType==GraphNodePane_MouseClickType::EMPTYSPACE && !mouseDrag){
		wxPoint mouseCurrentPos = getMouseEventPosition(event);
	
		nodes.push_front(new GraphNode(mouseCurrentPos.x,mouseCurrentPos.y,"Label"));

		Refresh();
	}

	mouseClickType = GraphNodePane_MouseClickType::NONE;
	mouseDrag=false;
}

void GraphNodePane::onMouseRightDown(wxMouseEvent& event){}
void GraphNodePane::onMouseRightUp(wxMouseEvent& event){}
void GraphNodePane::onMouseWheel(wxMouseEvent& event){}
void GraphNodePane::onMouseLeaveWindow(wxMouseEvent& event){}
void GraphNodePane::onKeyDown(wxKeyEvent& event){}
void GraphNodePane::onKeyUp(wxKeyEvent& event){}

void GraphNodePane::onMouseMove(wxMouseEvent& event){
	const wxPoint mouseCurrentAbsolutePos = getMouseEventAbsolutePosition(event);

	if(event.Dragging()){
		if(mouseDrag){
			moveView(mouseCurrentAbsolutePos.x-mousePreviousAbsolutePos.x,mouseCurrentAbsolutePos.y-mousePreviousAbsolutePos.y);
			Refresh();
		}else{
			if(!position_inside(mouseCurrentAbsolutePos,mouseClickAbsolutePos,mouseDragInitiationDistance))
				mouseDrag=true;
		}
	}

	mousePreviousAbsolutePos = mouseCurrentAbsolutePos;
}

void GraphNodePane::render(wxPaintEvent& event){
	glTranslatef(x,y,0.0f);
	for(auto node=nodes.begin(); node!=nodes.end(); ++node){
		(*node)->render(event);
	}
	glTranslatef(-x,-y,0.0f);
}

void GraphNodePane::moveView(float x,float y){
	this->x+=x;
	this->y+=y;
}

wxPoint GraphNodePane::getMouseEventPosition(wxMouseEvent& event){
	wxPoint pos = getMouseEventAbsolutePosition(event);
	pos.x-=x;
	pos.y-=y;

	return pos;
}

wxPoint GraphNodePane::getMouseEventAbsolutePosition(wxMouseEvent& event){
	return event.GetLogicalPosition(wxPaintDC(this));
}
