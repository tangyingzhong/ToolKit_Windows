///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>V1.0.0</version>
/// <describe>
/// FIFO data structure.you can only read the first element and wirte to the end
///</describe>
/// <date>2019/3/6</date>
///***********************************************************************
#ifndef QUEUE_H
#define QUEUE_H

#include "Tool/Common/SystemType.h"

namespace System
{
	namespace Buffer
	{
		template<class T>
		class Queue
		{
		public:
			typedef System::None None;
			typedef System::Boolean BOOL;
			typedef System::Int32 QueueSize;			
			typedef T ValueType;
			typedef ValueType& Reference;
			typedef ValueType* Pointer;
		
		public:
			// Construct the Queue
			Queue() {	}

			// Detructe the Queue
			~Queue() {	}

		private:
			// Forbid the object copying
			Queue(const Queue& other) {	}

			// Forbid the obejct assignment
			Queue& operator=(const Queue& other) {	}

		public:
			// Pop the data 
			BOOL Pop(Reference data)
			{
				BOOL bSuccess = false;

				if (!m_DataQueue.IsEmpty())
				{
					ValueType value = m_DataQueue.front();

					m_DataQueue.pop();

					data = value;

					bSuccess = true;

					return bSuccess;
				}

				return bSuccess;
			}

			// Push the data to the Queue
			None Push(ValueType data)
			{
				m_DataQueue.push(data);
			}

			// Clear the Queue
			None Clear()
			{
				DataQueue().swap(this->m_DataQueue);
			}

			// Get Queue size
			QueueSize Size()
			{
				return m_DataQueue.size();
			}

			// Swap two Queues
			None Swap(Queue& Queue)
			{
				m_DataQueue.swap(Queue.m_DataQueue);
			}

		private:
			// Data pointer

			

		};
	}
}

#endif // QUEUE_H