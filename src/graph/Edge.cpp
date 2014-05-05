#include "Edge.hpp"

#include "Node.hpp"
#include "../gl.hpp"

namespace GraphStructure{
	Edge::Edge(Node& to,std::string label,float weight) : to(to),label(label),weight(weight){}
	
	void Edge::render(wxPaintEvent& event,const Node& from)const{
		//Line
		glLineWidth(1);
		glColor3ub(170,170,170);

		glBegin(GL_LINES);
			glVertex2f(from.pos.x,from.pos.y);
			glVertex2f(to.pos.x,to.pos.y);
		glEnd();
	}
}
