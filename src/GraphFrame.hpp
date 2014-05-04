#ifndef __LOLIROFLE_WXGRAPHSTRUCTURE_GRAPHFRAME_HPP_INCLUDED__
#define __LOLIROFLE_WXGRAPHSTRUCTURE_GRAPHFRAME_HPP_INCLUDED__

#include "wx.hpp"
#include "GraphNode.hpp"
#include <array>
#include <list>

enum class GraphFrameViews : unsigned int{
	NodeVisualizer,
	Information,
	NodeProperties,

	length
};

class GraphFrame : public wxFrame{
public:
	GraphFrame(const wxSize& size,std::list<GraphNode*>& nodes,GraphNode*& selectedNode);

	wxWindow* getView(GraphFrameViews viewId);

private:
	std::array<wxWindow*,static_cast<unsigned int>(GraphFrameViews::length)> views;

	void setView(GraphFrameViews viewId,wxWindow* window);

	//Defines various events of the application
	void onNew   (wxCommandEvent& event);
	void onOpen  (wxCommandEvent& event);
	void onSave  (wxCommandEvent& event);
	void onSaveAs(wxCommandEvent& event);
	void onExit  (wxCommandEvent& event);
	void onAbout (wxCommandEvent& event);
	
	wxDECLARE_EVENT_TABLE();
};

enum class GraphFrame_MenuID : int{
	FileNew = 1,
	FileOpen,
	FileSave,
	FileSaveAs,
	
	ViewNodeVis,
	ViewInfo,
	ViewNodeProp
};

#endif
