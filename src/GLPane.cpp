#include "GLPane.hpp"

#include "gl.hpp"

wxBEGIN_EVENT_TABLE(GLPane,wxGLCanvas)
	EVT_MOTION      (GLPane::onMouseMove)
	EVT_LEFT_DOWN   (GLPane::onMouseLeftDown)
	EVT_LEFT_UP     (GLPane::onMouseLeftUp)
	EVT_RIGHT_DOWN  (GLPane::onMouseRightDown)
	EVT_RIGHT_UP    (GLPane::onMouseRightUp)
	EVT_LEAVE_WINDOW(GLPane::onMouseLeaveWindow)
	EVT_SIZE        (GLPane::onWindowResize)
	EVT_KEY_DOWN    (GLPane::onKeyDown)
	EVT_KEY_UP      (GLPane::onKeyUp)
	EVT_MOUSEWHEEL  (GLPane::onMouseWheel)
	EVT_PAINT       (GLPane::render)
wxEND_EVENT_TABLE()

void GLPane::onMouseMove(wxMouseEvent& event){}
void GLPane::onMouseLeftDown(wxMouseEvent& event){}
void GLPane::onMouseLeftUp(wxMouseEvent& event){}
void GLPane::onMouseRightDown(wxMouseEvent& event){}
void GLPane::onMouseRightUp(wxMouseEvent& event){}
void GLPane::onMouseWheel(wxMouseEvent& event){}
void GLPane::onMouseLeaveWindow(wxMouseEvent& event){}
void GLPane::onKeyDown(wxKeyEvent& event){}
void GLPane::onKeyUp(wxKeyEvent& event){}

GLPane::GLPane(wxFrame* parent,int* args) : wxGLCanvas(parent,wxID_ANY,args,wxDefaultPosition,wxDefaultSize,wxFULL_REPAINT_ON_RESIZE){
	m_context = new wxGLContext(this);

	//Avoid flashing on M$ Windows
	SetBackgroundStyle(wxBG_STYLE_CUSTOM);
}

GLPane::~GLPane(){
	delete m_context;
}

void GLPane::onWindowResize(wxSizeEvent& evt){
	Refresh();
}

int GLPane::getWidth(){
	return GetSize().x;
}

int GLPane::getHeight(){
	return GetSize().y;
}

void GLPane::render(wxPaintEvent& evt){
	if(!IsShown())
		return;

	wxGLCanvas::SetCurrent(*m_context);
	wxPaintDC(this); // only to be used in paint events. use wxClientDC to paint outside the paint event

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glInit2D(0,0,getWidth(),getHeight(),251,248,244);
	glLoadIdentity();

	const unsigned int nodeRadius = 25;
	const float x = 32.0f,
	            y = 48.0f;

	//Nodes
	glColor3ub(221,221,221);
	glRectf(x-nodeRadius,y-nodeRadius,x+nodeRadius,y+nodeRadius);
	glLineWidth(2);
	glColor3ub(128,128,128);
	glLineRect(x-nodeRadius,y-nodeRadius,x+nodeRadius,y+nodeRadius);

	glFlush();
	SwapBuffers();
}
