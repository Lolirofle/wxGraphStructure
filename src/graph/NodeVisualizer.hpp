#ifndef __LOLIROFLE_WXGRAPHSTRUCTURE_GRAPH_NODEVISUALIZER_HPP_INCLUDED__
#define __LOLIROFLE_WXGRAPHSTRUCTURE_GRAPH_NODEVISUALIZER_HPP_INCLUDED__

#include "../wx.hpp"
#include "../GLPane.hpp"
#include "NodeStatus.hpp"
#include <list>

namespace GraphStructure{
	class Node;

	enum class NodeVisualizer_MouseClickType{
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

	namespace NodeVisualizer_ContextMenuID{enum{
		Unknown = 1,

		NodeRemove,
		NodeConnectToThisFromSelect,
		NodeConnectToSelectFromThis,
		NodeConnectChooseFromList,
		NodeProperties,
		
		GraphAddNode,
		GraphCopy,
		GraphCut,
		GraphPaste,
		GraphRemove,
		GraphSelectAll,
		GraphProperties
	};}

	enum class NodeVisualizer_MouseReleaseType{
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

	class NodeVisualizer : public GLPane{
	private:
		//Mouse control
		wxPoint mouseClickAbsolutePos,
		        mousePreviousAbsolutePos;
		NodeVisualizer_MouseClickType mouseClickType;
		bool mouseDrag;
		unsigned short mouseDragInitiationDistance;

		//View
		float x,y;
		float scale;
		float minScale;
		float maxScale;

		//Data
		NodeStatus& nodeStatus;

		//Menus
		wxMenu* contextMenuGraph;
		wxMenu* contextMenuNode;
		wxMenu* contextMenuNodeConnect;

		wxDECLARE_EVENT_TABLE();
		
	protected:
		Node* getNodeAt(wxPoint pos);

	public:
		NodeVisualizer(wxFrame* parent,NodeStatus& nodeStatus);
		virtual ~NodeVisualizer();

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
		void onContextMenu(wxContextMenuEvent& event);
		void onNodeContextMenuRemove(wxCommandEvent& event);
		void onNodeContextMenuConnectToThisFromSelect(wxCommandEvent& event);
		void onNodeContextMenuConnectToSelectFromThis(wxCommandEvent& event);
		void onNodeContextMenuConnectChooseFromList(wxCommandEvent& event);

		void moveView(float x,float y);

		wxPoint getMouseEventPosition(wxMouseEvent& event)const;
		wxPoint getMouseEventAbsolutePosition(wxMouseEvent& event)const;

		void zoomIn(float scaling,wxPoint center);
		void zoomOut(float scaling,wxPoint center);
	};
}

#endif
