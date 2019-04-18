///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>V1.0.0</version>
/// <describe>
/// You can use it like a common array
///</describe>
/// <date>2019/3/2</date>
///***********************************************************************
#ifndef ARRAY_H
#define ARRAY_H

#include "Tool\Common\SystemType.h"

namespace System
{
	namespace Buffer
	{
		///*********************************************************
		/// <class>Array<T></class>
		/// <summary>
		/// We can use it like an array,so that we do not need
		/// to notice the array's memory management
		/// </summary>
		/// <version>V1.0.0 </version>
		/// <goup> C++ </group>
		/// <author>tangyingzhong</author>
		/// <contact>tangyz114987@outlook.com</contact>
		///**********************************************************/
		template<class T>
		class Array
		{
		public:
			typedef System::Empty Empty;
			typedef System::Object Object;
			typedef System::Boolean BOOL;
			typedef System::Int32 ArraySize;
			typedef System::Int32 Index;
			typedef System::Int32 Offset;
			typedef T ValueType;
			typedef ValueType* Pointer;
			typedef ValueType& Reference;

		public:
			// Construct the Array with size
			Array(ArraySize iArraySize = 0) :m_ArraySize(iArraySize), m_Pos(0), m_Disposed(false)
			{
				Initialize();
			}

			// Detructe the Array
			~Array()
			{
				Destory();
			}

			// Allow the object's copy behavior
			Array(const Array<T>& other)
			{
				this->DestoryBuffer();
				this->SetArraySize(other.GetArraySize());
				this->SetPos(other.GetPos());
				this->SetDisposed(other.GetDisposed());
				this->CreateBuffer(this->GetArraySize());
				if (this->GetElementPointer())
				{
					Array::Copy(other.GetElementPointer(), 0, this->GetElementPointer(), 0, this->GetArraySize());
				}
			}

			// Allow the object's assignment behavior
			Array<T>& operator=(const Array<T>& other)
			{
				if (this != &other)
				{
					this->DestoryBuffer();
					this->SetArraySize(other.GetArraySize());
					this->SetPos(other.GetPos());
					this->SetDisposed(other.GetDisposed());
					this->CreateBuffer(this->GetArraySize());
					if (this->GetElementPointer())
					{
						Array::Copy(other.GetElementPointer(), other.GetArraySize(), this->GetElementPointer(), this->GetArraySize());
					}
				}

				return *this;
			}

		public:
			// Override the data type
			operator Pointer()
			{
				return this->Data();
			}

			// Get the element by index
			Reference operator[](Index iIndex)
			{
				return At(iIndex);
			}

			// Resize the array
			Empty Resize(ArraySize iNewSize)
			{
				assert(iNewSize > 0);
				assert(iNewSize != this->GetArraySize());

				if (iNewSize < 0 || iNewSize == this->GetArraySize())
				{
					MessageBox(NULL, _T("Irlegal new size,please input a new size not equal to the current one or 0"), _T("Error"), 0);

					return;
				}

				// Deep copy buffer
				this->DeepCopyBuffer(iNewSize);

				// Update the array size
				this->SetArraySize(iNewSize);

				// Update the buffer pos
				this->SetPos(0);
			}

			// Make the array can be used as *(p+1)
			Array<T>& operator+(Index iIndex)
			{
				assert(iIndex >= 0);
				assert(iIndex < this->GetArraySize());

				if (iIndex < 0 || iIndex >= this->GetArraySize())
				{
					MessageBox(NULL, _T("Irlegal input index,you must input a correct index in array's size range."), _T("Error"), 0);

					return *this;
				}

				this->SetPos(iIndex);

				return *this;
			}

			// Get the value of current pos
			Reference operator*()
			{
				return At(this->GetPos());
			}

			// Swap two array
			Empty Swap(Array<T>& other)
			{
				Array<T> tempArray;

				tempArray = other;
				other = *this;
				*this = tempArray;
			}

			// Array's size
			ArraySize Size()
			{
				return this->GetArraySize();
			}

			// Clear the Array
			Empty Clear()
			{
				Array<T>().Swap(this);
			}

		public:
			//Copy the array. Notice: you must ensure that your dest array has enough space for the source size
			static Empty Copy(Array<ValueType>& SourceArray, Array<ValueType>& DestArray)
			{
				DestArray = SourceArray;
			}

			//Copy the array. Notice: you must ensure that your dest array has enough space for the source size
			static Empty Copy(Pointer pSourceArray, ArraySize iSourceSize, Pointer pDestArray, ArraySize iDestSize)
			{
				assert(pSourceArray != NULL);
				assert(pDestArray != NULL);
				assert(iDestSize >= iSourceSize);

				if (pSourceArray == NULL || pDestArray == NULL || iDestSize < iSourceSize)
				{
					return;
				}

				::memcpy_s(pDestArray, iDestSize, pSourceArray, iSourceSize);
			}

			// Clear the array. Notice: you must input legal start position and count of element
			static Empty Clear(Pointer pArray, Index iStartIndex, ArraySize iCount)
			{
				assert(pArray != NULL);
				assert(iStartIndex >= 0);
				assert(iCount >= 0);

				if (iStartIndex < 0 || iCount <= 0 || pArray == NULL)
				{
					return;
				}

				memset(pArray + iStartIndex, 0, sizeof(ValueType)*(iCount));
			}

			// Clear the array. Notice: you must input legal start position and count of element
			static Empty Clear(Array<ValueType>& Arr, Index iStartIndex, ArraySize iCount)
			{
				assert(Arr.Data() != NULL);
				assert(iStartIndex >= 0);
				assert(iCount >= 0);

				if (iStartIndex < 0 || iCount <= 0 || Arr.Data() == NULL)
				{
					return;
				}

				memset(Arr.Data() + iStartIndex, 0, sizeof(ValueType)*(iCount));
			}

		private:
			// Initialize the array
			Empty Initialize()
			{
				// Create a buffer
				this->CreateBuffer(this->GetArraySize());
			}

			// Destorty the array
			Empty Destory()
			{
				if (!this->GetDisposed())
				{
					this->SetDisposed(true);
					//Destory the buffer
					DestoryBuffer();
				}
			}

			// Create buffer
			Empty CreateBuffer(ArraySize iArraySize)
			{
				if (iArraySize == 0)
				{
					return;
				}

				this->SetElementPointer(new ValueType[iArraySize]);

				assert(this->GetElementPointer() != NULL);

				Array::Clear(this->GetElementPointer(), 0, iArraySize);
			}

			// Destory the buffer
			Empty DestoryBuffer()
			{
				if (this->GetElementPointer())
				{
					delete[] this->GetElementPointer();
					this->SetElementPointer(NULL);
				}
			}

			// Backup the current buffer
			Pointer Backup()
			{
				return this->GetElementPointer();
			}

			// Deep copy buffer
			Empty DeepCopyBuffer(ArraySize iNewSize)
			{
				// Backup the current buffer
				Pointer pPrevious = this->Backup();

				// Create a new buffer with the new size
				this->CreateBuffer(iNewSize);

				// Get the copy size
				ArraySize iCopySize = (iNewSize < this->GetArraySize() ? iNewSize : this->GetArraySize());

				// Copy prevoius buffer to the new buffer with the copy size
				Array::Copy(pPrevious, iCopySize, this->GetElementPointer(), iNewSize);

				// Destory the previous buffer
				delete[] pPrevious;
				pPrevious = NULL;
			}

			// Get the element by index
			Reference At(Index iIndex)
			{
				assert(iIndex >= 0);
				assert(iIndex < this->GetArraySize());

				if (iIndex < 0 || iIndex >= this->GetArraySize() || this->GetElementPointer() == NULL)
				{
					MessageBox(NULL, _T("Irlegal input index,you must input a correct index in array's size range."), _T("Error"), 0);

					return this->m_EmptyValue;
				}

				return this->GetElementPointer()[iIndex];
			}

			// Get the array pointer
			Pointer Data()
			{
				assert(this->GetElementPointer() != NULL);
				assert(this->GetArraySize() != 0);

				if (this->GetElementPointer() == NULL || this->GetArraySize() == 0)
				{
					MessageBox(NULL, _T("There is no data in the array,this is an irlegal array"), _T("Error"), 0);

					return NULL;
				}

				return this->GetElementPointer();
			}

		private:
			// Get element pointer
			inline Pointer GetElementPointer() const
			{
				return m_ElementPointer;
			}

			// Set element pointer
			inline Empty SetElementPointer(Pointer pElementPointer)
			{
				this->m_ElementPointer = pElementPointer;
			}

			// Get array size
			inline ArraySize GetArraySize() const
			{
				return m_ArraySize;
			}

			// Set array size
			inline Empty SetArraySize(ArraySize m_ArraySize)
			{
				this->m_ArraySize = m_ArraySize;
			}

			// Get the element's position
			inline Offset GetPos() const
			{
				return m_Pos;
			}

			// Set the element's position
			inline Empty SetPos(Offset m_Pos)
			{
				this->m_Pos = m_Pos;
			}

			//Get the Disposed status
			inline BOOL GetDisposed() const
			{
				return m_Disposed;
			}

			//Set the Disposed status
			inline Empty SetDisposed(BOOL bDisposed)
			{
				this->m_Disposed = bDisposed;
			}

		private:
			// Element's pointer
			Pointer m_ElementPointer;

			// Array's size
			ArraySize m_ArraySize;

			// Position of the pointer
			Offset m_Pos;

			// Error value data
			ValueType m_EmptyValue;

			// Disposed status 
			BOOL m_Disposed;
		};
	}
}

#endif //ARRAY_H_