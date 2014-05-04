#include "NodeVisualizer.hpp"

#include "../gl.hpp"
#include "Node.hpp"
#include "Edge.hpp"

/**
 * Returns if point a is inside point b's radius
 */
static bool position_inside(wxPoint a,wxPoint b,float radius){
	return a.x > b.x-radius && a.x < b.x+radius && a.y > b.y-radius && a.y < b.y+radius;
}

namespace GraphStructure{
	wxBEGIN_EVENT_TABLE(NodeVisualizer,GLPane)
		EVT_MOTION      (NodeVisualizer::onMouseMove)
		EVT_LEFT_DOWN   (NodeVisualizer::onMouseLeftDown)
		EVT_LEFT_UP     (NodeVisualizer::onMouseLeftUp)
		EVT_RIGHT_DOWN  (NodeVisualizer::onMouseRightDown)
		EVT_RIGHT_UP    (NodeVisualizer::onMouseRightUp)
		EVT_LEAVE_WINDOW(NodeVisualizer::onMouseLeaveWindow)
		EVT_KEY_DOWN    (NodeVisualizer::onKeyDown)
		EVT_KEY_UP      (NodeVisualizer::onKeyUp)
		EVT_MOUSEWHEEL  (NodeVisualizer::onMouseWheel)
	wxEND_EVENT_TABLE()

	NodeVisualizer::NodeVisualizer(wxFrame* parent,NodeStatus& nodeStatus) : GLPane(parent),mouseDrag(false),mouseDragInitiationDistance(8),x(0.0f),y(0.0f),scale(1.0f),minScale(1/16),maxScale(128),nodeStatus(nodeStatus){}

	NodeVisualizer::~NodeVisualizer(){
		//Free all allocated nodes
		nodeStatus.removeAllNodesApply([](Node* node){delete node;});
	}

	void NodeVisualizer::onMouseLeftDown(wxMouseEvent& event){
		mouseClickAbsolutePos = getMouseEventAbsolutePosition(event);
		const wxPoint mouseClickPos = getMouseEventPosition(event);

		//If clicked on node
		auto node = nodeStatus.getNodeAt(mouseClickPos);
		if(node){
			//When the selected node is the same as the to be selected node
			if(nodeStatus.getSelectedNode()==node)
				mouseClickType = NodeVisualizer_MouseClickType::RESELECT_NODE;
			else{
				mouseClickType = NodeVisualizer_MouseClickType::SELECT_NODE;
				nodeStatus.selectNode(*node);
				Refresh();
			}
		}else{
			mouseClickType = NodeVisualizer_MouseClickType::EMPTYSPACE;
		}
	}

	void NodeVisualizer::onMouseLeftUp(wxMouseEvent& event){
		//If dragging
		if(mouseDrag){
			mouseDrag=false;
		}else{
			//If clicked at empty space
			if(mouseClickType==NodeVisualizer_MouseClickType::EMPTYSPACE){
				//If any node is selected
				if(nodeStatus.getSelectedNode()){
					nodeStatus.deselectNodes();
				}else{
					wxPoint mouseCurrentPos = getMouseEventPosition(event);
					//Create new node at mouse position
					nodeStatus.addNode(new Node(mouseCurrentPos,"Label"));
				}
				Refresh();
			}
		}

		mouseClickType = NodeVisualizer_MouseClickType::NONE;
	}

	void NodeVisualizer::onMouseRightDown(wxMouseEvent& event){}
	void NodeVisualizer::onMouseRightUp(wxMouseEvent& event){}

	void NodeVisualizer::onMouseWheel(wxMouseEvent& event){
		if(event.GetWheelAxis()==wxMOUSE_WHEEL_VERTICAL){//TODO: Only takes care of one step at a time
			if(event.GetWheelRotation()>0)
				zoomIn(2.0f,wxPoint(getWidth()/2.0f,getHeight()/2.0f));
			else
				zoomOut(2.0f,wxPoint(getWidth()/2.0f,getHeight()/2.0f));
			Refresh();
		}
	}

	void NodeVisualizer::onMouseLeaveWindow(wxMouseEvent& event){}
	void NodeVisualizer::onKeyDown(wxKeyEvent& event){}
	void NodeVisualizer::onKeyUp(wxKeyEvent& event){}

	void NodeVisualizer::onMouseMove(wxMouseEvent& event){
		const wxPoint mouseCurrentAbsolutePos = getMouseEventAbsolutePosition(event);

		if(event.Dragging()){
			if(mouseDrag){
				switch(mouseClickType){
					case NodeVisualizer_MouseClickType::EMPTYSPACE:
						moveView(mouseCurrentAbsolutePos.x-mousePreviousAbsolutePos.x,mouseCurrentAbsolutePos.y-mousePreviousAbsolutePos.y);
						break;

					case NodeVisualizer_MouseClickType::SELECT_NODE:
					case NodeVisualizer_MouseClickType::RESELECT_NODE:{
						const wxPoint mouseCurrentPos = getMouseEventPosition(event);
						nodeStatus.getSelectedNode()->pos = mouseCurrentPos;
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

	void NodeVisualizer::render(wxPaintEvent& event){
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_POLYGON_SMOOTH);
		glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
		glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);

		glTranslatef(x,y,0.0f);
		glScalef(scale,scale,1.0f);
		for(auto node=nodeStatus.getNodes().begin(); node!=nodeStatus.getNodes().end(); ++node){
			(*node)->render(event,nodeStatus.isNodeSelected(*node));
		}
		glScalef(1.0f/scale,1.0f/scale,1.0f);
		glTranslatef(-x,-y,0.0f);
	}

	void NodeVisualizer::moveView(float x,float y){
		this->x+=x;
		this->y+=y;
	}

	wxPoint NodeVisualizer::getMouseEventPosition(wxMouseEvent& event)const{
		wxPoint pos = getMouseEventAbsolutePosition(event);
		pos.x = (pos.x-x)/scale;
		pos.y = (pos.y-y)/scale;

		return pos;
	}

	wxPoint NodeVisualizer::getMouseEventAbsolutePosition(wxMouseEvent& event)const{
		return event.GetLogicalPosition(wxPaintDC(const_cast<NodeVisualizer*>(this)));
	}

	void NodeVisualizer::zoomIn(float scaling,wxPoint center){
		if(scale<maxScale){
			//Scale n x
			scale*=scaling;

			//Correct translation for zooming in to the center
			x-=center.x/scale;
			y-=center.y/scale;
		}
	}

	void NodeVisualizer::zoomOut(float scaling,wxPoint center){
		if(scale>minScale){
			//Correct translation for zooming out from the center
			x+=center.x/scale;
			y+=center.y/scale;

			//Scale 1/n x
			scale/=scaling;
		}
	}
}
