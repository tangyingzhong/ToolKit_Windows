///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>V1.0.0</version>
/// <describe>
/// It can be used betwwen producer and customer as a common cache
///</describe>
/// <date>2019/3/6</date>
///***********************************************************************
#ifndef CIRCLEBUFFER_H
#define CIRCLEBUFFER_H

#include "Tool\Common\SystemType.h"
#include "Array.h"

namespace System
{
	namespace Buffer
	{
		template <class T>
		class CircleBuffer
		{
		public:
			typedef System::Empty Empty;
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
				this->SetBufferSize(other.GetBufferSize());
				this->m_CircleBuffer = other.m_CircleBuffer;
				this->SetReadPos(other.GetReadPos());
				this->SetWritePos(other.GetWritePos());
				this->SetIsFull(other.GetIsFull());
				this->SetDisposed(other.GetDisposed());
			}

			// Allow the object assignment
			CircleBuffer& operator=(const CircleBuffer& other)
			{
				if (this != &other)
				{
					this->SetBufferSize(other.GetBufferSize());
					this->m_CircleBuffer = other.m_CircleBuffer;
					this->SetReadPos(other.GetReadPos());
					this->SetWritePos(other.GetWritePos());
					this->SetIsFull(other.GetIsFull());
					this->SetDisposed(other.GetDisposed());
				}
				return *this;
			}

		public:	
			// Get the data automatically
			BOOL Fetch(Reference data)
			{
				BOOL bSuccess = false;

				// To know wether the buffer is empty
				if (this->IsEmpty() == true)
				{
					Sleep(2);

					return bSuccess;
				}

				// Get the current reading position
				Index iReadPos = this->GetReadPos() & (this->GetBufferSize() - 1);

				// Get the data at the position
				bSuccess = this->Read(iReadPos, data);

				// Change the read pos
				this->IncreaseReadPos();

				return bSuccess;
			}

			// Push the data automatically
			BOOL Push(Reference data)
			{
				BOOL bSuccess = false;

				// To know wether the buffer is full
				if (this->IsFull() == true)
				{
					Sleep(2);

					return bSuccess;
				}

				// Get the current writing position
				Index iWritePos = this->GetWritePos() & (this->GetBufferSize() - 1);

				// Write the data
				bSuccess = this->Write(iWritePos, data);

				// Change the write pos
				this->IncreaseWritePos();

				return bSuccess;
			}

			// Resize the Buffer size
			Empty Resize(Length iNewSize)
			{			
				this->SetReadPos(0);
				this->SetWritePos(0);
				this->SetIsFull(false);
				this->SetBufferSize(iNewSize);
				this->m_CircleBuffer.Resize(this->GetBufferSize());
			}

			// Clear the buffer
			Empty Clear()
			{
				this->SetReadPos(0);
				this->SetWritePos(0);
				this->SetIsFull(false);
				this->m_CircleBuffer.Clear();
			}

		private:
			// Initialize the CircleBuffer
			Empty Initialize(Length iBufferSize)
			{
				// Set the buffer size
				this->SetBufferSize(iBufferSize);

				// Resize the array
				this->m_CircleBuffer.Resize(this->GetBufferSize());

				// Set the read position
				this->SetReadPos(0);

				// Set the write position
				this->SetWritePos(0);

				// Set the full flag
				this->SetIsFull(false);
			}

			// Destory the CircleBuffer
			Empty Destory()
			{
				if (!GetDisposed())
				{
					SetDisposed(true);

				}
			}

			// Is the buffer full
			BOOL IsFull()
			{
				if (this->GetWritePos() - this->GetReadPos() == this->GetBufferSize())
				{
					return true;
				}

				return false;
			}

			// Is the buffer empty
			BOOL IsEmpty()
			{
				if (this->GetReadPos() - this->GetWritePos() == 0)
				{
					return true;
				}

				return false;
			}

			// Increment the position
			Empty IncrementPos(Index& iPos)
			{
				iPos++;
			}

			// Increase the read position
			Empty IncreaseReadPos()
			{
				this->IncrementPos(this->GetReadPos());
			}

			// Increase the write position
			Empty IncreaseWritePos()
			{
				this->IncrementPos(this->GetWritePos());
			}

			// Read the data from the exactly position
			BOOL Read(Index iPos, Reference data)
			{
				BOOL bSuccess = false;

				// Check the position's legal
				assert(iPos >= 0);
				assert(iPos <= (this->GetBufferSize() - 1));

				if (iPos<0 || iPos>(this->GetBufferSize() - 1))
				{
					return bSuccess;
				}

				// Get the data
				data = this->m_CircleBuffer[iPos];

				bSuccess = true;

				return bSuccess;
			}

			// Write the data from the exactly position
			BOOL Write(Index iPos, Reference data)
			{
				BOOL bSuccess = false;

				// Check the position's legal
				assert(iPos >= 0);
				assert(iPos <= (this->GetBufferSize() - 1));

				if (iPos<0 || iPos>(this->GetBufferSize() - 1))
				{
					return bSuccess;
				}

				// Get the data
				this->m_CircleBuffer[iPos] = data;

				bSuccess = true;

				return bSuccess;
			}

		private:
			// Get the write pos of buffer 
			inline Index GetWritePos() const
			{
				return this->m_WritePos;
			}

			// Set the write position
			inline Empty SetWritePos(Index iWritePos)
			{
				this->m_WritePos = iWritePos;
			}

			// Get the read position
			inline Index GetReadPos() const
			{
				return m_ReadPos;
			}

			// Set the read position
			inline Empty SetReadPos(Index iReadPos)
			{
				this->m_ReadPos = iReadPos;
			}

			// Set the buffer size
			inline Empty SetBufferSize(Length iBufferSize)
			{
				this->m_BufferSize = iBufferSize;
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
			inline Empty SetDisposed(BOOL bDisposed)
			{
				this->m_Disposed = bDisposed;
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