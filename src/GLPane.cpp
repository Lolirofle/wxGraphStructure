#include "GLPane.hpp"

#include "gl.hpp"

wxBEGIN_EVENT_TABLE(GLPane,wxGLCanvas)
	EVT_MOTION      (GLPane::mouseMoved)
	EVT_LEFT_DOWN   (GLPane::mouseDown)
	EVT_LEFT_UP     (GLPane::mouseReleased)
	EVT_RIGHT_DOWN  (GLPane::rightClick)
	EVT_LEAVE_WINDOW(GLPane::mouseLeftWindow)
	EVT_SIZE        (GLPane::resized)
	EVT_KEY_DOWN    (GLPane::keyPressed)
	EVT_KEY_UP      (GLPane::keyReleased)
	EVT_MOUSEWHEEL  (GLPane::mouseWheelMoved)
	EVT_PAINT       (GLPane::render)
wxEND_EVENT_TABLE()


// some useful events to use
void GLPane::mouseMoved(wxMouseEvent& event){}
void GLPane::mouseDown(wxMouseEvent& event){}
void GLPane::mouseWheelMoved(wxMouseEvent& event){}
void GLPane::mouseReleased(wxMouseEvent& event){}
void GLPane::rightClick(wxMouseEvent& event){}
void GLPane::mouseLeftWindow(wxMouseEvent& event){}
void GLPane::keyPressed(wxKeyEvent& event){}
void GLPane::keyReleased(wxKeyEvent& event){}

GLPane::GLPane(wxFrame* parent,int* args) : wxGLCanvas(parent,wxID_ANY,args,wxDefaultPosition,wxDefaultSize,wxFULL_REPAINT_ON_RESIZE){
	m_context = new wxGLContext(this);

	//Avoid flashing on M$ Windows
	SetBackgroundStyle(wxBG_STYLE_CUSTOM);
}

GLPane::~GLPane(){
	delete m_context;
}

void GLPane::resized(wxSizeEvent& evt){
//	wxGLCanvas::OnSize(evt);

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
