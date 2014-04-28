#ifndef __LOLIROFLE_WXGRAPHSTRUCTURE_GLPANE_HPP_INCLUDED__
#define __LOLIROFLE_WXGRAPHSTRUCTURE_GLPANE_HPP_INCLUDED__

#include "wx.hpp"
#include <wx/glcanvas.h>

class GLPane : public wxGLCanvas{
private:
	wxGLContext* m_context;

public:
	GLPane(wxFrame* parent,int* args);
	virtual ~GLPane();

	void onWindowResize(wxSizeEvent& event);

	int getWidth();
	int getHeight();

	void render(wxPaintEvent& evt);
	
	void onMouseMove(wxMouseEvent& event);
	void onMouseLeftDown(wxMouseEvent& event);
	void onMouseLeftUp(wxMouseEvent& event);
	void onMouseRightDown(wxMouseEvent& event);
	void onMouseRightUp(wxMouseEvent& event);
	void onMouseWheel(wxMouseEvent& event);
	void onMouseLeaveWindow(wxMouseEvent& event);
	void onKeyDown(wxKeyEvent& event);
	void onKeyUp(wxKeyEvent& event);

private:
	wxDECLARE_EVENT_TABLE();
};
#endif
