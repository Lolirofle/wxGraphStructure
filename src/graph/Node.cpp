#include "Node.hpp"

#include "Edge.hpp"
#include "../gl.hpp"

namespace GraphStructure{
	Node::Node(wxPoint pos,std::string label) : pos(pos),label(label),radius(25){}

	void Node::render(wxPaintEvent& event,bool selected)const{
		//Fill
		if(selected)
			glColor3ub(221,204,187);
		else
			glColor3ub(221,221,221);
		glCircle(pos.x,pos.y,radius,radius,true);
		
		//Outline
		glLineWidth(2);
		if(selected)
			glColor3ub(221,136,136);
		else
			glColor3ub(128,128,128);
		glCircle(pos.x,pos.y,radius,radius,false);
	}
}
