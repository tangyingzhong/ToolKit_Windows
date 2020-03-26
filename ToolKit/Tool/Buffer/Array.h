///************************************************************************
/// <copyrigth>Voice AI Technology Of ShenZhen</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>yingzhong@voiceaitech.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// You can use it like a common array
///</describe>
/// <date>2019/7/16</date>
///***********************************************************************
#ifndef ARRAY_H
#define ARRAY_H

#include "Common/SystemType.h"

using namespace System;

namespace System
{
	namespace Buffer
	{
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
			Array(ArraySize iArraySize = 512) :m_ArraySize(iArraySize),
				m_ElementPosition(0), 
				m_Disposed(false)
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
				SetArraySize(other.GetArraySize());
				SetElementPos(other.GetElementPos());
				SetDisposed(other.GetDisposed());
				CreateBuffer(GetArraySize());
				if (GetElementPointer())
				{
					Array::Copy(other.GetElementPointer(), other.GetArraySize(), GetElementPointer(), GetArraySize());
				}
			}

			// Allow the object's assignment behavior
			Array<T>& operator=(const Array<T>& other)
			{
				if (this != &other)
				{
					DestoryBuffer();
					SetArraySize(other.GetArraySize());
					SetElementPos(other.GetElementPos());
					SetDisposed(other.GetDisposed());
					CreateBuffer(GetArraySize());
					if (GetElementPointer())
					{
						Array::Copy(other.GetElementPointer(), other.GetArraySize(), GetElementPointer(), GetArraySize());
					}
				}

				return *this;
			}

		public:
			// Get the array's data pointer
			Pointer Data()
			{				
				return GetElementPointer();
			}

			// Get the element by index
			Reference operator[](Index iIndex)
			{
				return At(iIndex);
			}

			// Resize the array
			Empty Resize(ArraySize iNewSize)
			{
				if (iNewSize < 0)
				{
					ERROR_MESSAGEBOX(_T("Array Error"), _T("Irlegal new size < 0"));

					return;
				}

				// Deep copy buffer
				DeepCopyBuffer(iNewSize);

				// Update the array size
				SetArraySize(iNewSize);

				// Update the buffer pos
				SetElementPos(0);
			}

			// Make the array can be used as *(p+1)
			Array<T>& operator+(Index iIndex)
			{
				if (iIndex < 0 || iIndex >= GetArraySize())
				{
					ERROR_MESSAGEBOX(_T("Array Error"),_T("Irlegal input index,you must input a correct index in array's size range."));

					return *this;
				}

				SetElementPos(iIndex);

				return *this;
			}

			// Get the value of current pos
			Reference operator*()
			{
				return At(GetElementPos());
			}

			// Swap two arrays
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
				return GetArraySize();
			}

			// Clear the Array
			Empty Clear()
			{
				Array<T>::Clear(Data(),0,Size());
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
				if (pSourceArray == NULL || pDestArray == NULL || iDestSize < iSourceSize)
				{
					ERROR_MESSAGEBOX(_T("Array error"), _T("Input or Dest array pointer is null or dest size < source size"));

					return;
				}

				::memcpy_s(pDestArray, sizeof(ValueType)*iDestSize, pSourceArray, sizeof(ValueType)*iSourceSize);
			}

			// Clear the array. Notice: you must input legal start position and count of element
			static Empty Clear(Pointer pArray, Index iStartIndex, ArraySize iCount)
			{
				if (iStartIndex < 0 || iCount < 0 || pArray == NULL)
				{
					ERROR_MESSAGEBOX(_T("Array error"), _T("Input or Dest array pointer is null or clear count <0"));

					return;
				}

				memset(pArray + iStartIndex, 0, sizeof(ValueType)*iCount);
			}

			// Clear the array. Notice: you must input legal start position and count of element
			static Empty Clear(Array<ValueType>& Arr, Index iStartIndex, ArraySize iCount)
			{
				Clear(Arr.Data(), iStartIndex, iCount);
			}

		private:
			// Initialize the array
			Empty Initialize()
			{
				// Create a buffer
				CreateBuffer(GetArraySize());
			}

			// Destorty the array
			Empty Destory()
			{
				if (!GetDisposed())
				{
					SetDisposed(true);

					// Destory the buffer
					DestoryBuffer();
				}
			}

			// Create buffer
			Empty CreateBuffer(ArraySize iArraySize)
			{
				if (iArraySize == 0)
				{
					SetElementPointer(NULL);

					return;
				}

				SetElementPointer(new ValueType[iArraySize]);

				if (GetElementPointer() == NULL)
				{
					ERROR_MESSAGEBOX(_T("Array Error"), _T("Failed to create buffer in the array!"));

					return;
				} 

				Array<ValueType>::Clear(GetElementPointer(), 0, iArraySize);
			}

			// Destory the buffer
			Empty DestoryBuffer()
			{
				if (GetElementPointer())
				{
					delete[] GetElementPointer();

					SetElementPointer(NULL);
				}
			}

			// Backup the current buffer
			Pointer Backup()
			{
				return GetElementPointer();
			}

			// Deep copy buffer
			Empty DeepCopyBuffer(ArraySize iNewSize)
			{
				// Backup the current buffer
				Pointer pPrevious = Backup();

				// Create a new buffer with the new size
				CreateBuffer(iNewSize);

				if (pPrevious != NULL)
				{
					// Get the copy size
					ArraySize iCopySize = (iNewSize < GetArraySize() ? iNewSize : GetArraySize());

					// Copy prevoius buffer to the new buffer with the copy size
					Array::Copy(pPrevious, iCopySize, GetElementPointer(), iNewSize);

					// Destory the previous buffer
					delete[] pPrevious;
					pPrevious = NULL;
				}				
			}

			// Get the element by index
			Reference At(Index iIndex)
			{
				if (iIndex < 0 || iIndex >= GetArraySize() || GetElementPointer() == NULL)
				{
					ERROR_MESSAGEBOX(_T("Array Error"), _T("Irlegal input index,you must input a correct index in array's size range."));

					return m_EmptyElement;
				}

				return GetElementPointer()[iIndex];
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
				m_ElementPointer = pElementPointer;
			}

			// Get array size
			inline ArraySize GetArraySize() const
			{
				return m_ArraySize;
			}

			// Set array size
			inline Empty SetArraySize(ArraySize iArraySize)
			{
				m_ArraySize = iArraySize;
			}

			// Get the element's position
			inline Offset GetElementPos() const
			{
				return m_ElementPosition;
			}

			// Set the element's position
			inline Empty SetElementPos(Offset iElementPosition)
			{
				m_ElementPosition = iElementPosition;
			}

			//Get the Disposed status
			inline BOOL GetDisposed() const
			{
				return m_Disposed;
			}

			//Set the Disposed status
			inline Empty SetDisposed(BOOL bDisposed)
			{
				m_Disposed = bDisposed;
			}

		private:
			// Element's pointer
			Pointer m_ElementPointer;

			// Array's size
			ArraySize m_ArraySize;

			// Position of the pointer
			Offset m_ElementPosition;

			// Empty value data
			ValueType m_EmptyElement;

			// Disposed status 
			BOOL m_Disposed;
		};
	}
}

#endif // ARRAY_H