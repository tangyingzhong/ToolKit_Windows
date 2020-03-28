#include "MessageDistributor.h"

using namespace System::Thread;

// Construct the MessageDistributor
MessageDistributor::MessageDistributor():m_Disposed(false)
{
	
}

// Detructe the MessageDistributor
MessageDistributor::~MessageDistributor()
{
	if (!GetDisposed())
	{
		SetDisposed(true);
	}
}

// Send message to the Form and attaching the data 
MessageDistributor::None MessageDistributor::Send(TargetFormName strFormName, MessageValue iMessageValue, DataAttach& AttachData)
{
	HWND hForm = ::FindWindow(NULL, strFormName.CStr());
	if (hForm)
	{
		::SendMessage(hForm, iMessageValue, NULL, (LPARAM)&AttachData);
	}
}

// Send the message to the specify form
MessageDistributor::None MessageDistributor::Send(TargetFormName strFormName, MessageValue iMessageValue)
{	
	HWND hForm = ::FindWindow(NULL, strFormName.CStr());
	if (hForm)
	{
		::SendMessage(hForm, iMessageValue, NULL, NULL);
	}
}

// Post the Message to the sepcify window
MessageDistributor::None MessageDistributor::Post(TargetFormName strFormName, MessageValue iMessageValue, DataAttach& AttachData)
{
	HWND hForm = ::FindWindow(NULL, strFormName.CStr());
	if (hForm)
	{
		::PostMessage(hForm, iMessageValue, NULL, (LPARAM)&AttachData);
	}
}

// Post the Message to the sepcify window
MessageDistributor::None MessageDistributor::Post(TargetFormName strFormName, MessageValue iMessageValue)
{
	HWND hForm = ::FindWindow(NULL, strFormName.CStr());
	if (hForm)
	{
		::PostMessage(hForm, iMessageValue, NULL, NULL);
	}
}