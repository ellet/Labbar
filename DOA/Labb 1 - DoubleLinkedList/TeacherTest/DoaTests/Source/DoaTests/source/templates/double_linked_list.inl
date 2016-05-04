#include <cassert>


namespace mhm
{
    template<typename T>
    DoubleLinkedList<T>::Node::Node( const T &aValue )
    : myData( aValue )
    , myNext( nullptr )
    , myPrev( nullptr )
    {
    }


    template<typename T>
    DoubleLinkedList<T>::DoubleLinkedList( void )
    : myFirst( nullptr )
    , myLast( nullptr )
    {
    }


    template<typename T>
    typename DoubleLinkedList<T>::Node *DoubleLinkedList<T>::GetFirstNode( void )
    {
        return myFirst;
    }


    template<typename T>
    typename DoubleLinkedList<T>::Node *DoubleLinkedList<T>::GetLastNode( void )
    {
        return myLast;
    }


    template<typename T>
    void DoubleLinkedList<T>::InsertNodeBeforeNode( Node *aNode, Node *aNodeToInsert )
    {
        aNodeToInsert->myNext = aNode;

        if( aNode != nullptr )
        {
            aNodeToInsert->myPrev = aNode->myPrev;

            if( aNode->myPrev )
            {
                aNode->myPrev->myNext = aNodeToInsert;
            }
            else
            {
                myFirst = aNodeToInsert;
            }

            aNode->myPrev = aNodeToInsert;
        }
        else
        {
            if( myLast != nullptr )
            {
                aNodeToInsert->myPrev = myLast;
                myLast->myNext = aNodeToInsert;
                myLast = aNodeToInsert;
            }
            else if( myFirst == nullptr )
            {
                aNodeToInsert->myPrev = nullptr;
                myFirst
                = myLast
                = aNodeToInsert;
            }
        }
    }


    template<typename T>
    void DoubleLinkedList<T>::InsertNodeSorted( Node *aNode )
    {
        Node *currentNode = myFirst;

        while( currentNode && currentNode->myData > aNode->myData )
        {
            currentNode = currentNode->myNext;
        }

        InsertNodeBeforeNode( currentNode, aNode );
    }
    

    template<typename T>
    void DoubleLinkedList<T>::InsertNodeSorted( const T &aValue )
    {
        Node *currentNode = myFirst;

        while( currentNode && currentNode->myData > aValue )
        {
            currentNode = currentNode->myNext;
        }

        InsertNodeBeforeNode( currentNode, new Node( aValue ) );
    }


    template<typename T>
    typename DoubleLinkedList<T>::Node *DoubleLinkedList<T>::Find( const T &aValue )
    {
        Node *currentNode = myFirst;

        while( currentNode && currentNode->myData != aValue )
        {
            currentNode = currentNode->myNext;
        }

        return currentNode;
    }


    template<typename T>
    void DoubleLinkedList<T>::DeleteNode( Node *aNode )
    {
        if( myFirst == aNode )
        {
            myFirst = aNode->myNext;
        }
        else
        {
            aNode->myPrev->myNext = aNode->myNext;
        }

        if( myLast == aNode )
        {
            myLast = aNode->myPrev;
        }
        else
        {
            aNode->myNext->myPrev = aNode->myPrev;
        }
    }


    template<typename T>
    void DoubleLinkedList<T>::DeleteNode( const T &aValue )
    {
        Node *foundNode = Find( aValue );

        assert( foundNode != nullptr && "Couldn't find node to delete." );

        DeleteNode( foundNode );
    }
}
