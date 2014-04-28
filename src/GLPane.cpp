#include "GLPane.hpp"

#include "gl.hpp"

wxBEGIN_EVENT_TABLE(GLPane,wxGLCanvas)
	EVT_SIZE (GLPane::onWindowResize)
	EVT_PAINT(GLPane::onRender)
wxEND_EVENT_TABLE()

static int args[] = {WX_GL_RGBA,WX_GL_DOUBLEBUFFER,WX_GL_DEPTH_SIZE,16,0};

GLPane::GLPane(wxFrame* parent) : wxGLCanvas(parent,wxID_ANY,args,wxDefaultPosition,wxDefaultSize,wxFULL_REPAINT_ON_RESIZE){
	m_context = new wxGLContext(this);

	//Avoid flashing on M$ Windows
	SetBackgroundStyle(wxBG_STYLE_CUSTOM);
}

GLPane::~GLPane(){
	delete m_context;
}

void GLPane::onWindowResize(wxSizeEvent& event){
	Refresh();
}

int GLPane::getWidth(){
	return GetSize().x;
}

int GLPane::getHeight(){
	return GetSize().y;
}

void GLPane::onRender(wxPaintEvent& event){
	if(!IsShown())
		return;

	wxGLCanvas::SetCurrent(*m_context);
	wxPaintDC(this); // only to be used in paint events. use wxClientDC to paint outside the paint event

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glInit2D(0,0,getWidth(),getHeight(),251,248,244);
	glLoadIdentity();

	render(event);

	glFlush();
	SwapBuffers();
}
