#pragma once


namespace mhm
{
    template<typename T>
    class DoubleLinkedList
    {
    public:     class Node
                {
                            friend class DoubleLinkedList;

                public:     Node( const T &aValue );
                            
                private:    Node *myNext,
                                 *myPrev; 
                            T myData;
                };


                DoubleLinkedList( void );


                /**
                 *  Returns the tail of the list.
                 *
                 *  @return Returns the first node of the list or nullptr if the list
                 *          is empty.
                 */
                Node *GetFirstNode( void );


                /**
                 *  Returns the head of the list.
                 *
                 *  @return Returns the last node of the list or nullptr if the list
                 *          is empty.
                 */
                Node *GetLastNode( void );


                /**
                 *  Inserts a node before another node.
                 *
                 *  @param  aNode gives the node which to place the new node before
                 *  @param  aNodeToInsert gives the node to insert into the list
                 */
                void InsertNodeBeforeNode( Node *aNode, Node *aNodeToInsert );


                /**
                 *  Insert a node sorted in decending order. The value of the node to
                 *  insert must be comparable using the < operator.
                 *
                 *  @param  aNodeToInsert gives the node to insert.
                 */
                void InsertNodeSorted( Node *aNodeToInsert );


                /**
                 *  Insert a node sorted in decending order. The value to insert must
                 *  be comparable using the < operator.
                 *
                 *  @param  aNodeToInsert gives the node to insert.
                 */
                void InsertNodeSorted( const T &aValueToInsert );


                /**
                 *  Deletes the given node from the list.
                 *
                 *  !!Asserts if the node isn't found.
                 *
                 *  @param  aNodeToDelete gives the node to delete from the list.
                 */
                void DeleteNode( Node *aNodeToDelete );


                /**
                 *  Deletes the first node with the given value from the list.
                 *
                 *  !!Asserts if the value isn't found.
                 *
                 *  @param  aValueToDelete gives the value to delete from the list.
                 */
                void DeleteNode( const T &aValueToDelete );


                /**
                 *  Searches the list for the given value and if found returns the
                 *  first node with the value.
                 *
                 *  @param  aValue gives the value to search for
                 *
                 *  @return Returns the first node with the given value or nullptr if
                 *          the value isn't found.
                 */
                Node *Find( const T &aValue );

    private:    Node *myFirst,
                     *myLast;
    };
}


#include "double_linked_list.inl"
