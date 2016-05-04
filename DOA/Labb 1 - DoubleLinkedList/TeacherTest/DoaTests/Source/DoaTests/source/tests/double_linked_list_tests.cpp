#include "stdafx.h"

#include "student_code/double_linked_list.h"
using namespace CommonUtilities;


using namespace Microsoft::VisualStudio::CppUnitTestFramework;


#pragma warning( push )
#pragma warning( disable : 4201 4238 )


template class DoubleLinkedList<double>;


namespace CollectionsTests
{
    TEST_CLASS( DoubleLinkedListTests )
    {
    public:     /**
                 *  Tests the default constructor.
                 *
                 *  Checks that the first node is set to nullptr.
                 */
                TEST_METHOD( DoubleLinkedList_DefaultConstructor_FirstNode )
                {
                    DoubleLinkedList<double> l;

                    Assert::IsNull( l.GetFirstNode(), L"An empty list must return nullptr from GetFirstNode()." );
                }


                /**
                 *  Tests the default constructor.
                 *
                 *  Checks that the last node is set to nullptr.
                 */
                TEST_METHOD( DoubleLinkedList_DefaultConstructor_LastNode )
                {
                    DoubleLinkedList<double> l;

                    Assert::IsNull( l.GetLastNode(), L"An empty list must return nullptr from GetLastNode()." );
                }


                /**
                 *  Test insertion into an empty list.
                 *
                 *  Checks that the first node isn't set to nullptr.
                 */
                TEST_METHOD( DoubleLinkedList_InsertSortedInEmpty_FirstNode )
                {
                    DoubleLinkedList<double> l;

                    l.InsertNodeSorted( 12.4 );

                    Assert::IsNotNull( l.GetFirstNode() );
                }


                /**
                 *  Test insertion into an empty list.
                 *
                 *  Checks that the last node isn't set to nullptr.
                 */
                TEST_METHOD( DoubleLinkedList_InsertSortedInEmpty_LastNode )
                {
                    DoubleLinkedList<double> l;

                    l.InsertNodeSorted( 12.4 );

                    Assert::IsNotNull( l.GetLastNode() );
                }


                /**
                 *  Test insertion into an empty list.
                 *
                 *  Checks that the first and the last node are the same.
                 */
                TEST_METHOD( DoubleLinkedList_InsertSortedInEmpty_FirstLastEqual )
                {
                    DoubleLinkedList<double> l;

                    l.InsertNodeSorted( 12.4 );

                    Assert::AreEqual( l.GetFirstNode(), l.GetLastNode() );
                }


                /**
                 *  Tests DoubleLinkedList::Find in a list with only one element.
                 *
                 *  Checks that the first node and the result of find on the value of the only node
                 *  are the same.
                 */
                TEST_METHOD( DoubleLinkedList_TestFindWithOneElement_FindsNode )
                {
                    DoubleLinkedList<double> l;

                    l.InsertNodeSorted( 54.12 );

                    Assert::AreEqual( l.GetFirstNode(), l.Find( 54.12 ) );
                }


                /**
                 *  Tests DoubleLinkedList::Find in a list with only one element.
                 *
                 *  Checks that the result of find on a node that should't exist is nullptr.
                 */
                TEST_METHOD( DoubleLinkedList_TestFindWithOneElement_NotFindingBogusNode )
                {
                    DoubleLinkedList<double> l;

                    l.InsertNodeSorted( 54.12 );

                    Assert::IsNull( l.Find( 12.43 ) );
                }


                /**
                 *  Tests DoubleLinkedList::Find in a list with multiple elements.
                 *
                 *  Checks that the first and the last node are not the same.
                 */
                TEST_METHOD( DoubleLinkedList_TestFindWithMultipleElements_FirstLastNotEqual )
                {
                    DoubleLinkedList<double> l;

                    l.InsertNodeSorted( 1 );
                    l.InsertNodeSorted( 2 );
                    l.InsertNodeSorted( 3 );

                    Assert::AreNotEqual( l.GetFirstNode(), l.GetLastNode(), L"First and last node can't be the same in list with multiple nodes.", LINE_INFO() );
                }


                /**
                 *  Tests DoubleLinkedList::Find in a list with multiple elements.
                 *
                 *  Checks that the result of find on a value known to exist in the list doesn't
                 *  return nullptr.
                 */
                TEST_METHOD( DoubleLinkedList_TestFindWithMultipleElements_KnownValueFound )
                {
                    DoubleLinkedList<double> l;

                    l.InsertNodeSorted( 1 );
                    l.InsertNodeSorted( 2 );
                    l.InsertNodeSorted( 3 );

                    Assert::IsNotNull( l.Find( 2 ) );
                }


                /**
                 *  Tests insertion of node at the end of a list with a single node.
                 *
                 *  Checks that the first node isn't the nullptr.
                 */
                TEST_METHOD( DoubleLinkedList_InsertSortedLastWithOneNode_HeadNotNull )
                {
                    DoubleLinkedList<double> l;

                    l.InsertNodeSorted( 12.4 );
                    l.InsertNodeSorted( 13.3 );

                    Assert::IsNotNull( l.GetFirstNode(), L"Head (first) node shouldn't be null after inserting a new node.", LINE_INFO() );
                }


                /**
                 *  Tests insertion of node at the end of a list with a single node.
                 *
                 *  Checks that the last node isn't the nullptr.
                 */
                TEST_METHOD( DoubleLinkedList_InsertSortedLastWithOneNode_TailNotNull )
                {
                    DoubleLinkedList<double> l;

                    l.InsertNodeSorted( 12.4 );
                    l.InsertNodeSorted( 13.3 );

                    Assert::IsNotNull( l.GetLastNode() );
                }


                /**
                 *  Tests insertion of node at the end of a list with a single node.
                 *
                 *  Checks that the first and last node isn't the same.
                 */
                TEST_METHOD( DoubleLinkedList_InsertSortedLastWithOneNode_HeadTailDiffers )
                {
                    DoubleLinkedList<double> l;

                    l.InsertNodeSorted( 12.4 );
                    l.InsertNodeSorted( 13.3 );

                    Assert::AreNotEqual( l.GetFirstNode(), l.GetLastNode() );
                }


                /**
                 *  Tests insertion of node at the end of a list with a single node.
                 *
                 *  Checks that the first node have the expected value.
                 */
                TEST_METHOD( DoubleLinkedList_InsertSortedLastWithOneNode_HeadCorrectValue )
                {
                    DoubleLinkedList<double> l;

                    l.InsertNodeSorted( 12.4 );
                    l.InsertNodeSorted( 13.3 );

                    Assert::AreEqual( l.Find( 13.3 ), l.GetFirstNode() );
                }


                /**
                 *  Tests insertion of node at the end of a list with a single node.
                 *
                 *  Checks that the first node isn't inserted in ascending order.
                 */
                TEST_METHOD( DoubleLinkedList_InsertSortedLastWithOneNode_HeadWrongValue )
                {
                    DoubleLinkedList<double> l;

                    l.InsertNodeSorted( 12.4 );
                    l.InsertNodeSorted( 13.3 );

                    Assert::AreNotEqual( l.Find( 12.4 ), l.GetFirstNode() );
                }


                /**
                 *  Tests insertion of node at the end of a list with a single node.
                 *
                 *  Checks that the last node have the expected value.
                 */
                TEST_METHOD( DoubleLinkedList_InsertSortedLastWithOneNode_TailCorrectValue )
                {
                    DoubleLinkedList<double> l;

                    l.InsertNodeSorted( 12.4 );
                    l.InsertNodeSorted( 13.3 );

                    Assert::AreEqual( l.Find( 12.4 ), l.GetLastNode() );
                }


                /**
                 *  Tests insertion of node at the end of a list with a single node.
                 *
                 *  Checks that the last node isn't in ascending order
                 */
                TEST_METHOD( DoubleLinkedList_InsertSortedLastWithOneNode_TailWrongValue )
                {
                    DoubleLinkedList<double> l;

                    l.InsertNodeSorted( 12.4 );
                    l.InsertNodeSorted( 13.3 );

                    Assert::AreNotEqual( l.Find( 13.3 ), l.GetLastNode() );
                }


                /**
                 *  Test insertion of multiple nodes.
                 *
                 *  Checks that the first node is the expected node.
                 */
                TEST_METHOD( DoubleLinkedList_TestInsertMultipleNodes_HeadCorrect )
                {
                    DoubleLinkedList<double> l;

                    DoubleLinkedList<double>::Node *firstNode = new DoubleLinkedList<double>::Node( 6 );
                    DoubleLinkedList<double>::Node *middleNode = new DoubleLinkedList<double>::Node( 3 );
                    DoubleLinkedList<double>::Node *lastNode = new DoubleLinkedList<double>::Node( 2 );

                    l.InsertNodeSorted( middleNode );
                    l.InsertNodeSorted( firstNode );
                    l.InsertNodeSorted( lastNode );

                    Assert::AreEqual( l.Find( 6 ), l.GetFirstNode() );
                }


                /**
                 *  Test insertion of multiple nodes.
                 *
                 *  Checks that the last node is the expected node.
                 */
                TEST_METHOD( DoubleLinkedList_TestInsertMultipleNodes_TailCorrect )
                {
                    DoubleLinkedList<double> l;

                    DoubleLinkedList<double>::Node *firstNode = new DoubleLinkedList<double>::Node( 6 );
                    DoubleLinkedList<double>::Node *middleNode = new DoubleLinkedList<double>::Node( 3 );
                    DoubleLinkedList<double>::Node *lastNode = new DoubleLinkedList<double>::Node( 2 );

                    l.InsertNodeSorted( middleNode );
                    l.InsertNodeSorted( firstNode );
                    l.InsertNodeSorted( lastNode );

                    Assert::AreEqual( l.Find( 2 ), l.GetLastNode() );
                }


                /**
                 *  Test insertion of multiple values.
                 *
                 *  Checks that the first node have the expected value.
                 */
                TEST_METHOD( DoubleLinkedList_TestInsertMultipleValues_HeadCorrect )
                {
                    DoubleLinkedList<double> l;

                    l.InsertNodeSorted( 3 );
                    l.InsertNodeSorted( 2 );
                    l.InsertNodeSorted( 6 );

                    Assert::AreEqual( l.Find( 6 ), l.GetFirstNode() );
                }


                /**
                 *  Test insertion of multiple values.
                 *
                 *  Checks that the last node have the expected value.
                 */
                TEST_METHOD( DoubleLinkedList_TestInsertMultipleValues_TailCorrect )
                {
                    DoubleLinkedList<double> l;

                    l.InsertNodeSorted( 3 );
                    l.InsertNodeSorted( 2 );
                    l.InsertNodeSorted( 6 );

                    Assert::AreEqual( l.Find( 2 ), l.GetLastNode() );
                }


                /**
                 *  Tests deletion of the tail node in a list.
                 *
                 *  Checks that the first node is the expected node.
                 */
                TEST_METHOD( DoubleLinkedList_TestDeleteTailNode_HeadNodeCorrect )
                {
                    DoubleLinkedList<double> l;

                    DoubleLinkedList<double>::Node *firstNode = new DoubleLinkedList<double>::Node( 6 );
                    DoubleLinkedList<double>::Node *middleNode = new DoubleLinkedList<double>::Node( 3 );
                    DoubleLinkedList<double>::Node *lastNode = new DoubleLinkedList<double>::Node( 2 );

                    l.InsertNodeSorted( firstNode );
                    l.InsertNodeSorted( middleNode );
                    l.InsertNodeSorted( lastNode );
                    
                    l.DeleteNode( lastNode );

                    Assert::AreEqual( firstNode, l.GetFirstNode() );
                }


                /**
                 *  Tests deletion of the tail node in a list.
                 *
                 *  Checks that the last node is the expected node.
                 */
                TEST_METHOD( DoubleLinkedList_TestDeleteTailNode_TailNodeCorrect )
                {
                    DoubleLinkedList<double> l;

                    DoubleLinkedList<double>::Node *firstNode = new DoubleLinkedList<double>::Node( 6 );
                    DoubleLinkedList<double>::Node *middleNode = new DoubleLinkedList<double>::Node( 3 );
                    DoubleLinkedList<double>::Node *lastNode = new DoubleLinkedList<double>::Node( 2 );

                    l.InsertNodeSorted( firstNode );
                    l.InsertNodeSorted( middleNode );
                    l.InsertNodeSorted( lastNode );
                    
                    l.DeleteNode( lastNode );

                    Assert::AreEqual( middleNode, l.GetLastNode() );
                }


                /**
                 *  Tests deletion of the head node in a list.
                 *
                 *  Checks that the first node is the expected node.
                 */
                TEST_METHOD( DoubleLinkedList_TestDeleteHeadNode_HeadNodeCorrect )
                {
                    DoubleLinkedList<double> l;

                    DoubleLinkedList<double>::Node *firstNode = new DoubleLinkedList<double>::Node( 6 );
                    DoubleLinkedList<double>::Node *middleNode = new DoubleLinkedList<double>::Node( 3 );
                    DoubleLinkedList<double>::Node *lastNode = new DoubleLinkedList<double>::Node( 2 );

                    l.InsertNodeSorted( firstNode );
                    l.InsertNodeSorted( middleNode );
                    l.InsertNodeSorted( lastNode );
                    
                    l.DeleteNode( firstNode );

                    Assert::AreEqual( middleNode, l.GetFirstNode() );
                }


                /**
                 *  Tests deletion of the head node in a list.
                 *
                 *  Checks that the last node is the expected node.
                 */
                TEST_METHOD( DoubleLinkedList_TestDeleteHeadNode_TailNodeCorrect )
                {
                    DoubleLinkedList<double> l;

                    DoubleLinkedList<double>::Node *firstNode = new DoubleLinkedList<double>::Node( 6 );
                    DoubleLinkedList<double>::Node *middleNode = new DoubleLinkedList<double>::Node( 3 );
                    DoubleLinkedList<double>::Node *lastNode = new DoubleLinkedList<double>::Node( 2 );

                    l.InsertNodeSorted( firstNode );
                    l.InsertNodeSorted( middleNode );
                    l.InsertNodeSorted( lastNode );
                    
                    l.DeleteNode( firstNode );

                    Assert::AreEqual( middleNode, l.GetFirstNode() );
                    Assert::AreEqual( lastNode, l.GetLastNode() );
                }


                /**
                 *  Tests removal of tail value in a list.
                 *
                 *  Checks that the first node have the expected value.
                 */
                TEST_METHOD( DoubleLinkedList_TestDeleteTailValue_HeadValueCorrect )
                {
                    DoubleLinkedList<double> l;

                    DoubleLinkedList<double>::Node *firstNode = new DoubleLinkedList<double>::Node( 6 );
                    DoubleLinkedList<double>::Node *middleNode = new DoubleLinkedList<double>::Node( 3 );
                    DoubleLinkedList<double>::Node *lastNode = new DoubleLinkedList<double>::Node( 2 );

                    l.InsertNodeSorted( firstNode );
                    l.InsertNodeSorted( middleNode );
                    l.InsertNodeSorted( lastNode );

                    l.DeleteNode( 2 );

                    Assert::AreEqual( firstNode, l.GetFirstNode() );
                }


                /**
                 *  Tests removal of tail value in a list.
                 *
                 *  Checks that the last node have the expected value.
                 */
                TEST_METHOD( DoubleLinkedList_TestDeleteTailValue_TailValueCorrect )
                {
                    DoubleLinkedList<double> l;

                    DoubleLinkedList<double>::Node *firstNode = new DoubleLinkedList<double>::Node( 6 );
                    DoubleLinkedList<double>::Node *middleNode = new DoubleLinkedList<double>::Node( 3 );
                    DoubleLinkedList<double>::Node *lastNode = new DoubleLinkedList<double>::Node( 2 );

                    l.InsertNodeSorted( firstNode );
                    l.InsertNodeSorted( middleNode );
                    l.InsertNodeSorted( lastNode );

                    l.DeleteNode( 2 );

                    Assert::AreEqual( middleNode, l.GetLastNode() );
                }


                /**
                 *  Tests removal of head value in a list.
                 *
                 *  Checks that the fist node have the expected value.
                 */
                TEST_METHOD( DoubleLinkedList_TestDeleteHeadValue_HeadValueCorrect )
                {
                    DoubleLinkedList<double> l;

                    DoubleLinkedList<double>::Node *firstNode = new DoubleLinkedList<double>::Node( 6 );
                    DoubleLinkedList<double>::Node *middleNode = new DoubleLinkedList<double>::Node( 3 );
                    DoubleLinkedList<double>::Node *lastNode = new DoubleLinkedList<double>::Node( 2 );

                    l.InsertNodeSorted( firstNode );
                    l.InsertNodeSorted( middleNode );
                    l.InsertNodeSorted( lastNode );

                    l.DeleteNode( 6 );

                    Assert::AreEqual( middleNode, l.GetFirstNode() );
                }


                /**
                 *  Tests removal of head value in a list.
                 *
                 *  Checks that the last node have the expected value.
                 */
                TEST_METHOD( DoubleLinkedList_TestDeleteHeadValue_TailValueCorrect )
                {
                    DoubleLinkedList<double> l;

                    DoubleLinkedList<double>::Node *firstNode = new DoubleLinkedList<double>::Node( 6 );
                    DoubleLinkedList<double>::Node *middleNode = new DoubleLinkedList<double>::Node( 3 );
                    DoubleLinkedList<double>::Node *lastNode = new DoubleLinkedList<double>::Node( 2 );

                    l.InsertNodeSorted( firstNode );
                    l.InsertNodeSorted( middleNode );
                    l.InsertNodeSorted( lastNode );

                    l.DeleteNode( 6 );

                    Assert::AreEqual( lastNode, l.GetLastNode() );
                }


                /**
                 *  Test removal of last node in list.
                 *
                 *  Checks that the first node is the nullptr.
                 */
                TEST_METHOD( DoubleLinkedList_TestDeleteLastNode_HeadNodeCorrect )
                {
                    DoubleLinkedList<double> l;

                    DoubleLinkedList<double>::Node *firstNode = new DoubleLinkedList<double>::Node( 6 );

                    l.InsertNodeSorted( firstNode );

                    l.DeleteNode( 6 );

                    Assert::IsNull( l.GetFirstNode() );
                }


                /**
                 *  Test removal of last node in list.
                 *
                 *  Checks that the last node is the nullptr.
                 */
                TEST_METHOD( DoubleLinkedList_TestDeleteLastNode_TailNodeCorrect )
                {
                    DoubleLinkedList<double> l;

                    DoubleLinkedList<double>::Node *firstNode = new DoubleLinkedList<double>::Node( 6 );

                    l.InsertNodeSorted( firstNode );

                    l.DeleteNode( 6 );

                    Assert::IsNull( l.GetFirstNode() );
                }
                

                /**
                 *  Tests removal of last node in list and then adding a new node.
                 *
                 *  Checks that the new node is the first node.
                 */
                TEST_METHOD( DoubleLinkedList_TestDeleteLastAndInsert_HeadNodeCorrect )
                {
                    DoubleLinkedList<double> l;

                    DoubleLinkedList<double>::Node *firstNode = new DoubleLinkedList<double>::Node( 6 );
                    DoubleLinkedList<double>::Node newNode( 12 );

                    l.InsertNodeSorted( firstNode );
                    l.DeleteNode( 6 );
                    l.InsertNodeSorted( &newNode );

                    Assert::AreEqual( &newNode, l.GetFirstNode() );
                }
                

                /**
                 *  Tests removal of last node in list and then adding a new node.
                 *
                 *  Checks that the new node is the last node.
                 */
                TEST_METHOD( DoubleLinkedList_TestDeleteLastAndInsert_TailNodeCorrect )
                {
                    DoubleLinkedList<double> l;

                    DoubleLinkedList<double>::Node *firstNode = new DoubleLinkedList<double>::Node( 6 );
                    DoubleLinkedList<double>::Node newNode( 12 );

                    l.InsertNodeSorted( firstNode );
                    l.DeleteNode( 6 );
                    l.InsertNodeSorted( &newNode );

                    Assert::AreEqual( &newNode, l.GetLastNode() );
                }
    };
}


namespace Microsoft
{
    namespace VisualStudio
    {
        namespace CppUnitTestFramework
        {
            template<> static std::wstring ToString<DoubleLinkedList<double>::Node>( class DoubleLinkedList<double>::Node *t )
            {
                RETURN_WIDE_STRING( t );
            }
        }
    }
}
