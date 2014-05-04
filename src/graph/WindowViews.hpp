#ifndef __LOLIROFLE_WXGRAPHSTRUCTURE_GRAPH_WINDOWVIEWS_HPP_INCLUDED__
#define __LOLIROFLE_WXGRAPHSTRUCTURE_GRAPH_WINDOWVIEWS_HPP_INCLUDED__

#include <array>
#include "../wx.hpp"

namespace GraphStructure{
	enum class WindowViews : unsigned int{
		NodeVisualizer,
		Information,
		NodeProperties,

		length
	};

	class WindowViewContainer{
	public:
		std::array<wxWindow*,static_cast<unsigned int>(WindowViews::length)> views;

		wxWindow* getView(WindowViews viewId)const;

	protected:
		void setView(WindowViews viewId,wxWindow* window);
	};
}

#endif
