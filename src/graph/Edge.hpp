#ifndef __LOLIROFLE_WXGRAPHSTRUCTURE_GRAPHEDGE_HPP_INCLUDED__
#define __LOLIROFLE_WXGRAPHSTRUCTURE_GRAPHEDGE_HPP_INCLUDED__

#include <string>
#include "../wx.hpp"

namespace GraphStructure{
	class Node;

	class Edge{
	protected:
		Node& to;
		std::string label;
		float weight;
		unsigned int count;

	public:
		Edge(Node& to,std::string label="",float weight=0.0f,unsigned int count=1);

		void render(wxPaintEvent& event,const Node& from)const;
	};
}

#endif
