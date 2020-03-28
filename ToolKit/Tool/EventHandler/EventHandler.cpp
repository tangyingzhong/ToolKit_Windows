#include "EventHandler.h"

// Construct the event handler
EventHandler::EventHandler():m_bDisposed(false)
{
    Initialize();
}

// Destruct the event handler
EventHandler::~EventHandler()
{
    Destory();
}

// Initialize the event handler
None EventHandler::Initialize()
{
	ClearTable();
}

// Destory the event handler
None EventHandler::Destory()
{
    if(!GetDisposed())
    {
        SetDisposed(true);

		ClearTable();
    }
}

// Clear the map table
None EventHandler::ClearTable()
{
	EventMapTable().swap(m_EventMapTable);
}

// Fire event
None EventHandler::FireEvent(Object pSender, Int32 iEventID,EventArgs* pArgs)
{
    if(pSender==nullptr)
    {
        return;
    }

    if(pArgs==nullptr)
    {
        return;
    }

    if(m_EventMapTable.empty())
    {
        return;
    }

    for(EventMapTable::iterator EventIter=m_EventMapTable.begin();
        EventIter!=m_EventMapTable.end();
        ++EventIter)
    {
        Object pReceiver=EventIter->first;

        IDFuncMapTable IdFuncTable=m_EventMapTable[pReceiver];

        if(IdFuncTable.find(iEventID)!=IdFuncTable.end())
        {
            HandlerFuncTable FuncTable=IdFuncTable[iEventID];

            for(HandlerFuncTable::iterator FuncIter=FuncTable.begin();
                FuncIter!=FuncTable.end();
                ++FuncIter)
            {
                EventPara Paramenter;

                Paramenter.pSender=pSender;

                Paramenter.pReceiver=pReceiver;

                Paramenter.iEventID=iEventID;

                Paramenter.pArgs=pArgs;

                (*FuncIter)(Paramenter);
            }
        }
    }
}

// Register an object's callback to the event handler
Boolean EventHandler::RegisterEvent(Object pReceiver, Int32 iEventID,HandlerFunc pHandlerFunc)
{
    if(pReceiver==nullptr)
    {
        return false;
    }

    if(pHandlerFunc==nullptr)
    {
        return false;
    }

   if(m_EventMapTable.find(pReceiver)!=m_EventMapTable.end())
   {
         IDFuncMapTable IdFuncTable=m_EventMapTable[pReceiver];

         if(IdFuncTable.find(iEventID)!=IdFuncTable.end())
         {
             HandlerFuncTable FuncTable=IdFuncTable[iEventID];

             for(HandlerFuncTable::iterator FuncIter=FuncTable.begin();
                 FuncIter!=FuncTable.end();
                 ++FuncIter)
             {
                if(pHandlerFunc==*FuncIter)
                {
                    return false;
                }
             }

             // Add to the func table
             FuncTable.push_back(pHandlerFunc);

             IdFuncTable[iEventID]=FuncTable;

             m_EventMapTable[pReceiver]=IdFuncTable;
         }
         else
         {
             // Add to the id-func map table
             HandlerFuncTable FuncTable;

             FuncTable.push_back(pHandlerFunc);

             IdFuncTable.insert(make_pair(iEventID,FuncTable));

             m_EventMapTable[pReceiver]=IdFuncTable;
         }
   }
   else
   {
        HandlerFuncTable FuncTable;

        FuncTable.push_back(pHandlerFunc);

        IDFuncMapTable IdFuncTable;

        IdFuncTable.insert(make_pair(iEventID,FuncTable));

         m_EventMapTable.insert(make_pair(pReceiver,IdFuncTable));
   }

   return true;
}

// UnRegister receiver
Boolean EventHandler::UnRegisterEvent(Object pReceiver)
{
    if(pReceiver==nullptr)
    {
        return false;
    }

    if(m_EventMapTable.empty())
    {
        return false;
    }

   if(m_EventMapTable.find(pReceiver)!=m_EventMapTable.end())
   {
        m_EventMapTable.erase(pReceiver);

        return true;
   }

   return false;
}

// UnRegister receiver
Boolean EventHandler::UnRegisterEvent(Object pReceiver, Int32 iEventID)
{
    if(pReceiver==nullptr)
    {
        return false;
    }

    if(m_EventMapTable.empty())
    {
        return false;
    }

   if(m_EventMapTable.find(pReceiver)!=m_EventMapTable.end())
   {
       IDFuncMapTable IdFuncTable=m_EventMapTable[pReceiver];

       if(IdFuncTable.find(iEventID)!=IdFuncTable.end())
       {
           IdFuncTable.erase(iEventID);

           m_EventMapTable[pReceiver]=IdFuncTable;

           return true;
       }
   }

   return false;
}

// UnRegister an object's callback from the event handler
Boolean EventHandler::UnRegisterEvent(Object pReceiver, Int32 iEventID,HandlerFunc pHandlerFunc)
{
    if(pReceiver==nullptr)
    {
        return false;
    }

    if(pHandlerFunc==nullptr)
    {
        return false;
    }

    if(m_EventMapTable.empty())
    {
        return false;
    }

   if(m_EventMapTable.find(pReceiver)!=m_EventMapTable.end())
   {
       IDFuncMapTable IdFuncTable=m_EventMapTable[pReceiver];

       if(IdFuncTable.find(iEventID)!=IdFuncTable.end())
       {
          HandlerFuncTable FuncTable=IdFuncTable[iEventID];

          for(HandlerFuncTable::iterator FuncIter=FuncTable.begin();
              FuncIter!=FuncTable.end();)
          {
             if(pHandlerFunc==*FuncIter)
             {
                 FuncIter=FuncTable.erase(FuncIter);

                 IdFuncTable[iEventID]=FuncTable;

                 m_EventMapTable[pReceiver]=IdFuncTable;

                 return true;
             }
             else
             {
                 ++FuncIter;
             }
          }
       }
   }

   return false;
}

// UnRegister all eventids
Boolean EventHandler::UnRegisterEvent(Int32 iEventID)
{
    if(m_EventMapTable.empty())
    {
        return false;
    }

    for(EventMapTable::iterator EventIter=m_EventMapTable.begin();
        EventIter!=m_EventMapTable.end();
        ++EventIter)
    {
        IDFuncMapTable IdFuncTable=m_EventMapTable[EventIter->first];

        if(IdFuncTable.find(iEventID)!=IdFuncTable.end())
        {
            IdFuncTable.erase(iEventID);
        }
    }

    return true;
}

// UnRegister all eventid's func
Boolean EventHandler::UnRegisterEvent(Int32 iEventID,HandlerFunc pHandlerFunc)
{
    if(pHandlerFunc==nullptr)
    {
        return false;
    }

    if(m_EventMapTable.empty())
    {
        return false;
    }

    for(EventMapTable::iterator EventIter=m_EventMapTable.begin();
        EventIter!=m_EventMapTable.end();
        ++EventIter)
    {
        Object pReceiver=EventIter->first;

        IDFuncMapTable IdFuncTable=m_EventMapTable[pReceiver];

        if(IdFuncTable.find(iEventID)!=IdFuncTable.end())
        {
            HandlerFuncTable FuncTable=IdFuncTable[iEventID];

            for(HandlerFuncTable::iterator FuncIter=FuncTable.begin();
                FuncIter!=FuncTable.end();)
            {
               if(pHandlerFunc==*FuncIter)
               {
                   FuncIter=FuncTable.erase(FuncIter);

                   IdFuncTable[iEventID]=FuncTable;

                   m_EventMapTable[pReceiver]=IdFuncTable;
               }
            }
        }
    }

    return true;
}

// UnRegister all funcs
Boolean EventHandler::UnRegisterEvent(HandlerFunc pHandlerFunc)
{
    if(pHandlerFunc==nullptr)
    {
        return false;
    }

    if(m_EventMapTable.empty())
    {
        return false;
    }

    for(EventMapTable::iterator EventIter=m_EventMapTable.begin();
        EventIter!=m_EventMapTable.end();
        ++EventIter)
    {
        Object pReceiver=EventIter->first;

        IDFuncMapTable IdFuncTable=m_EventMapTable[pReceiver];

        for(IDFuncMapTable::iterator IDFuncIter=IdFuncTable.begin();
            IDFuncIter!=IdFuncTable.end();
            ++IDFuncIter)
        {
            int iEventID=IDFuncIter->first;

            HandlerFuncTable FuncTable=IdFuncTable[iEventID];

            for(HandlerFuncTable::iterator FuncIter=FuncTable.begin();
                FuncIter!=FuncTable.end();)
            {
               if(pHandlerFunc==*FuncIter)
               {
                   FuncIter=FuncTable.erase(FuncIter);

                   IdFuncTable[iEventID]=FuncTable;

                   m_EventMapTable[pReceiver]=IdFuncTable;
               }
            }
        }
    }

    return true;
}
