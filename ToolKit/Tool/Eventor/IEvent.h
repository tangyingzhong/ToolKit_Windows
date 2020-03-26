///************************************************************************
/// <copyrigth>Voice AI Technology Of ShenZhen</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>yingzhong@voiceaitech.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Event interface for base event operation
///</describe>
/// <date>2019/12/10</date>
///***********************************************************************
#ifndef IEVENT_H
#define IEVENT_H

#include "EventHandler/EventArgs.h"
#include "EventHandler/IEventHandler.h"

class IEvent
{
public:
	typedef IEventHandler::HandlerFunc HandlerFunc;

public:
	// Virtual destruct the eventor
	virtual ~IEvent(){	}

	// Listen plugins
	virtual Empty Listen(Object pListener,
		HandlerFunc pListenHandler,
		Int32 iEventID) = 0;
};

#endif // IEVENT_H
