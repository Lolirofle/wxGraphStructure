#include "App.hpp"

#include "Frame.hpp"
#include "NodePane.hpp"

wxIMPLEMENT_APP(GraphStructure::App);

namespace GraphStructure{
	bool App::OnInit(){
		//Creates the frame
		Frame *frame = new Frame(wxSize(450,340));

		//Horizontal sizer layout
		wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
			sizer->Add(
				new NodePane(frame),
				true,
				wxEXPAND
			);

			sizer->Add(
				new wxTextCtrl(frame,-1,wxT("Initial text"),wxDefaultPosition,wxSize(100,60),wxTE_MULTILINE),
				/*Stretchable*/ true,
				/*Flags      */ wxEXPAND | wxALL
			);
		frame->SetSizer(sizer);
		frame->SetAutoLayout(true);

		//Show the frame
		frame->Show(true);

		return true;
	}
}
