///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>V1.0.0</version>
/// <describe>
/// It can find the previous and next element 
///</describe>
/// <date>2019/3/6</date>
///***********************************************************************
#ifndef DOUBLELIST_H
#define DOUBLELIST_H

#include "Tool/Common/SystemType.h"

namespace System
{
	namespace Buffer
	{
		template<class T>
		class DoubleList
		{
		public:
			typedef System::None None;
			typedef System::Boolean BOOL;
			typedef System::Int32 Length;
			typedef System::Int32 Index;
			typedef T ValueType;
			typedef ValueType& Reference;
			typedef ValueType* Pointer;
			typedef struct Element
			{
				ValueType Data;
				struct Element* pPre;
				struct Element* pNext;
			}Node;

			typedef Node* NodeElement;

		public:
			// Construct the DoubleList
			DoubleList() :m_Disposed(false)
			{
				this->Initialize();
			}

			// Detructe the DoubleList
			~DoubleList() 
			{
				this->Destory();
			}

			// Allow the object copying
			DoubleList(const DoubleList& other)
			{
				if (this->IsEmpty())
				{
					this->SetHead(other.GetHead());
				}
				else
				{
					// Copy the list
					this->Copy(other);
				}

				this->SetDisposed(other.GetDisposed());
			}

			// Allow the obejct assignment
			DoubleList& operator=(const DoubleList& other)
			{
				if (this != &other)
				{
					if (this->IsEmpty())
					{
						this->SetHead(other.GetHead());
					}
					else
					{
						// Destory the list at first
						this->DeleteNode(this->GetHead());

						// Create a head node
						this->CreateHeadNode();

						// Copy the list
						this->Copy(other);
					}

					this->SetDisposed(other.GetDisposed());
				}

				return *this;
			}

		public:
			// Add the element 
			None Add(Reference Data)
			{
				// Link the node to the end
				this->LinkToEnd(Data);
			}

			// Remove the element
			BOOL Remove(Reference Data)
			{
				// Unlink the element
				this->Unlink(Data);
			}

			// Get the list size
			Length Size()
			{
				return this->GetLength();
			}

			// Is list None or not
			BOOL IsEmpty()
			{
				return this->_IsEmpty();
			}

		private:
			// Init the list
			None Initialize()
			{
				// Create head node
				this->CreateHeadNode();
			}

			// Destory the list
			None Destory()
			{
				if (!this->GetDisposed())
				{
					this->SetDisposed(true);

					if (!this->_IsEmpty())
					{
						this->DeleteNode(this->GetHead());
					}
				}
			}

			// Delete the element
			None DeleteNode(NodeElement pNodeElement)
			{
				if (pNodeElement == NULL)
				{
					return;
				}

				DeleteNode(pNodeElement->pNext);

				// Destory the node
				this->DestoryNode(pNodeElement);
			}

			// Link a node to the end
			None LinkToEnd(Reference Data)
			{
				// Create a node
				NodeElement pNode = this->CeateNode(Data);

				this->LinkToEnd(pNode);	
			}

			// Link a node to the end
			None LinkToEnd(NodeElement pNodeElement)
			{
				// Get the last element
				NodeElement pLastNode = this->FindLast();

				// Link the element to the end element
				pLastNode->pNext = pNodeElement;

				pNodeElement->pPre = pLastNode;
			}

			// Unlink the node
			None Unlink(NodeElement pNodeElement)
			{
				// Find the previous node
				NodeElement PreNode = pNodeElement->pPre;

				// Unlink
				PreNode->pNext = pNodeElement->pNext;

				pNodeElement->pNext->pPre = PreNode;

				// Destory this node
				this->DestoryNode(pNodeElement);
			}

			// Unlink the node
			None Unlink(Reference Data)
			{
				// Find the current node
				NodeElement CurNode = this->Find(Data);

				this->Unlink(CurNode);
			}

			// Create a node
			NodeElement CeateNode(Reference Data)
			{
				NodeElement pNode = new Node();

				pNode->Data = Data;

				pNode->pPre = NULL;

				pNode->pNext = NULL;

				return pNode;
			}

			// Destory the node
			None DestoryNode(NodeElement pNodeElement)
			{
				if (pNodeElement != NULL)
				{
					delete pNodeElement;

					pNodeElement = NULL;
				}
			}

			// Create head node
			None CreateHeadNode()
			{
				ValueType Data;

				this->SetHead(this->CeateNode(Data));
			}

			// Find the element
			NodeElement Find(Reference Data)
			{
				if (this->_IsEmpty())
				{
					return NULL;
				}

				NodeElement CurNode = this->GetHead();

				while (CurNode->pNext != NULL)
				{
					CurNode = CurNode->pNext;

					// Element class must override the operator ==
					if (CurNode->Data == Data)
					{
						break;
					}
				}

				return CurNode;
			}

			// Find the last element 
			NodeElement FindLast()
			{
				if (this->_IsEmpty())
				{
					return NULL;
				}

				NodeElement CurNode = this->GetHead();

				while (CurNode->pNext != NULL)
				{
					CurNode = CurNode->pNext;
				}

				return CurNode;
			}

			// Get the current list length
			Length GetLength()
			{
				if (this->_IsEmpty())
				{
					return 0;
				}

				NodeElement CurNode = this->GetHead();

				int iCount = 0;

				while (CurNode->pNext != NULL)
				{
					CurNode = CurNode->pNext;

					iCount++;
				}

				return iCount;
			}

			// List is None or not
			BOOL _IsEmpty()
			{
				if (this->GetHead() == NULL)
				{
					return true;
				}

				return false;
			}

			// Copy the list 
			BOOL Copy(const DoubleList& List)
			{
				NodeElement pNode = List.GetHead();

				while (pNode->pNext != NULL)
				{
					pNode = pNode->pNext;

					NodeElement pNode = this->CeateNode(pNode->Data);

					this->LinkToEnd(pNode);
				}
			}

		private:
			// Get the head element
			inline NodeElement GetHead() const
			{
				return m_Head;
			}

			// Set the head element
			inline None SetHead(NodeElement pNodeElement)
			{
				this->m_Head = pNodeElement;
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
			// Head node
			NodeElement m_Head;

			// Disposed status
			BOOL m_Disposed;
		};
	}
}

#endif // DOUBLELIST_H