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

namespace System
{
	namespace Buffer
	{
		///*********************************************************
		/// <class> CircleBuffer<T> </class>
		/// <summary>
		/// it is circle buffer designed by STL vector
		/// </summary>
		/// <version>V1.0.0 </version>
		/// <goup> C++ </group>
		/// <author>tangyingzhong</author>
		/// <contact>tangyz114987@outlook.com</contact>
		///**********************************************************/
		template <class T>
		class CircleBuffer
		{
		public:
			typedef System::Empty Empty;
			typedef System:Boolean BOOL;
			typedef System::Object Object;
			typedef System::Byte Byte;
			typedef System::ByteArray ByteArray;
			typedef System::UInt32 Length;
			typedef Length Offset;
			typedef Offset Index;
			typedef T ValueType;
			typedef ValueType* Pointer;
			typedef ValueType& Reference;

			typedef struct _RingParamenter
			{
				std::vector<ValueType> vCache;				// Cache for the data 
				Length iCacheSize;							// Cache size
				Offset iReadPos;							// Read position
				Offset iWritePos;							// Write position
				BOOL bIsFull;								// Is the cache full or not
			}RingParamenter;

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
				this->m_RingParamenter.vCache = other.m_RingParamenter.vCache;
				this->m_RingParamenter.iCacheSize = 0;
				this->m_RingParamenter.iReadPos = 0;
				this->m_RingParamenter.iWritePos = 0;
				this->m_RingParamenter.iIsFull = false;
				this->m_Disposed = other.m_Disposed;
			}

			// Allow the object assignment
			CircleBuffer& operator=(const CircleBuffer& other)
			{
				if (this != &other)
				{
					this->m_RingParamenter.vCache = other.m_RingParamenter.vCache;
					this->m_RingParamenter.iCacheSize = 0;
					this->m_RingParamenter.iReadPos = 0;
					this->m_RingParamenter.iWritePos = 0;
					this->m_RingParamenter.iIsFull = false;
					this->m_Disposed = other.m_Disposed;
				}
				return *this;
			}

		public:
			// Read the data from the exactly position
			BOOL Read(Reference data, Offset iPos)
			{
				BOOL bSuccess = false;

				// To know wether there is data in buffer
				if (this->IsEmpty() == true)
				{
					Sleep(2);
					return bSuccess;
				}

				// Check the position's legal
				assert(iPos >= 0);
				assert(iPos <= (this->m_RingParamenter.iCacheSize - 1));

				if (iPos<0 || iPos>(this->m_RingParamenter.iCacheSize - 1))
				{
					return bSuccess;
				}

				// Get the data
				data = this->m_RingParamenter.vCache[iPos];

				bSuccess = true;

				return bSuccess;
			}

			// Read the data automatically
			BOOL Read(Reference data)
			{
				BOOL bSuccess = false;

				// To know wether there is data in buffer
				if (this->IsEmpty() == true)
				{
					Sleep(2);
					return bSuccess;
				}

				// Get the current reading position
				Index iReadPos = this->m_RingParamenter.iReadPos & (this->m_RingParamenter.iCacheSize - 1);

				// Get the data
				data = this->m_RingParamenter.vCache[iReadPos];

				// Change the read pos
				++(this->m_RingParamenter.iReadPos);

				bSuccess = true;

				return bSuccess;
			}

			// Write the data automatically
			BOOL Write(Reference data)
			{
				BOOL bSuccess = false;

				// To know wether there is data in buffer
				if (this->IsFull() == true)
				{
					Sleep(2);
					return bSuccess;
				}

				// Get the current writing position
				Index iWritePos = this->m_RingParamenter.iWritePos & (this->m_RingParamenter.iCacheSize - 1);

				// Write the data
				this->m_RingParamenter.vCache[iWritePos] = data;

				// Change the write pos
				++(this->m_RingParamenter.iWritePos);

				if (this->m_RingParamenter.iWritePos == this->m_RingParamenter.iCacheSize)
				{
					this->m_RingParamenter.bIsFull = true;
				}

				bSuccess = true;

				return bSuccess;
			}

			// Resize the Buffer size
			Empty Resize(Length iNewSize)
			{
				assert(iNewSize > 0);
				assert(this->m_RingParamenter.iCacheSize != iNewSize);

				if (iNewSize <= 0 || this->m_RingParamenter.iCacheSize == iNewSize)
				{
					return;
				}

				this->m_RingParamenter.vCache.resize(iNewSize);
			}

			// Clear the buffer
			Empty Clear()
			{
				Length iBackupLength = this->m_RingParamenter.iCacheSize;

				this->ClearRingParamenter();

				this->Resize(iBackupLength);
			}

			// Get the buffer full state
			inline BOOL GetIsFull() const
			{
				return this->m_RingParamenter.iIsFull;
			}

			// Get the write pos of buffer 
			inline Offset GetWritePos() const
			{
				return this->m_RingParamenter.iWritePos;
			}

		private:
			// Is the buffer full
			BOOL IsFull()
			{
				if (this->m_RingParamenter.iWritePos - this->m_RingParamenter.iReadPos == this->m_RingParamenter.iCacheSize)
				{
					return true;
				}

				return false;
			}

			// Is the buffer empty
			BOOL IsEmpty()
			{
				if (this->m_RingParamenter.iWritePos - this->m_RingParamenter.iReadPos == 0)
				{
					return true;
				}

				return false;
			}

		private:
			// Initialize the CircleBuffer IPC
			Empty Initialize(Length iCacheSize)
			{
				// Clear the ring paramenter
				this->ClearRingParamenter();

				// Set the buffer size
				this->m_RingParamenter.iCacheSize = iCacheSize;
			}

			// Destory the CircleBuffer IPC
			Empty Destory()
			{
				if (!GetDisposed())
				{
					SetDisposed(true);
				}
			}

			// Clear the ring paramenter
			Empty ClearRingParamenter()
			{
				std::vector<ValueType>().swap(this->m_RingParamenter.vCache);
				this->m_RingParamenter.iCacheSize = 0;
				this->m_RingParamenter.iReadPos = 0;
				this->m_RingParamenter.iWritePos = 0;
				this->m_RingParamenter.iIsFull = false;
			}

		private:
			// Set the write position
			inline Empty SetWritePos(Offset iWritePos)
			{
				this->m_RingParamenter.iWritePos = iWritePos;
			}

			// Set the buffer full state
			inline Empty SetIsFull(BOOL bIsFull)
			{
				this->m_RingParamenter.bIsFull = bIsFull;
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
			// Paramenter of the cache
			RingParamenter m_RingParamenter;

			// Disposed status
			BOOL m_Disposed;

		};
	}
}

#endif //CIRCLEBUFFER_H_