#ifndef __LOLIROFLE_WXGRAPHSTRUCTURE_VIEWMENUEVENT_HPP_INCLUDED__
#define __LOLIROFLE_WXGRAPHSTRUCTURE_VIEWMENUEVENT_HPP_INCLUDED__

#include "wx.hpp"

//https://code.google.com/p/freetype-gl/
//http://wiki.wxwidgets.org/Custom_Events
//http://wiki.wxwidgets.org/Custom_Events_Tutorial
class ViewMenuEvent : public wxMenuEvent{
public:
	ViewMenuEvent(wxEventType type=wxEVT_NULL,int id=0,wxMenu *menu=NULL));
	~ViewMenuEvent();
	
};

#endif
