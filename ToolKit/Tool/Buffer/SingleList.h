///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>V1.0.0</version>
/// <describe>
/// SingleList structure which can fast insert and delete elments
///</describe>
/// <date>2019/3/6</date>
///***********************************************************************
#ifndef SINGLELIST_H
#define SINGLELIST_H

#include "Tool\Common\SystemType.h"

namespace System
{
	namespace Buffer
	{
		///*********************************************************
		/// <class> SingleList<T> </class>
		/// <summary>
		/// List can insert and delete the elements quickly.
		/// </summary>
		/// <version>V1.0.0 </version>
		/// <goup> C++ </group>
		/// <author>tangyingzhong</author>
		/// <contact>tangyz114987@outlook.com</contact>
		///**********************************************************/
		template<class T>
		class SingleList
		{
		public:
			typedef System::Empty Empty;
			typedef System::Boolean BOOL;
			typedef System::Int32 Length;
			typedef System::Int32 Index;
			typedef System::SByteArray SByteArray;
			typedef T ValueType;
			typedef ValueType& Reference;
			typedef ValueType* Pointer;
			typedef struct Element
			{
				ValueType Data;
				struct Element* pNext;
			}Node;

			typedef Node* NodeElement;

		public:
			// Construct the SingleList
			SingleList() :m_Disposed(false)
			{
				this->Initialize();
			}

			// Detructe the SingleList
			~SingleList() 
			{
				this->Destory();
			}

			// Allow the object copying
			SingleList(const SingleList& other)
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
			SingleList& operator=(const SingleList& other)
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
			Empty Add(Reference Data)
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

			// Is list empty or not
			BOOL IsEmpty()
			{
				return this->_IsEmpty();
			}

		private:
			// Init the list
			Empty Initialize()
			{
				// Create head node
				this->CreateHeadNode();
			}

			// Destory the list
			Empty Destory()
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
			Empty DeleteNode(NodeElement pNodeElement)
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
			Empty LinkToEnd(Reference Data)
			{
				// Create a node
				NodeElement pNode = this->CeateNode(Data);

				// Get the last element
				NodeElement pLastNode = this->FindLast();

				// Link the element to the end element
				pLastNode->pNext = pNode;
			}

			// Link a node to the end
			Empty LinkToEnd(NodeElement pNodeElement)
			{
				// Get the last element
				NodeElement pLastNode = this->FindLast();

				// Link the element to the end element
				pLastNode->pNext = pNodeElement;
			}

			// Unlink the node
			Empty Unlink(NodeElement pNodeElement)
			{
				// Find the previous node
				NodeElement PreNode = this->FindPrevious(pNodeElement);

				// Unlink
				PreNode->pNext = pNodeElement->pNext;

				// Destory this node
				this->DestoryNode(pNodeElement);
			}

			// Unlink the node
			Empty Unlink(Reference Data)
			{
				// Find the previous node
				NodeElement PreNode = this->FindPrevious(Data);

				// Unlink
				PreNode->pNext = pNodeElement->pNext;

				// Destory this node
				this->DestoryNode(pNodeElement);
			}

			// Create a node
			NodeElement CeateNode(Reference Data)
			{
				NodeElement pNode = new Node();

				pNode->Data = Data;

				pNode->pNext = NULL;

				return pNode;
			}

			// Destory the node
			Empty DestoryNode(NodeElement pNodeElement)
			{
				if (pNodeElement != NULL)
				{
					delete pNodeElement;

					pNodeElement = NULL;
				}
			}

			// Create head node
			Empty CreateHeadNode()
			{
				this->SetHead(this->CeateNode(NULL));
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

			// Find the previous element
			NodeElement FindPrevious(NodeElement pNode)
			{
				if (this->_IsEmpty())
				{
					return NULL;
				}

				if (pNode == NULL)
				{
					return NULL;
				}

				NodeElement CurNode = this->GetHead();

				NodeElement PreNode = CurNode;

				while (CurNode->pNext != NULL)
				{
					PreNode = CurNode;

					CurNode = CurNode->pNext;

					if (CurNode == pNode)
					{
						break;
					}
				}

				return PreNode;
			}

			// Find the previous element
			NodeElement FindPrevious(Reference Data)
			{
				if (this->_IsEmpty())
				{
					return NULL;
				}

				if (pNode == NULL)
				{
					return NULL;
				}

				NodeElement CurNode = this->GetHead();

				NodeElement PreNode = CurNode;

				while (CurNode->pNext != NULL)
				{
					PreNode = CurNode;

					CurNode = CurNode->pNext;

					if (CurNode->Data == Data)
					{
						break;
					}
				}

				return PreNode;
			}

			// Get the element's position(-1: fail to find)
			Index GetPos(Reference Data)
			{
				if (this->_IsEmpty())
				{
					return -1;
				}

				NodeElement CurNode = this->GetHead();

				int iCount = -1;

				while (CurNode->pNext != NULL)
				{
					CurNode = CurNode->pNext;

					iCount++;

					// Element class must override the operator ==
					if (CurNode->Data == Data)
					{
						break;
					}
				}

				return iCount;
			}

			// Find the element in position
			NodeElement At(Index iPos)
			{
				if (this->_IsEmpty())
				{
					return NULL;
				}

				if (iPos < 0 || iPos >= this->GetLength())
				{
					return NULL;
				}

				NodeElement CurNode = this->GetHead();

				// Not inclued head node 
				int iCount = -1;

				while (CurNode->pNext != NULL)
				{
					CurNode = CurNode->pNext;

					iCount++;

					if (iCount == iPos)
					{
						break;
					}
				}

				return CurNode;
			}
			
			// Get the index element(you shouldn't use it in the loop)
			Reference operator[](Index iPos)
			{
				if (this->_IsEmpty())
				{
					return m_EmptyElment;
				}

				if (iPos<0 || iPos >= this->GetLength())
				{
					return m_EmptyElment;
				}

				NodeElement pNode = this->At(iPos);

				return pNode->Data;
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

			// List is empty or not
			BOOL _IsEmpty()
			{
				if (this->GetHead() == NULL)
				{
					return true;
				}

				return false;
			}

			// Copy the list 
			BOOL Copy(const SingleList& List)
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
			inline Empty SetHead(NodeElement pNodeElement)
			{
				this->m_Head = pNodeElement;
			}

			// Get the disposed status
			inline BOOL GetDisposed() const
			{
				return m_Disposed;
			}

			// Set the disposed status
			inline Empty SetDisposed(BOOL bDisposed)
			{
				this->m_Disposed = bDisposed;
			}

		private:
			// Head node
			NodeElement m_Head;

			// Empty value
			ValueType m_EmptyElment;

			// Disposed status
			BOOL m_Disposed;
		};
	}
}

#endif //SINGLELIST_H