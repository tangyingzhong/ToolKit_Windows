///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>V1.0.0</version>
/// <describe>
/// Distribute the Messages to the windows kernel
///</describe>
/// <date>2019/3/6</date>
///***********************************************************************
#ifndef MESSAGEDISTRIBUTOR_H
#define MESSAGEDISTRIBUTOR_H

#include "Tool\BaseType\String.h"

using namespace System::BasicType;

namespace System
{
	namespace Thread
	{
		class MessageDistributor
		{
		public:
			typedef System::Empty Empty;
			typedef System::Boolean BOOL;
			typedef System::Int32 MessageValue;
			typedef String TargetFormName;
			typedef COPYDATASTRUCT DataAttach;

		public:
			// Construct the MessageDistributor
			MessageDistributor();

			// Detructe the MessageDistributor
			~MessageDistributor();

		private:
			// Forbid the object copying
			MessageDistributor(const MessageDistributor& other) {	}

			// Forbid the obejct assignment
			MessageDistributor& operator=(const MessageDistributor& other) {	}

		public:
			// Send the Message to the sepcify window
			Empty Send(TargetFormName strFormName, MessageValue iMessageValue, DataAttach& AttachData);

			// Send the Messageto the sepcify window
			Empty Send(TargetFormName strFormName, MessageValue iMessageValue);

			// Post the Message to the sepcify window(the message will be stored in windows message queue)
			Empty Post(TargetFormName strFormName, MessageValue iMessageValue, DataAttach& AttachData);

			// Post the Messageto the sepcify window(the message will be stored in windows message queue)
			Empty Post(TargetFormName strFormName, MessageValue iMessageValue);

		private:
			// Get the disposed
			inline BOOL GetDisposed() const
			{
				return m_Disposed;
			}

			// Set the disposed	
			inline Empty SetDisposed(BOOL bDisposed)
			{
				this->m_Disposed = bDisposed;
			}

		private:
			// Disposed status
			BOOL m_Disposed;
		};
	}
}

#endif // MESSAGEDISTRIBUTOR_H