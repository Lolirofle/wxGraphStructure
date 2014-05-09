#include "Edge.hpp"

#include "Node.hpp"
#include "../gl.hpp"
#include <cmath>

namespace GraphStructure{
	Edge::Edge(Node& to,std::string label,float weight,unsigned int count) : to(to),label(label),weight(weight),count(count){}
	
	void Edge::render(wxPaintEvent& event,const Node& from)const{
		//Line
		glLineWidth(1);
		glColor3ub(170,170,170);

		glBegin(GL_LINES);
			glVertex2f(from.pos.x,from.pos.y);
			glVertex2f(to.pos.x,to.pos.y);
		glEnd();

		//Head in center
		const float angle = atan2(to.pos.y-from.pos.y,to.pos.x-from.pos.x);
		const unsigned short arrowSize = 24;

		const wxPoint head(
			(to.pos.x-from.pos.x)/2 + arrowSize*cosf(angle)/2 + from.pos.x,
			(to.pos.y-from.pos.y)/2 + arrowSize*sinf(angle)/2 + from.pos.y
		);

		glColor4ub(170,170,170,128);
		glBegin(GL_TRIANGLES);
			glVertex2f(head.x,head.y);
			glVertex2f(
				head.x - arrowSize*cosf(angle - M_PI/6),
				head.y - arrowSize*sinf(angle - M_PI/6)
			);
			glVertex2f(
				head.x - arrowSize*cosf(angle + M_PI/6),
				head.y - arrowSize*sinf(angle + M_PI/6)
			);
			glVertex2f(head.x,head.y);
		glEnd();
	}
}
