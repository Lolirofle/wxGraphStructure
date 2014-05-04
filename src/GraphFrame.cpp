#include "GraphFrame.hpp"

#include "defs.h"
#include "GraphNodePane.hpp"

wxBEGIN_EVENT_TABLE(GraphFrame,wxFrame)
	EVT_MENU(static_cast<int>(GraphFrame_MenuID::FileNew)   ,GraphFrame::onNew)
	EVT_MENU(static_cast<int>(GraphFrame_MenuID::FileOpen)  ,GraphFrame::onOpen)
	EVT_MENU(static_cast<int>(GraphFrame_MenuID::FileSave)  ,GraphFrame::onSave)
	EVT_MENU(static_cast<int>(GraphFrame_MenuID::FileSaveAs),GraphFrame::onSaveAs)
	EVT_MENU(wxID_EXIT                                      ,GraphFrame::onExit)
	EVT_MENU(wxID_ABOUT                                     ,GraphFrame::onAbout)
wxEND_EVENT_TABLE()

GraphFrame::GraphFrame(const wxSize& size,std::list<GraphNode*>& nodes,GraphNode*& selectedNode) : wxFrame(NULL,wxID_ANY,wxT(APP_NAME),wxDefaultPosition,size){
	///////////////////////////////////
	// Views
	//
	setView(GraphFrameViews::NodeVisualizer,new GraphNodePane(this,nodes,selectedNode));
	setView(GraphFrameViews::Information   ,new wxTextCtrl(this,-1,wxT("Initial text"),wxDefaultPosition,wxSize(100,60),wxTE_MULTILINE));

	//Horizontal sizer layout
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
		sizer->Add(
			getView(GraphFrameViews::NodeVisualizer),
			true,
			wxEXPAND
		);

		sizer->Add(
			getView(GraphFrameViews::Information),
			/*Stretchable*/ true,
			/*Flags      */ wxEXPAND | wxALL
		);
	SetSizer(sizer);
	SetAutoLayout(true);

	///////////////////////////////////
	// Menu bar
	//

	//File menu
	wxMenu *menu_file = new wxMenu;
	menu_file->Append(
		static_cast<int>(GraphFrame_MenuID::FileNew),
		wxT("&New\tCtrl-N"),
		wxT("New graph")
	);
	menu_file->Append(
		static_cast<int>(GraphFrame_MenuID::FileOpen),
		wxT("&Open\tCtrl-O"),
		wxT("Open graph from file")
	);
	menu_file->Append(
		static_cast<int>(GraphFrame_MenuID::FileSave),
		wxT("&Save\tCtrl-S"),
		wxT("Save graph to the current file")
	);
	menu_file->Append(
		static_cast<int>(GraphFrame_MenuID::FileSaveAs),
		wxT("Save &As...\tShift-Ctrl-S"),
		wxT("Save graph to a file")
	);
	menu_file->AppendSeparator();
	menu_file->Append(wxID_EXIT);

	//View menu
	wxMenu *menu_view = new wxMenu;
	menu_view->AppendCheckItem(
		static_cast<int>(GraphFrame_MenuID::ViewNodeVis),
		wxT("Node Visualizer"),
		wxT("Visualizes the graph nodes")
	);
	menu_view->AppendCheckItem(
		static_cast<int>(GraphFrame_MenuID::ViewInfo),
		wxT("Information"),
		wxT("Shows general information about the graph")
	);
	menu_view->AppendCheckItem(
		static_cast<int>(GraphFrame_MenuID::ViewNodeProp),
		wxT("Node Properties"),
		wxT("Shows information about the selected nodes")
	);

	//Help menu
	wxMenu *menu_help = new wxMenu;
	menu_help->Append(wxID_ABOUT);

	//Menu bar
	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append(menu_file,wxT("&File"));
	menuBar->Append(menu_view,wxT("&View"));
	menuBar->Append(menu_help,wxT("&Help"));
	SetMenuBar(menuBar);

	///////////////////////////////////
	// Status bar
	//
	CreateStatusBar();
	SetStatusText(wxT(""));
}

void GraphFrame::onExit(wxCommandEvent& event){
	Close(true);
}

void GraphFrame::onAbout(wxCommandEvent& event){
	//Message box creation
	wxMessageBox(
		//Content
		wxT(APP_NAME "\n\nCopyright © 2014 Lolirofle"),

		//Title
		wxT("About " APP_NAME),

		//Buttons
		wxOK | wxICON_INFORMATION
	);
}

void GraphFrame::onNew   (wxCommandEvent& event){}
void GraphFrame::onOpen  (wxCommandEvent& event){}
void GraphFrame::onSave  (wxCommandEvent& event){}
void GraphFrame::onSaveAs(wxCommandEvent& event){}

wxWindow* GraphFrame::getView(GraphFrameViews viewId){
	return views[static_cast<unsigned int>(viewId)];
}

void GraphFrame::setView(GraphFrameViews viewId,wxWindow* window){
	views[static_cast<unsigned int>(viewId)] = window;
}
