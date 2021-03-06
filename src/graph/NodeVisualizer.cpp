#include "NodeVisualizer.hpp"

#include "../gl.hpp"
#include "Node.hpp"
#include "Edge.hpp"

/**
 * Returns if point a is inside point b's radius
 */
static bool point_insideRadius(wxPoint a,wxPoint b,float radius){
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
		EVT_CONTEXT_MENU(NodeVisualizer::onContextMenu)
	wxEND_EVENT_TABLE()

	NodeVisualizer::NodeVisualizer(wxFrame* parent,NodeStatus& nodeStatus) : GLPane(parent),mouseDrag(false),mouseDragInitiationDistance(8),x(0.0f),y(0.0f),scale(1.0f),minScale(1/16),maxScale(128),nodeStatus(nodeStatus){
		contextMenuGraph = new wxMenu;
			contextMenuGraph->Append         (NodeVisualizer_GraphContextMenuID::Unknown   ,"<Graph>"    )->Enable(false);
			contextMenuGraph->AppendSeparator();
			contextMenuGraph->Append         (NodeVisualizer_GraphContextMenuID::AddNode   ,"Add Node...");
			contextMenuGraph->AppendSeparator();
			contextMenuGraph->Append         (NodeVisualizer_GraphContextMenuID::Copy      ,"Copy"       )->Enable(nodeStatus.hasNodeSelected());
			contextMenuGraph->Append         (NodeVisualizer_GraphContextMenuID::Cut       ,"Cut"        )->Enable(nodeStatus.hasNodeSelected());
			contextMenuGraph->Append         (NodeVisualizer_GraphContextMenuID::Paste     ,"Paste"      )->Enable(nodeStatus.hasNodeSelected());
			contextMenuGraph->Append         (NodeVisualizer_GraphContextMenuID::Remove    ,"Remove"     )->Enable(nodeStatus.hasNodeSelected());
			contextMenuGraph->Append         (NodeVisualizer_GraphContextMenuID::SelectAll ,"Select All" );
			contextMenuGraph->AppendSeparator();
			contextMenuGraph->Append         (NodeVisualizer_GraphContextMenuID::Properties,"Properties" );
			contextMenuGraph->Connect(wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&NodeVisualizer::onGraphContextMenu,NULL,this);

		contextMenuNodeConnect = new wxMenu;
			contextMenuNodeConnect->Append(NodeVisualizer_NodeContextMenuID::ConnectToThisFromSelect,"To this from selection")->Enable(nodeStatus.hasNodeSelected());
			contextMenuNodeConnect->Append(NodeVisualizer_NodeContextMenuID::ConnectToSelectFromThis,"To selection from this")->Enable(nodeStatus.hasNodeSelected());
			contextMenuNodeConnect->Append(NodeVisualizer_NodeContextMenuID::ConnectChooseFromList  ,"Choose from list...");
			contextMenuNodeConnect->Connect(wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(NodeVisualizer::onNodeContextMenu),NULL,this);

		contextMenuNode = new wxMenu;
			contextMenuNode->Append         (NodeVisualizer_NodeContextMenuID::Unknown        ,"<Node>"     )->Enable(false);
			contextMenuNode->AppendSeparator();
			contextMenuNode->Append         (NodeVisualizer_NodeContextMenuID::Remove     ,"Remove"     );
			contextMenuNode->AppendSubMenu  (contextMenuNodeConnect,"Connect...");
			contextMenuNode->AppendSeparator();
			contextMenuNode->Append         (NodeVisualizer_NodeContextMenuID::Properties ,"Properties" );
			contextMenuNode->Connect(wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&NodeVisualizer::onNodeContextMenu,NULL,this);
	}

	NodeVisualizer::~NodeVisualizer(){
		//Free all allocated nodes
		nodeStatus.removeAllNodes();

		//Free menus
		delete contextMenuGraph;
		delete contextMenuNode;

		//Free submenus
		/*This is freed when the menus are freed?
		delete contextMenuNodeConnect;
		*/
	}

	void NodeVisualizer::onMouseLeftDown(wxMouseEvent& event){
		mouseClickAbsolutePos = getMouseEventAbsolutePosition(event);
		const wxPoint mouseClickPos = getMouseEventPosition(event);

		//If clicked on node
		auto node = nodeStatus.getNodeAt(mouseClickPos);
		if(node){
			//When the selected node is the same as the to be selected node
			if(nodeStatus.isNodeSelected(node)){
				mouseClickType = NodeVisualizer_MouseClickType::RESELECT_NODE;
			}else{
				mouseClickType = NodeVisualizer_MouseClickType::SELECT_NODE;
			}
			if(!event.ShiftDown())
				nodeStatus.deselectNodes();
			nodeStatus.selectNode(*node);
		}else{
			mouseClickType = NodeVisualizer_MouseClickType::EMPTYSPACE;
		}

		event.Skip();
	}

	void NodeVisualizer::onMouseLeftUp(wxMouseEvent& event){
		//If dragging
		if(mouseDrag){
			mouseDrag=false;
		}else{
			//If clicked at empty space
			if(mouseClickType==NodeVisualizer_MouseClickType::EMPTYSPACE){
				//If any node is selected
				if(nodeStatus.hasNodeSelected()){
					nodeStatus.deselectNodes();
				}else{
					wxPoint mouseCurrentPos = getMouseEventPosition(event);
					//Create new node at mouse position
					nodeStatus.addNode(Node(mouseCurrentPos,"Label"));
				}
			}
		}

		mouseClickType = NodeVisualizer_MouseClickType::NONE;

		event.Skip();
	}

	void NodeVisualizer::onMouseRightDown(wxMouseEvent& event){
		const wxPoint mouseClickPos = getMouseEventPosition(event);
	
		//If clicked on node
		auto node = nodeStatus.getNodeAt(mouseClickPos);
		if(node){
			PopupMenu(contextMenuNode);
		}else{
			event.Skip();
		}
	}

	void NodeVisualizer::onMouseRightUp(wxMouseEvent& event){
		event.Skip();
	}

	void NodeVisualizer::onMouseWheel(wxMouseEvent& event){
		if(event.GetWheelAxis()==wxMOUSE_WHEEL_VERTICAL){//TODO: Only takes care of one step at a time
			if(event.GetWheelRotation()>0)
				zoomIn(2.0f,wxPoint(getWidth()/2.0f,getHeight()/2.0f));
			else
				zoomOut(2.0f,wxPoint(getWidth()/2.0f,getHeight()/2.0f));
			Refresh();
		}

		event.Skip();
	}

	void NodeVisualizer::onMouseLeaveWindow(wxMouseEvent& event){
		event.Skip();
	}
	
	void NodeVisualizer::onKeyDown(wxKeyEvent& event){
		switch(event.GetKeyCode()){
			case WXK_SPACE:
				nodeStatus.connect(*nodeStatus.getSelectedNodes().front(),Edge(*nodeStatus.getSelectedNodes().back()));
				break;

			case WXK_DELETE:
				if(!nodeStatus.hasNodeSelected())
					break;

				//Remove all selected nodes
				for(auto node=nodeStatus.getSelectedNodes().begin(); node!=nodeStatus.getSelectedNodes().end(); ++node){
					nodeStatus.removeNode(*node);
				}

				//Deselect the removed nodes
				nodeStatus.deselectNodes();

				break;

			default:
				goto CheckCharCode;
		}
		goto End;

		CheckCharCode:{
			auto chr = event.GetUnicodeKey();

			if(chr == '+'){
				zoomIn(2,wxPoint(getWidth()/2.0f,getHeight()/2.0f));
				Refresh();
			}else if(chr == '-'){
				zoomOut(2,wxPoint(getWidth()/2.0f,getHeight()/2.0f));
				Refresh();
			}
		}

		End:
		event.Skip();
	}
	
	void NodeVisualizer::onKeyUp(wxKeyEvent& event){
		event.Skip();
	}

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
						//TODO: Implement moving all selected nodes
						nodeStatus.getSelectedNodes().front()->pos = mouseCurrentPos;
					}	break;

					default:
						break;
				}
				Refresh();
			}else{
				if(!point_insideRadius(mouseCurrentAbsolutePos,mouseClickAbsolutePos,mouseDragInitiationDistance))
					mouseDrag=true;
			}
		}

		mousePreviousAbsolutePos = mouseCurrentAbsolutePos;

		event.Skip();
	}

	void NodeVisualizer::onContextMenu(wxContextMenuEvent& event){
		PopupMenu(contextMenuGraph);
		event.Skip();
	}

	void NodeVisualizer::onGraphContextMenu(wxCommandEvent& event){
		switch(event.GetId()){
			case NodeVisualizer_GraphContextMenuID::SelectAll:
				nodeStatus.selectNodes();
				break;

			default:
				break;
		}
	}

	void NodeVisualizer::onNodeContextMenu(wxCommandEvent& event){
		std::cout<<event.GetId()<<std::endl;
	}

	void NodeVisualizer::render(wxPaintEvent& event){
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_POLYGON_SMOOTH);
		glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
		glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);

		glTranslatef(x,y,0.0f);
		glScalef(scale,scale,1.0f);

		//Edges
		for(auto node=nodeStatus.getNodes().begin(); node!=nodeStatus.getNodes().end(); ++node){
			for(auto edge=node->connections.begin(); edge!=node->connections.end(); ++edge){
				edge->render(event,*node);
			}
		}

		//Nodes
		for(auto node=nodeStatus.getNodes().begin(); node!=nodeStatus.getNodes().end(); ++node){
			node->render(event,nodeStatus.isNodeSelected(&*node));
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
