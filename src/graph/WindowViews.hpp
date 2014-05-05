#ifndef __LOLIROFLE_WXGRAPHSTRUCTURE_GRAPH_WINDOWVIEWS_HPP_INCLUDED__
#define __LOLIROFLE_WXGRAPHSTRUCTURE_GRAPH_WINDOWVIEWS_HPP_INCLUDED__

#include <array>
#include "../wx.hpp"

namespace GraphStructure{
	class NodeVisualizer;
	class NodeProperties;

	namespace WindowViews{enum{
		NodeVisualizer,
		NodeProperties,
		Information,

		length
	};}

	union WindowViewContainer{
		wxWindow* views[WindowViews::length];
		struct{
			//TODO: Fix extensibility
			NodeVisualizer* nodeVisualizer;
			NodeProperties* nodeProperties;
			wxWindow* information;
		};
	};
}

#endif
