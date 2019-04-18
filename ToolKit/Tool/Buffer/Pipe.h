///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>V1.0.0</version>
/// <describe>
/// Pipe ,which can load any data and it has no border.
///</describe>
/// <date>2019/3/6</date>
///***********************************************************************
#ifndef PIPE_H
#define PIPE_H

#include "Tool\Common\SystemType.h"

namespace System
{
	namespace Buffer
	{
		///*********************************************************
		/// <class> Pipe<T> </class>
		/// <summary>
		/// It has no border so you have to pay attention to the size of it
		/// </summary>
		/// <version>V1.0.0 </version>
		/// <goup> C++ </group>
		/// <author>tangyingzhong</author>
		/// <contact>tangyz114987@outlook.com</contact>
		///**********************************************************/
		template<class T>
		class Pipe
		{
		public:
			typedef System::Empty Empty;
			typedef System::Boolean BOOL;
			typedef System::Int32 PipeSize;
			typedef T ValueType;
			typedef ValueType& Reference;
			typedef ValueType* Pointer;
			typedef std::queue<ValueType> DataQueue;

		public:
			// Construct the pipe
			Pipe() {	}

			// Detructe the Pipe
			~Pipe() {	}

		private:
			// Forbid the object copying
			Pipe(const Pipe& other) {	}

			// Forbid the obejct assignment
			Pipe& operator=(const Pipe& other) {	}

		public:
			// Read the data 
			BOOL Read(Reference data)
			{
				BOOL bSuccess = false;

				if (!m_DataQueue.empty())
				{
					ValueType value = m_DataQueue.front();

					m_DataQueue.pop();

					data = value;

					bSuccess = true;

					return bSuccess;
				}

				return bSuccess;
			}

			// Write the data to the pipe
			Empty Write(ValueType data)
			{
				m_DataQueue.push(data);
			}

			// Clear the pipe
			Empty Clear()
			{
				DataQueue().swap(this->m_DataQueue);
			}

			// Get pipe size
			PipeSize Size()
			{
				return m_DataQueue.size();
			}

			// Swap two pipes
			Empty Swap(Pipe& pipe)
			{
				m_DataQueue.swap(pipe.m_DataQueue);
			}

		private:
			// Data queue
			DataQueue m_DataQueue;
		};
	}
}

#endif //PIPE_H_