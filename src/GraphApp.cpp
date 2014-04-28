#include "GraphApp.hpp"

#include "GraphFrame.hpp"
#include "GraphNodePane.hpp"

wxIMPLEMENT_APP(GraphApp);

bool GraphApp::OnInit(){
	//Creates the frame
	GraphFrame *frame = new GraphFrame(wxSize(450,340));

	//Horizontal sizer layout
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
		sizer->Add(
			new GraphNodePane(frame),
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
