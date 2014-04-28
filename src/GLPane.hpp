#ifndef __LOLIROFLE_WXGRAPHSTRUCTURE_GLPANE_HPP_INCLUDED__
#define __LOLIROFLE_WXGRAPHSTRUCTURE_GLPANE_HPP_INCLUDED__

#include "wx.hpp"
#include <wx/glcanvas.h>

class GLPane : public wxGLCanvas{
public:
	GLPane(wxFrame* parent,int* args);
	virtual ~GLPane();

	void resized(wxSizeEvent& evt);

	int getWidth();
	int getHeight();

	void render(wxPaintEvent& evt);

private:
    wxGLContext* m_context;
	
	void mouseMoved(wxMouseEvent& event);
	void mouseDown(wxMouseEvent& event);
	void mouseWheelMoved(wxMouseEvent& event);
	void mouseReleased(wxMouseEvent& event);
	void rightClick(wxMouseEvent& event);
	void mouseLeftWindow(wxMouseEvent& event);
	void keyPressed(wxKeyEvent& event);
	void keyReleased(wxKeyEvent& event);

	wxDECLARE_EVENT_TABLE();
};
#endif
