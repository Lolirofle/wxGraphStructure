#ifndef __LOLIROFLE_WXGRAPHSTRUCTURE_RENDERABLE_HPP_INCLUDED__
#define __LOLIROFLE_WXGRAPHSTRUCTURE_RENDERABLE_HPP_INCLUDED__

#include "wx.hpp"

class Renderable{
public:
	virtual void render(wxPaintEvent& event)=0;
};

#endif
