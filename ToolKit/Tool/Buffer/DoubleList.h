///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>V1.0.0</version>
/// <describe>
/// DoubleList structure which is designed by principle ,FIFO
///</describe>
/// <date>2019/3/6</date>
///***********************************************************************
#ifndef DOUBLELIST_H
#define DOUBLELIST_H

#include "Tool\Common\SystemType.h"

namespace System
{
	namespace Buffer
	{
		///*********************************************************
		/// <class> DoubleList<T> </class>
		/// <summary>
		/// FIFO data structure.you can only read the first element and wirte to the end
		/// </summary>
		/// <version>V1.0.0 </version>
		/// <goup> C++ </group>
		/// <author>tangyingzhong</author>
		/// <contact>tangyz114987@outlook.com</contact>
		///**********************************************************/
		template<class T>
		class DoubleList
		{
		public:
			typedef System::Empty Empty;
			typedef System::Boolean BOOL;
			typedef System::Int32 ListSize;			
			typedef T ValueType;
			typedef ValueType& Reference;
			typedef ValueType* Pointer;
		
		public:
			// Construct the DoubleList
			DoubleList() {	}

			// Detructe the DoubleList
			~DoubleList() {	}

		private:
			// Forbid the object copying
			DoubleList(const DoubleList& other) {	}

			// Forbid the obejct assignment
			DoubleList& operator=(const DoubleList& other) {	}

		public:
			// Pop the data 
			BOOL Pop(Reference data)
			{
				BOOL bSuccess = false;

				if (!m_DataDoubleList.empty())
				{
					ValueType value = m_DataDoubleList.front();

					m_DataDoubleList.pop();

					data = value;

					bSuccess = true;

					return bSuccess;
				}

				return bSuccess;
			}

			// Push the data to the DoubleList
			Empty Push(ValueType data)
			{
				m_DataDoubleList.push(data);
			}

			// Clear the DoubleList
			Empty Clear()
			{
				DataDoubleList().swap(this->m_DataDoubleList);
			}

			// Get DoubleList size
			ListSize Size()
			{
				return m_DataDoubleList.size();
			}

			// Swap two DoubleLists
			Empty Swap(DoubleList& DoubleList)
			{
				m_DataDoubleList.swap(DoubleList.m_DataDoubleList);
			}

		private:
			// Data pointer

			

		};
	}
}

#endif //DoubleList_H_