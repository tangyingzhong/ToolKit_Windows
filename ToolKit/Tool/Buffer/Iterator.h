///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>V1.0.0</version>
/// <describe>
/// Iterator structure which just like a pointer
///</describe>
/// <date>2019/3/6</date>
///***********************************************************************
#ifndef ITERATOR_H
#define ITERATOR_H

#include "Tool/Common/SystemType.h"

namespace System
{
	namespace Buffer
	{
		template<class T>
		class Iterator
		{
		public:
			typedef System::None None;
			typedef System::Boolean BOOL;
			typedef System::Int32 Length;
			typedef System::Int32 Index;

			typedef T ValueType;
			typedef ValueType& Reference;
			typedef ValueType* Pointer;
			
		public:
			// Construct the Iterator
			Iterator() :m_Disposed(false)
			{
				this->Initialize();
			}

			// Detructe the Iterator
			~Iterator() 
			{
				this->Destory();
			}

			// Allow the object copying
			Iterator(const Iterator& other)
			{
				
			}

			// Allow the obejct assignment
			Iterator& operator=(const Iterator& other)
			{
				if (this != &other)
				{


				}

				return *this;
			}

		public:
			// Override the * 

			// Override the ++

			// Override the ++ (int)

			// Override the --

			// Override the -- (int)

			// Override the ->

			// Override the =

			// Override the ==

			// Override the !=

		private:
			// Init the list
			None Initialize()
			{
				
			}

			// Destory the list
			None Destory()
			{
				if (!this->GetDisposed())
				{
					this->SetDisposed(true);

				
				}
			}

		
		private:
			// Get the data pointer
			inline Pointer GetPointer() const
			{
				return m_Pointer;
			}

			// Set the data pointer
			inline None SetPointer(Pointer pPointer)
			{
				this->m_Pointer = pPointer;
			}

			// Get the disposed status
			inline BOOL GetDisposed() const
			{
				return m_Disposed;
			}

			// Set the disposed status
			inline None SetDisposed(BOOL bDisposed)
			{
				this->m_Disposed = bDisposed;
			}

		private:
			// Data pointer
			Pointer m_Pointer;

			// Disposed status
			BOOL m_Disposed;
		};
	}
}

#endif // ITERATOR_H