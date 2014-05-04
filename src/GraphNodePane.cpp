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

GraphNodePane::GraphNodePane(wxFrame* parent,std::list<GraphNode*>& nodes,GraphNode*& selectedNode) : GLPane(parent),mouseDrag(false),mouseDragInitiationDistance(8),x(0.0f),y(0.0f),scale(1.0f),minScale(1/16),maxScale(128),nodes(nodes),selectedNode(selectedNode){}

GraphNodePane::~GraphNodePane(){
	//Free all allocated nodes
	while(!nodes.empty()){
		delete nodes.front();
		nodes.pop_front();
	}
}

void GraphNodePane::onMouseLeftDown(wxMouseEvent& event){
	mouseClickAbsolutePos = getMouseEventAbsolutePosition(event);
	const wxPoint mouseClickPos = getMouseEventPosition(event);

	//If clicked on node
	auto node = getNodeAt(mouseClickPos);
	if(node){
		//When the selected node is the same as the to be selected node
		if(selectedNode==node)
			mouseClickType = GraphNodePane_MouseClickType::RESELECT_NODE;
		else{
			mouseClickType = GraphNodePane_MouseClickType::SELECT_NODE;
			selectedNode = node;
			Refresh();
		}
	}else{
		mouseClickType = GraphNodePane_MouseClickType::EMPTYSPACE;
	}
}

void GraphNodePane::onMouseLeftUp(wxMouseEvent& event){
	//If dragging
	if(mouseDrag){
		mouseDrag=false;
	}else{
		//If clicked at empty space
		if(mouseClickType==GraphNodePane_MouseClickType::EMPTYSPACE){
			//If any node is selected
			if(selectedNode){
				selectedNode = NULL;
			}else{
				wxPoint mouseCurrentPos = getMouseEventPosition(event);
				//Create new node at mouse position
				nodes.push_back(new GraphNode(mouseCurrentPos,"Label"));
			}
			Refresh();
		}
	}

	mouseClickType = GraphNodePane_MouseClickType::NONE;
}

void GraphNodePane::onMouseRightDown(wxMouseEvent& event){}
void GraphNodePane::onMouseRightUp(wxMouseEvent& event){}

void GraphNodePane::onMouseWheel(wxMouseEvent& event){
	if(event.GetWheelAxis()==wxMOUSE_WHEEL_VERTICAL){//TODO: Only takes care of one step at a time
		if(event.GetWheelRotation()>0)
			zoomIn(2.0f,wxPoint(getWidth()/2.0f,getHeight()/2.0f));
		else
			zoomOut(2.0f,wxPoint(getWidth()/2.0f,getHeight()/2.0f));
		Refresh();
	}
}

void GraphNodePane::onMouseLeaveWindow(wxMouseEvent& event){}
void GraphNodePane::onKeyDown(wxKeyEvent& event){}
void GraphNodePane::onKeyUp(wxKeyEvent& event){}

void GraphNodePane::onMouseMove(wxMouseEvent& event){
	const wxPoint mouseCurrentAbsolutePos = getMouseEventAbsolutePosition(event);

	if(event.Dragging()){
		if(mouseDrag){
			switch(mouseClickType){
				case GraphNodePane_MouseClickType::EMPTYSPACE:
					moveView(mouseCurrentAbsolutePos.x-mousePreviousAbsolutePos.x,mouseCurrentAbsolutePos.y-mousePreviousAbsolutePos.y);
					break;

				case GraphNodePane_MouseClickType::SELECT_NODE:
				case GraphNodePane_MouseClickType::RESELECT_NODE:{
					const wxPoint mouseCurrentPos = getMouseEventPosition(event);
					selectedNode->pos = mouseCurrentPos;
				}	break;

				default:
					break;
			}
			Refresh();
		}else{
			if(!position_inside(mouseCurrentAbsolutePos,mouseClickAbsolutePos,mouseDragInitiationDistance))
				mouseDrag=true;
		}
	}

	mousePreviousAbsolutePos = mouseCurrentAbsolutePos;
}

void GraphNodePane::render(wxPaintEvent& event){
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);

	glTranslatef(x,y,0.0f);
	glScalef(scale,scale,1.0f);
	for(auto node=nodes.begin(); node!=nodes.end(); ++node){
		(*node)->render(event,*node==selectedNode);
	}
	glScalef(1.0f/scale,1.0f/scale,1.0f);
	glTranslatef(-x,-y,0.0f);
}

void GraphNodePane::moveView(float x,float y){
	this->x+=x;
	this->y+=y;
}

wxPoint GraphNodePane::getMouseEventPosition(wxMouseEvent& event){
	wxPoint pos = getMouseEventAbsolutePosition(event);
	pos.x = (pos.x-x)/scale;
	pos.y = (pos.y-y)/scale;

	return pos;
}

wxPoint GraphNodePane::getMouseEventAbsolutePosition(wxMouseEvent& event){
	return event.GetLogicalPosition(wxPaintDC(this));
}

GraphNode* GraphNodePane::getNodeAt(wxPoint pos){
	for(auto node=nodes.begin(); node!=nodes.end(); ++node){
		if(hypot((*node)->pos.x - pos.x,(*node)->pos.y - pos.y) < (*node)->radius){
			return *node;
		}
	}
	return NULL;
}

void GraphNodePane::zoomIn(float scaling,wxPoint center){
	if(scale<maxScale){
		//Scale n x
		scale*=scaling;

		//Correct translation for zooming in to the center
		x-=center.x/scale;
		y-=center.y/scale;
	}
}

void GraphNodePane::zoomOut(float scaling,wxPoint center){
	if(scale>minScale){
		//Correct translation for zooming out from the center
		x+=center.x/scale;
		y+=center.y/scale;

		//Scale 1/n x
		scale/=scaling;
	}
}
