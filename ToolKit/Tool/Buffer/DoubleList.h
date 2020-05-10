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
				Initialize();
			}

			// Detructe the DoubleList
			~DoubleList()
			{
				Destory();
			}

			// Allow the object copying
			DoubleList(const DoubleList& other)
			{
				// Copy the list
				Copy(other);

				SetDisposed(other.GetDisposed());
			}

			// Allow the obejct assignment
			DoubleList& operator=(const DoubleList& other)
			{
				if (this != &other)
				{
					// Destory the list at first
					DeleteNode(GetHead());

					// Create a head node
					CreateHeadNode();

					// Copy the list
					Copy(other);

					SetDisposed(other.GetDisposed());
				}

				return *this;
			}

		public:
			// Get the element
			BOOL Get(Index iIndex, Reference Data)
			{
				if (iIndex<0 || iIndex > Size())
				{
					return false;
				}

				NodeElement CurNode = Find(iIndex);
				if (CurNode == NULL)
				{
					return false;
				}

				Data = CurNode->Data;

				return true;
			}

			// Add the element 
			None Add(Reference Data)
			{
				// Link the node to the end
				LinkToEnd(Data);
			}

			// Remove the element
			BOOL Remove(Index iIndex)
			{
				if (iIndex<0 || iIndex > Size())
				{
					return false;
				}

				NodeElement CurNode = Find(iIndex);
				if (CurNode == NULL)
				{
					return false;
				}

				// Unlink the element
				Unlink(CurNode);

				return true;
			}

			// Remove the element
			BOOL Remove(Reference Data)
			{
				// Unlink the element
				Unlink(Data);
			}

			// Get the list size
			Length Size()
			{
				return GetLength();
			}

			// Is list None or not
			BOOL IsEmpty()
			{
				return _IsEmpty();
			}

		private:
			// Init the list
			None Initialize()
			{
				// Create head node
				CreateHeadNode();
			}

			// Destory the list
			None Destory()
			{
				if (!GetDisposed())
				{
					SetDisposed(true);

					if (!IsEmpty())
					{
						DeleteNode(GetHead());
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
				DestoryNode(pNodeElement);
			}

			// Link a node to the end
			None LinkToEnd(Reference Data)
			{
				// Create a node
				NodeElement pNode = CeateNode(Data);

				LinkToEnd(pNode);	
			}

			// Link a node to the end
			None LinkToEnd(NodeElement pNodeElement)
			{
				// Get the last element
				NodeElement pLastNode = FindLast();

				// Link the element to the end element
				pLastNode->pNext = pNodeElement;

				pNodeElement->pPre = pLastNode;
			}

			// Unlink the node
			None Unlink(NodeElement pNodeElement)
			{
				if (pNodeElement == NULL)
				{
					return;
				}

				if (pNodeElement == GetHead())
				{
					return;
				}

				// Find the previous node
				NodeElement PreNode = pNodeElement->pPre;

				// Unlink
				PreNode->pNext = pNodeElement->pNext;

				pNodeElement->pNext->pPre = PreNode;

				// Destory this node
				DestoryNode(pNodeElement);
			}

			// Unlink the node
			None Unlink(Reference Data)
			{
				// Find the current node
				NodeElement CurNode = Find(Data);

				Unlink(CurNode);
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

				SetHead(CeateNode(Data));
			}

			// Find the element
			NodeElement Find(Index iIndex)
			{
				if (IsEmpty())
				{
					return NULL;
				}

				NodeElement CurNode = GetHead();

				Index iCurIndex = 0;

				while (CurNode->pNext != NULL)
				{
					CurNode = CurNode->pNext;

					if (iIndex == iCurIndex)
					{
						break;
					}

					++iCurIndex;
				}

				return CurNode;
			}

			// Find the element
			NodeElement Find(Reference Data)
			{
				if (IsEmpty())
				{
					return NULL;
				}

				NodeElement CurNode = GetHead();

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
				NodeElement CurNode = GetHead();

				while (CurNode->pNext != NULL)
				{
					CurNode = CurNode->pNext;
				}

				return CurNode;
			}

			// Get the current list length
			Length GetLength()
			{
				if (IsEmpty())
				{
					return 0;
				}

				NodeElement CurNode = GetHead();
				if (CurNode ==NULL)
				{
					return 0;
				}

				int iCount = 0;

				while (CurNode->pNext != NULL)
				{
					CurNode = CurNode->pNext;

					++iCount;
				}

				return iCount;
			}

			// List is None or not
			BOOL _IsEmpty()
			{
				NodeElement pNode = GetHead();

				if (pNode == NULL)
				{
					return true;
				}

				if (pNode->pNext == NULL)
				{
					return true;
				}

				return false;
			}

			// Copy the list 
			BOOL Copy(const DoubleList& List)
			{
				NodeElement pHeadNode = List.GetHead();
				if (pHeadNode == NULL)
				{
					return false;
				}

				NodeElement pNode = pHeadNode->pNext;

				while (pNode != NULL)
				{
					NodeElement pNewNode = CeateNode(pNode->Data);

					LinkToEnd(pNewNode);

					pNode = pNode->pNext;
				}

				return true;
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
				m_Head = pNodeElement;
			}

			// Get the disposed status
			inline BOOL GetDisposed() const
			{
				return m_Disposed;
			}

			// Set the disposed status
			inline None SetDisposed(BOOL bDisposed)
			{
				m_Disposed = bDisposed;
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