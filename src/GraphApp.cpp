#include "GraphApp.hpp"

#include "GraphFrame.hpp"

wxIMPLEMENT_APP(GraphApp);

bool GraphApp::OnInit(){
	//Prepare nodes
	selectedNode = NULL;

	//Creates the frame
	GraphFrame *frame = new GraphFrame(wxSize(450,340),nodes,selectedNode);

	//Show the frame
	frame->Show(true);

	return true;
}
