#include "Node.hpp"

#include "gl.hpp"

namespace GraphStructure{
	Node::Node(float x,float y,std::string label) : x(x),y(y),label(label){}

	void Node::render(wxPaintEvent& event){
		const unsigned int nodeRadius = 25;

		glColor3ub(221,221,221);
		glCircle(x,y,nodeRadius,nodeRadius/1.5,true);
		glLineWidth(2);
		glColor3ub(128,128,128);
		glCircle(x,y,nodeRadius,nodeRadius/1.5,false);
	}
}
