#ifndef __LOLIROFLE_WXGRAPHSTRUCTURE_GRAPHFRAME_HPP_INCLUDED__
#define __LOLIROFLE_WXGRAPHSTRUCTURE_GRAPHFRAME_HPP_INCLUDED__

#include "wx.hpp"

class GraphFrame : public wxFrame{
public:
	GraphFrame(const wxSize& size);
private:
	//Defines various events of the application
	void onNew   (wxCommandEvent& event);
	void onOpen  (wxCommandEvent& event);
	void onSave  (wxCommandEvent& event);
	void onSaveAs(wxCommandEvent& event);
	void onExit  (wxCommandEvent& event);
	void onAbout (wxCommandEvent& event);
	
	wxDECLARE_EVENT_TABLE();
};

enum{
	GraphFrame_MenuID_FileNew,
	GraphFrame_MenuID_FileOpen,
	GraphFrame_MenuID_FileSave,
	GraphFrame_MenuID_FileSaveAs,
};

#endif
