#include "Frame.hpp"

#include "defs.h"

namespace GraphStructure{
	wxBEGIN_EVENT_TABLE(Frame,wxFrame)
		EVT_MENU(Frame_MenuID_FileNew   ,Frame::onNew)
		EVT_MENU(Frame_MenuID_FileOpen  ,Frame::onOpen)
		EVT_MENU(Frame_MenuID_FileSave  ,Frame::onSave)
		EVT_MENU(Frame_MenuID_FileSaveAs,Frame::onSaveAs)
		EVT_MENU(wxID_EXIT                   ,Frame::onExit)
		EVT_MENU(wxID_ABOUT                  ,Frame::onAbout)
	wxEND_EVENT_TABLE()

	Frame::Frame(const wxSize& size) : wxFrame(NULL,wxID_ANY,wxT(APP_NAME),wxDefaultPosition,size){
		//File menu
		wxMenu *menu_file = new wxMenu;
		menu_file->Append(
			Frame_MenuID_FileNew,
			wxT("&New\tCtrl-N"),
			wxT("New graph")
		);
		menu_file->Append(
			Frame_MenuID_FileOpen,
			wxT("&Open\tCtrl-O"),
			wxT("Open graph from file")
		);
		menu_file->Append(
			Frame_MenuID_FileSave,
			wxT("&Save\tCtrl-S"),
			wxT("Save graph to the current file")
		);
		menu_file->Append(
			Frame_MenuID_FileSaveAs,
			wxT("Save &As...\tShift-Ctrl-S"),
			wxT("Save graph to a file")
		);
		menu_file->AppendSeparator();
		menu_file->Append(wxID_EXIT);

		//Help menu
		wxMenu *menu_help = new wxMenu;
		menu_help->Append(wxID_ABOUT);

		//Menu bar
		wxMenuBar *menuBar = new wxMenuBar;
		menuBar->Append(menu_file,wxT("&File"));
		menuBar->Append(menu_help,wxT("&Help"));
		SetMenuBar(menuBar);

		//Status bar
		CreateStatusBar();
		SetStatusText(wxT("Welcome to wxWidgets!"));
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

	void Frame::onNew   (wxCommandEvent& event){}
	void Frame::onOpen  (wxCommandEvent& event){}
	void Frame::onSave  (wxCommandEvent& event){}
	void Frame::onSaveAs(wxCommandEvent& event){}
}
