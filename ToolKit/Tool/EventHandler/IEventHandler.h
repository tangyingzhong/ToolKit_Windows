#ifndef IEVENTHANDLER_H
#define IEVENTHANDLER_H

#include "Common/SystemType.h"
#include "EventHandler/EventArgs.h"

using namespace std;
using namespace System;
using namespace System::EventArgument;

struct EventPara
{
    // Sender
    Object pSender;

    // Receiver
    Object pReceiver;

    // Event id
    Int32 iEventID;

    // Event args
    EventArgs* pArgs;

    EventPara()
    {
        pSender=nullptr;
        pReceiver=nullptr;
        iEventID=-1;
        pArgs=nullptr;
    }

    Boolean IsEmpty()
    {
        return (pSender==nullptr)
                && (pReceiver==nullptr)
                && (iEventID==-1)
                && (pArgs==nullptr);
    }
};

class IEventHandler
{
public:
    typedef Empty(*HandlerFunc)(EventPara& EventParamenter);

public:
    // Destruct the event handler
    virtual ~IEventHandler(){    }

public:
    // Fire event
    virtual Empty FireEvent(Object pSender,Int32 iEventID,EventArgs* pArgs)=0;

    // Register an object's callback to the event handler
    virtual Boolean RegisterEvent(Object pReceiver, Int32 iEventID,HandlerFunc pHandlerFunc)=0;

    // UnRegister receiver
    virtual Boolean UnRegisterEvent(Object pReceiver)=0;

    // UnRegister receiver
    virtual Boolean UnRegisterEvent(Object pReceiver, Int32 iEventID)=0;

    // UnRegister an object's callback from the event handler
    virtual Boolean UnRegisterEvent(Object pReceiver, Int32 iEventID,HandlerFunc pHandlerFunc)=0;

    // UnRegister all eventids
    virtual Boolean UnRegisterEvent(Int32 iEventID)=0;

    // UnRegister all eventid's func
    virtual Boolean UnRegisterEvent(Int32 iEventID,HandlerFunc pHandlerFunc)=0;

    // UnRegister all funcs
    virtual Boolean UnRegisterEvent(HandlerFunc pHandlerFunc)=0;
};

#endif //EVENTHANDLER_H
