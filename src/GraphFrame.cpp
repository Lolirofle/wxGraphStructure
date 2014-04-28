#include "GraphFrame.hpp"

#include "defs.h"

wxBEGIN_EVENT_TABLE(GraphFrame,wxFrame)
	EVT_MENU(GraphFrame_MenuID_FileNew   ,GraphFrame::onNew)
	EVT_MENU(GraphFrame_MenuID_FileOpen  ,GraphFrame::onOpen)
	EVT_MENU(GraphFrame_MenuID_FileSave  ,GraphFrame::onSave)
	EVT_MENU(GraphFrame_MenuID_FileSaveAs,GraphFrame::onSaveAs)
	EVT_MENU(wxID_EXIT                   ,GraphFrame::onExit)
	EVT_MENU(wxID_ABOUT                  ,GraphFrame::onAbout)
wxEND_EVENT_TABLE()

GraphFrame::GraphFrame(const wxSize& size) : wxFrame(NULL,wxID_ANY,wxT(APP_NAME),wxDefaultPosition,size){
	//File menu
	wxMenu *menu_file = new wxMenu;
	menu_file->Append(
		GraphFrame_MenuID_FileNew,
		wxT("&New\tCtrl-N"),
		wxT("New graph")
	);
	menu_file->Append(
		GraphFrame_MenuID_FileOpen,
		wxT("&Open\tCtrl-O"),
		wxT("Open graph from file")
	);
	menu_file->Append(
		GraphFrame_MenuID_FileSave,
		wxT("&Save\tCtrl-S"),
		wxT("Save graph to the current file")
	);
	menu_file->Append(
		GraphFrame_MenuID_FileSaveAs,
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
