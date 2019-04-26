#include "Application\PreCompile.h"
#include "MessageDistributor.h"

using namespace System::Thread;

///************************************************************************
/// <summary>
/// Construct the MessageDistributor
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
MessageDistributor::MessageDistributor():m_Disposed(false)
{
	
}


///************************************************************************
/// <summary>
/// Detructe the MessageDistributor
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
MessageDistributor::~MessageDistributor()
{
	if (!GetDisposed())
	{
		SetDisposed(true);
	}
}


///************************************************************************
/// <summary>
/// Send message to the Form and attaching the data 
/// </summary>
/// <param name=ReceiverName strFormName>Target form</param>
/// <param name=MessageValue iMessageValue>Message value</param>
/// <param name=DataAttach & AttachData>Attach data</param>
/// <returns></returns>
/// <remarks>
/// None
/// </remarks>
///***********************************************************************
MessageDistributor::Empty MessageDistributor::Send(TargetFormName strFormName, MessageValue iMessageValue, DataAttach& AttachData)
{
	HWND hForm = ::FindWindow(NULL, strFormName.CStr());
	if (hForm)
	{
		::SendMessage(hForm, iMessageValue, NULL, (LPARAM)&AttachData);
	}
}


///************************************************************************
/// <summary>
/// Send the message to the specify form
/// </summary>
/// <param name=ReceiverName strFormName>Target form</param>
/// <param name=MessageValue iMessageValue>Message value</param>
/// <returns></returns>
/// <remarks>
/// None
/// </remarks>
///***********************************************************************
MessageDistributor::Empty MessageDistributor::Send(TargetFormName strFormName, MessageValue iMessageValue)
{	
	HWND hForm = ::FindWindow(NULL, strFormName.CStr());
	if (hForm)
	{
		::SendMessage(hForm, iMessageValue, NULL, NULL);
	}
}


///************************************************************************
/// <summary>
/// Post the Message to the sepcify window
/// </summary>
/// <param name=ReceiverName strFormName>Target Form</param>
/// <param name=MessageValue iMessageValue>Message value</param>
/// <param name=DataAttach & AttachData>Attach data to the form</param>
/// <returns></returns>
/// <remarks>
/// Note:the message will be stored in windows message queue
/// </remarks>
///***********************************************************************
MessageDistributor::Empty MessageDistributor::Post(TargetFormName strFormName, MessageValue iMessageValue, DataAttach& AttachData)
{
	HWND hForm = ::FindWindow(NULL, strFormName.CStr());
	if (hForm)
	{
		::PostMessage(hForm, iMessageValue, NULL, (LPARAM)&AttachData);
	}
}


///************************************************************************
/// <summary>
/// Post the Message to the sepcify window
/// </summary>
/// <param name=ReceiverName strFormName>Target Form</param>
/// <param name=MessageValue iMessageValue>Message value</param>
/// <returns></returns>
/// <remarks>
/// Note:the message will be stored in windows message queue
/// </remarks>
///***********************************************************************
MessageDistributor::Empty MessageDistributor::Post(TargetFormName strFormName, MessageValue iMessageValue)
{
	HWND hForm = ::FindWindow(NULL, strFormName.CStr());
	if (hForm)
	{
		::PostMessage(hForm, iMessageValue, NULL, NULL);
	}
}