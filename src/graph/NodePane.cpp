#include "NodePane.hpp"

#include "gl.hpp"
#include "Node.hpp"
#include "Edge.hpp"

namespace GraphStructure{
	static bool position_inside(wxPoint a,wxPoint b,float radius){
		return a.x > b.x-radius && a.x < b.x+radius && a.y > b.y-radius && a.y < b.y+radius;
	}

	wxBEGIN_EVENT_TABLE(NodePane,GLPane)
		EVT_MOTION      (NodePane::onMouseMove)
		EVT_LEFT_DOWN   (NodePane::onMouseLeftDown)
		EVT_LEFT_UP     (NodePane::onMouseLeftUp)
		EVT_RIGHT_DOWN  (NodePane::onMouseRightDown)
		EVT_RIGHT_UP    (NodePane::onMouseRightUp)
		EVT_LEAVE_WINDOW(NodePane::onMouseLeaveWindow)
		EVT_KEY_DOWN    (NodePane::onKeyDown)
		EVT_KEY_UP      (NodePane::onKeyUp)
		EVT_MOUSEWHEEL  (NodePane::onMouseWheel)
	wxEND_EVENT_TABLE()

	NodePane::NodePane(wxFrame* parent) : GLPane(parent),mouseDrag(false),mouseDragInitiationDistance(8),x(0.0f),y(0.0f),scale(1),minScale(1/16),maxScale(128){
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_POLYGON_SMOOTH);
		glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
		glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);
	}

	void NodePane::onMouseLeftDown(wxMouseEvent& event){
		mouseClickAbsolutePos = getMouseEventAbsolutePosition(event);
		mouseClickType = GraphNodePane_MouseClickType::EMPTYSPACE;
	}

	void NodePane::onMouseLeftUp(wxMouseEvent& event){
		if(mouseClickType==GraphNodePane_MouseClickType::EMPTYSPACE && !mouseDrag){
			wxPoint mouseCurrentPos = getMouseEventPosition(event);
		
			nodes.push_front(new Node(mouseCurrentPos.x,mouseCurrentPos.y,"Label"));

			Refresh();
		}

		mouseClickType = GraphNodePane_MouseClickType::NONE;
		mouseDrag=false;
	}

	void NodePane::onMouseRightDown(wxMouseEvent& event){}
	void NodePane::onMouseRightUp(wxMouseEvent& event){}
	void NodePane::onMouseWheel(wxMouseEvent& event){}
	void NodePane::onMouseLeaveWindow(wxMouseEvent& event){}
	void NodePane::onKeyDown(wxKeyEvent& event){}
	void NodePane::onKeyUp(wxKeyEvent& event){}

	void NodePane::onMouseMove(wxMouseEvent& event){
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

	void NodePane::render(wxPaintEvent& event){
		glTranslatef(x,y,0.0f);
		for(auto node=nodes.begin(); node!=nodes.end(); ++node){
			(*node)->render(event);
		}
		glTranslatef(-x,-y,0.0f);
	}

	void NodePane::moveView(float x,float y){
		this->x+=x;
		this->y+=y;
	}

	wxPoint NodePane::getMouseEventPosition(wxMouseEvent& event){
		wxPoint pos = getMouseEventAbsolutePosition(event);
		pos.x-=x;
		pos.y-=y;

		return pos;
	}

	wxPoint NodePane::getMouseEventAbsolutePosition(wxMouseEvent& event){
		return event.GetLogicalPosition(wxPaintDC(this));
	}
}
