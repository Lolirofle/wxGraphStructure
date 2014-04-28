#include "GraphApp.hpp"

#include "GraphFrame.hpp"
#include "GLPane.hpp"

wxIMPLEMENT_APP(GraphApp);

bool GraphApp::OnInit(){
	//Creates the frame
	GraphFrame *frame = new GraphFrame(wxSize(450,340));

	//Horizontal sizer layout
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
		int args[] = {WX_GL_RGBA,WX_GL_DOUBLEBUFFER,WX_GL_DEPTH_SIZE,16,0};
		sizer->Add(
			new GLPane(frame,args),
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
