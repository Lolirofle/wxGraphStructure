#include "WindowViews.hpp"

namespace GraphStructure{
	wxWindow* WindowViewContainer::getView(WindowViews viewId)const{
		return views[static_cast<unsigned int>(viewId)];
	}

	void WindowViewContainer::setView(WindowViews viewId,wxWindow* window){
		views[static_cast<unsigned int>(viewId)] = window;
	}
}
