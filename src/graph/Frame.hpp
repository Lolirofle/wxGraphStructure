#ifndef __LOLIROFLE_WXGRAPHSTRUCTURE_GRAPH_FRAME_HPP_INCLUDED__
#define __LOLIROFLE_WXGRAPHSTRUCTURE_GRAPH_FRAME_HPP_INCLUDED__

#include "wx.hpp"
#include "Node.hpp"
#include "NodeStatus.hpp"
#include "WindowViews.hpp"
#include <list>

namespace GraphStructure{
	class Frame : public wxFrame{
	public:
		Frame(const wxSize& size,NodeStatus& nodeStatus);

		void setupLayout(const WindowViewContainer& viewContainer);
	private:
		NodeStatus& nodeStatus;
		
		/**
		 * @return True  => Proceed
		 *         False => Cancel
		 */
		bool showSaveConfirmation();

		//Defines various events of the application
		void onNew   (wxCommandEvent& event);
		void onOpen  (wxCommandEvent& event);
		void onSave  (wxCommandEvent& event);
		void onSaveAs(wxCommandEvent& event);
		void onExit  (wxCommandEvent& event);
		void onAbout (wxCommandEvent& event);
		
		wxDECLARE_EVENT_TABLE();
	};

	enum class Window_MenuID : int{
		FileNew = 1,
		FileOpen,
		FileSave,
		FileSaveAs,
		
		ViewNodeVis,
		ViewInfo,
		ViewNodeProp
	};
}

#endif
