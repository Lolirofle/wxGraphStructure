#ifndef __LOLIROFLE_WXGRAPHSTRUCTURE_GLPANE_HPP_INCLUDED__
#define __LOLIROFLE_WXGRAPHSTRUCTURE_GLPANE_HPP_INCLUDED__

#include "wx.hpp"
#include <wx/glcanvas.h>

class GLPane : public wxGLCanvas{
private:
	wxGLContext* m_context;
	wxDECLARE_EVENT_TABLE();

	void onRender(wxPaintEvent& event);

public:
	GLPane(wxFrame* parent);
	virtual ~GLPane();

	void onWindowResize(wxSizeEvent& event);

	int getWidth();
	int getHeight();

	virtual void render(wxPaintEvent& event)=0;
};
#endif
