///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// It can be used betwwen producer and customer as a common cache
///</describe>
/// <date>2019/7/16</date>
///***********************************************************************
#ifndef CIRCLEBUFFER_H
#define CIRCLEBUFFER_H

#include "Tool/Common/SystemType.h"
#include "Array.h"

namespace System
{
	namespace Buffer
	{
		template <class T>
		class CircleBuffer
		{
		public:
			typedef System::None None;
			typedef System::Boolean BOOL;
			typedef System::Object Object;
			typedef System::Byte Byte;
			typedef System::ByteArray ByteArray;
			typedef System::UInt32 Length;
			typedef System::UInt32 Index;
			typedef T ValueType;
			typedef ValueType* Pointer;
			typedef ValueType& Reference;

		public:
			// Construct the CircleBuffer
			CircleBuffer(Length iBufferSize = 8) :m_Disposed(false)
			{
				Initialize(iBufferSize);
			}

			// Detructe the CircleBuffer
			~CircleBuffer()
			{
				Destory();
			}

			// Allow the object copying
			CircleBuffer(const CircleBuffer& other)
			{
				SetBufferSize(other.GetBufferSize());
				m_CircleBuffer = other.m_CircleBuffer;
				SetReadPos(other.GetReadPos());
				SetWritePos(other.GetWritePos());
				SetIsFull(other.GetIsFull());
				SetDisposed(other.GetDisposed());
			}

			// Allow the object assignment
			CircleBuffer& operator=(const CircleBuffer& other)
			{
				if (this != &other)
				{
					SetBufferSize(other.GetBufferSize());
					m_CircleBuffer = other.m_CircleBuffer;
					SetReadPos(other.GetReadPos());
					SetWritePos(other.GetWritePos());
					SetIsFull(other.GetIsFull());
					SetDisposed(other.GetDisposed());
				}
				return *this;
			}

		public:	
			// Get the data automatically
			BOOL Fetch(Reference data)
			{
				BOOL bSuccess = false;

				// To know wether the buffer is None
				if (IsEmpty() == true)
				{
					Sleep(2);

					return bSuccess;
				}

				// Get the current reading position
				Index iReadPos = GetReadPos() & (GetBufferSize() - 1);

				// Get the data at the position
				bSuccess = Read(iReadPos, data);

				// Change the read pos
				IncreaseReadPos();

				return bSuccess;
			}

			// Push the data automatically
			BOOL Push(Reference data)
			{
				BOOL bSuccess = false;

				// To know wether the buffer is full
				if (IsFull() == true)
				{
					Sleep(2);

					return bSuccess;
				}

				// Get the current writing position
				Index iWritePos = GetWritePos() & (GetBufferSize() - 1);

				// Write the data
				bSuccess = Write(iWritePos, data);

				// Change the write pos
				IncreaseWritePos();

				return bSuccess;
			}

			// Resize the Buffer size
			None Resize(Length iNewSize)
			{			
				SetReadPos(0);
				SetWritePos(0);
				SetIsFull(false);
				SetBufferSize(iNewSize);
				m_CircleBuffer.Resize(GetBufferSize());
			}

			// Clear the buffer
			None Clear()
			{
				SetReadPos(0);
				SetWritePos(0);
				SetIsFull(false);
				m_CircleBuffer.Clear();
			}

		private:
			// Initialize the CircleBuffer
			None Initialize(Length iBufferSize)
			{
				// Set the buffer size
				SetBufferSize(iBufferSize);

				// Resize the array
				m_CircleBuffer.Resize(GetBufferSize());

				// Set the read position
				SetReadPos(0);

				// Set the write position
				SetWritePos(0);

				// Set the full flag
				SetIsFull(false);
			}

			// Destory the CircleBuffer
			None Destory()
			{
				if (!GetDisposed())
				{
					SetDisposed(true);

				}
			}

			// Is the buffer full
			BOOL IsFull()
			{
				if (GetWritePos() - GetReadPos() == GetBufferSize())
				{
					return true;
				}

				return false;
			}

			// Is the buffer None
			BOOL IsEmpty()
			{
				if (GetReadPos() - GetWritePos() == 0)
				{
					return true;
				}

				return false;
			}

			// Increment the position
			None IncrementPos(Index& iPos)
			{
				iPos++;
			}

			// Increase the read position
			None IncreaseReadPos()
			{
				IncrementPos(GetReadPos());
			}

			// Increase the write position
			None IncreaseWritePos()
			{
				IncrementPos(GetWritePos());
			}

			// Read the data from the exactly position
			BOOL Read(Index iPos, Reference data)
			{
				BOOL bSuccess = false;

				// Check the position's legal
				if (iPos<0 || iPos>(GetBufferSize() - 1))
				{
					return bSuccess;
				}

				// Get the data
				data = m_CircleBuffer[iPos];

				bSuccess = true;

				return bSuccess;
			}

			// Write the data from the exactly position
			BOOL Write(Index iPos, Reference data)
			{
				BOOL bSuccess = false;

				// Check the position's legal
				if (iPos<0 || iPos>(GetBufferSize() - 1))
				{
					return bSuccess;
				}

				// Get the data
				m_CircleBuffer[iPos] = data;

				bSuccess = true;

				return bSuccess;
			}

		private:
			// Get the write pos of buffer 
			inline Index GetWritePos() const
			{
				return m_WritePos;
			}

			// Set the write position
			inline None SetWritePos(Index iWritePos)
			{
				m_WritePos = iWritePos;
			}

			// Get the read position
			inline Index GetReadPos() const
			{
				return m_ReadPos;
			}

			// Set the read position
			inline None SetReadPos(Index iReadPos)
			{
				m_ReadPos = iReadPos;
			}

			// Set the buffer size
			inline None SetBufferSize(Length iBufferSize)
			{
				m_BufferSize = iBufferSize;
			}

			// Get the buffer size
			inline Length GetBufferSize() const
			{
				return m_BufferSize;
			}

			// Get the disposed
			inline BOOL GetDisposed() const
			{
				return m_Disposed;
			}

			// Set the disposed	
			inline None SetDisposed(BOOL bDisposed)
			{
				m_Disposed = bDisposed;
			}

		private:
			// Circle buffer
			Array<ValueType> m_CircleBuffer;

			// Buffer size
			Length m_BufferSize;

			// Write position
			Index m_WritePos;

			// Read position
			Index m_ReadPos;

			// Disposed status
			BOOL m_Disposed;
		};
	}
}

#endif // CIRCLEBUFFER_H