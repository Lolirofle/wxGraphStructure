#include "GraphNodePane.hpp"

#include "gl.hpp"

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


GraphNodePane::GraphNodePane(wxFrame* parent) : GLPane(parent),x(0.0f),y(0.0f){}

void GraphNodePane::onMouseLeftDown(wxMouseEvent& event){}
void GraphNodePane::onMouseLeftUp(wxMouseEvent& event){}
void GraphNodePane::onMouseRightDown(wxMouseEvent& event){}
void GraphNodePane::onMouseRightUp(wxMouseEvent& event){}
void GraphNodePane::onMouseWheel(wxMouseEvent& event){}
void GraphNodePane::onMouseLeaveWindow(wxMouseEvent& event){}
void GraphNodePane::onKeyDown(wxKeyEvent& event){}
void GraphNodePane::onKeyUp(wxKeyEvent& event){}

void GraphNodePane::onMouseMove(wxMouseEvent& event){
	const wxPoint mouseCurrentPos = event.GetPosition();

	if(event.Dragging()){
		moveView(mouseCurrentPos.x-mousePreviousPos.x,mouseCurrentPos.y-mousePreviousPos.y);
	}

	mousePreviousPos = mouseCurrentPos;

	Refresh();
}

void GraphNodePane::render(wxPaintEvent& evt){
	const unsigned int nodeRadius = 25;
	const float nodeX = 32.0f,
	            nodeY = 48.0f;

	glTranslatef(x,y,0.0f);
		//Nodes
		glColor3ub(221,221,221);
		glRectf(nodeX-nodeRadius,nodeY-nodeRadius,nodeX+nodeRadius,nodeY+nodeRadius);
		glLineWidth(2);
		glColor3ub(128,128,128);
		glLineRect(nodeX-nodeRadius,nodeY-nodeRadius,nodeX+nodeRadius,nodeY+nodeRadius);
	glTranslatef(-x,-y,0.0f);
}

void GraphNodePane::moveView(float x,float y){
	this->x+=x;
	this->y+=y;
}
