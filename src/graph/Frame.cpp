#include "Frame.hpp"

#include "defs.h"
#include "NodeVisualizer.hpp"

namespace GraphStructure{
	wxBEGIN_EVENT_TABLE(Frame,wxFrame)
		EVT_MENU(static_cast<int>(Window_MenuID::FileNew)   ,Frame::onNew)
		EVT_MENU(static_cast<int>(Window_MenuID::FileOpen)  ,Frame::onOpen)
		EVT_MENU(static_cast<int>(Window_MenuID::FileSave)  ,Frame::onSave)
		EVT_MENU(static_cast<int>(Window_MenuID::FileSaveAs),Frame::onSaveAs)
		EVT_MENU(wxID_EXIT                                  ,Frame::onExit)
		EVT_MENU(wxID_ABOUT                                 ,Frame::onAbout)
	wxEND_EVENT_TABLE()

	Frame::Frame(const wxSize& size,NodeStatus& nodeStatus) : wxFrame(NULL,wxID_ANY,wxT(APP_NAME),wxDefaultPosition,size),nodeStatus(nodeStatus){
		///////////////////////////////////
		// Menu bar
		//

		//File menu
		wxMenu *menu_file = new wxMenu;
		menu_file->Append(
			static_cast<int>(Window_MenuID::FileNew),
			wxT("&New\tCtrl-N"),
			wxT("New graph")
		);
		menu_file->Append(
			static_cast<int>(Window_MenuID::FileOpen),
			wxT("&Open\tCtrl-O"),
			wxT("Open graph from file")
		);
		menu_file->Append(
			static_cast<int>(Window_MenuID::FileSave),
			wxT("&Save\tCtrl-S"),
			wxT("Save graph to the current file")
		);
		menu_file->Append(
			static_cast<int>(Window_MenuID::FileSaveAs),
			wxT("Save &As...\tShift-Ctrl-S"),
			wxT("Save graph to a file")
		);
		menu_file->AppendSeparator();
		menu_file->Append(wxID_EXIT);

		//View menu
		wxMenu *menu_view = new wxMenu;
		menu_view->AppendCheckItem(
			static_cast<int>(Window_MenuID::ViewNodeVis),
			wxT("Node Visualizer"),
			wxT("Visualizes the graph nodes")
		);
		menu_view->AppendCheckItem(
			static_cast<int>(Window_MenuID::ViewInfo),
			wxT("Information"),
			wxT("Shows general information about the graph")
		);
		menu_view->AppendCheckItem(
			static_cast<int>(Window_MenuID::ViewNodeProp),
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

	void Frame::setupLayout(const WindowViewContainer& viewContainer){
		///////////////////////////////////
		// Layout
		//
		
		wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
			sizer->Add(
				viewContainer.getView(WindowViews::NodeVisualizer),
				true,
				wxEXPAND
			);

			wxBoxSizer* sizerV = new wxBoxSizer(wxVERTICAL);
				sizerV->Add(
					viewContainer.getView(WindowViews::NodeProperties),
					true,
					wxEXPAND
				);

				sizerV->Add(
					viewContainer.getView(WindowViews::Information),
					/*Stretchable*/ true,
					/*Flags      */ wxEXPAND | wxALL
				);
			sizer->Add(
				sizerV,
				true,
				wxEXPAND
			);
		SetSizer(sizer);
		SetAutoLayout(true);
	}

	void Frame::onExit(wxCommandEvent& event){
		Close(true);
	}

	void Frame::onAbout(wxCommandEvent& event){
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

	void Frame::onNew   (wxCommandEvent& event){
		nodeStatus.removeAllNodesApply([](Node* node){delete node;});
	}
	void Frame::onOpen  (wxCommandEvent& event){}
	void Frame::onSave  (wxCommandEvent& event){}
	void Frame::onSaveAs(wxCommandEvent& event){}
}
