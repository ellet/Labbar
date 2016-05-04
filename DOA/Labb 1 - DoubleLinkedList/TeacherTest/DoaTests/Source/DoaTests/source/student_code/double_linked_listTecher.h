#pragma once
#include <cassert>


namespace CommonUtilities
{
    template<typename T>
    class DoubleLinkedList
    {
    public:     
				class Node
                {
                public:     

					Node()
					{
						myNextNode = nullptr;
						myPrevNode = nullptr;
					}
					Node( const T &aValue )
					{
						myNextNode = nullptr;
						myPrevNode = nullptr;
						myData = aValue;
					}
					~Node()
					{

					}

					inline Node* GetPrevNode() const
					{
						return myPrevNode;
					}

					inline void SetPrevNode(Node* aNode)
					{
						myPrevNode = aNode;
					}

					inline Node* GetNextNode() const
					{
						return myNextNode;
					}

					inline void SetNextNode(Node* aNode)
					{
						myNextNode = aNode;
					}

					inline T GetData() const
					{
						return myData;
					}
				private:

					

					Node *myNextNode;
					Node *myPrevNode;
					T myData;
                };


				DoubleLinkedList()
				{
					myFirstNode = nullptr;
					myLastNode = nullptr;
				}
				~DoubleLinkedList()
				{
					if (myFirstNode != nullptr)
					{
						DoubleLinkedList<T>::Node *node = myFirstNode;
						while (node->GetNextNode() != nullptr)
						{
							node = node->GetNextNode();
							delete node->GetPrevNode();
						}
						delete node;
					}

					myFirstNode = nullptr;
					myLastNode = nullptr;
				}

				/**
				*  Returns the tail of the list.
				*
				*  @return Returns the first node of the list or nullptr if the list
				*          is empty.
				*/
				inline Node *GetFirstNode(void)
				{
					return myFirstNode;
				}
				


				/**
				*  Returns the head of the list.
				*
				*  @return Returns the last node of the list or nullptr if the list
				*          is empty.
				*/
				inline Node *GetLastNode(void)
				{
					return myLastNode;
				}


				/**
				*  Inserts a node after another node.
				*
				*  @param  aNode gives the node which to place the new node before
				*  @param  aNodeToInsert gives the node to insert into the list
				*/
				inline void InsertNodeBeforeNode(Node *aNode, Node *aNodeToInsert)
				{
					assert(aNode != nullptr && "Can't insert node after node on empty list!");
						if (myFirstNode == nullptr && aNode != nullptr)
						{
							assert(false && "Trying to insert before non-existing node!");
							return;
						}
						else if (myFirstNode == nullptr && aNode == nullptr)
						{
							myFirstNode = aNodeToInsert;
							myLastNode = aNodeToInsert;
							return;
						}

						//list
						DoubleLinkedList<T>::Node *node = myLastNode;
						while (node != nullptr && node != aNode)
						{
							node = node->GetPrevNode();
						}

						aNodeToInsert->SetPrevNode(node);
						if (node == nullptr)
						{
							aNodeToInsert->SetNextNode(myFirstNode);
						}
						else
						{
							aNodeToInsert->SetNextNode(node->GetNextNode());
						}

						if (aNodeToInsert->GetNextNode() != nullptr)
						{
							aNodeToInsert->GetNextNode()->SetPrevNode(aNodeToInsert);
						}
						else
						{
							myLastNode = aNodeToInsert;
						}

						if (node == nullptr)
						{
							myFirstNode = aNodeToInsert;
						}
						else
						{
							node->SetNextNode(aNodeToInsert);
						}
				}


				/**
				*  Insert a node sorted in decending order. The value of the node to
				*  insert must be comparable using the < operator.
				*
				*  @param  aNodeToInsert gives the node to insert.
				*/
				inline void InsertNodeSorted(Node *aNodeToInsert)
				{
					if (myFirstNode == nullptr)
					{
						myFirstNode = aNodeToInsert;
						myLastNode = aNodeToInsert;
						return;
					}

					//list
					DoubleLinkedList<T>::Node *node = myFirstNode;
					while (node != nullptr && aNodeToInsert->GetData() < node->GetData())
					{
						node = node->GetNextNode();
					}

					if (node == myFirstNode)
					{
						InsertNodeBeforeNode(myFirstNode, aNodeToInsert);
					}
					else if (node != nullptr)
					{
						InsertNodeBeforeNode(node->GetPrevNode(), aNodeToInsert);
					}
					else // node == nullptr
					{
						InsertNodeBeforeNode(myLastNode, aNodeToInsert);
					}
				}


				/**
				*  Insert a node sorted in decending order. The value to insert must
				*  be comparable using the < operator.
				*
				*  @param  aNodeToInsert gives the node to insert.
				*/
				inline void InsertNodeSorted(const T &aValueToInsert)
				{
					//DoubleLinkedList<T>::Node *node = new DoubleLinkedList<T>::Node(aValueToInsert);
					InsertNodeSorted(new DoubleLinkedList<T>::Node(aValueToInsert));
				}


				/**
				*  Deletes the given node from the list.
				*
				*  !!Asserts if the node isn't found.
				*
				*  @param  aNodeToDelete gives the node to delete from the list.
				*/
				inline void DeleteNode(Node *aNodeToDelete)
				{
					if (aNodeToDelete == nullptr || Find(aNodeToDelete->GetData()) == nullptr)
					{
						assert(false && "Node not found!");
					}

					if (aNodeToDelete->GetPrevNode() == nullptr && aNodeToDelete->GetNextNode() == nullptr)
					{
						delete aNodeToDelete;
						myFirstNode = nullptr;
						myLastNode = nullptr;
						return;
					}

					if (aNodeToDelete->GetPrevNode() == nullptr)
					{
						myFirstNode = aNodeToDelete->GetNextNode();
					}
					else
					{
						aNodeToDelete->GetPrevNode()->SetNextNode(aNodeToDelete->GetNextNode());
					}

					if (aNodeToDelete->GetNextNode() == nullptr)
					{
						myLastNode = aNodeToDelete->GetPrevNode();
					}
					else
					{
						aNodeToDelete->GetNextNode()->SetPrevNode(aNodeToDelete->GetPrevNode());
					}

					delete aNodeToDelete;
				}


				/**
				*  Deletes the first node with the given value from the list.
				*
				*  !!Asserts if the value isn't found.
				*
				*  @param  aValueToDelete gives the value to delete from the list.
				*/
				inline void DeleteNode(const T &aValueToDelete)
				{
					DeleteNode(Find(aValueToDelete));
				}


				/**
				*  Searches the list for the given value and if found returns the
				*  first node with the value.
				*
				*  @param  aValue gives the value to search for
				*
				*  @return Returns the first node with the given value or nullptr if
				*          the value isn't found.
				*/
				inline Node *Find(const T &aValue)
				{
					DoubleLinkedList<T>::Node *node = myFirstNode;

					if (node == nullptr)
					{
						return node;
					}

					while (node->GetData() != aValue)
					{
						node = node->GetNextNode();
						if (node == nullptr)
						{
							return node;
						}
					}

					return node;
				}

			private:
				Node *myFirstNode;
				Node *myLastNode;

    };
}