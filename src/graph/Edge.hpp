#ifndef __LOLIROFLE_WXGRAPHSTRUCTURE_GRAPHEDGE_HPP_INCLUDED__
#define __LOLIROFLE_WXGRAPHSTRUCTURE_GRAPHEDGE_HPP_INCLUDED__

#include <string>

namespace GraphStructure{
	class Node;

	class Edge{
	protected:
		Node& to;
		std::string label;
		float weight;

	public:
		Edge(Node& to,std::string label,float weight=0.0f);

		void render(wxPaintEvent& event)const;
	};
}

#endif
