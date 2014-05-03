#ifndef __LOLIROFLE_WXGRAPHSTRUCTURE_GRAPH_FRAME_HPP_INCLUDED__
#define __LOLIROFLE_WXGRAPHSTRUCTURE_GRAPH_FRAME_HPP_INCLUDED__

#include "wx.hpp"

namespace GraphStructure{
	class Frame : public wxFrame{
	public:
		Frame(const wxSize& size);
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
		Frame_MenuID_FileNew,
		Frame_MenuID_FileOpen,
		Frame_MenuID_FileSave,
		Frame_MenuID_FileSaveAs,
	};
}

#endif
