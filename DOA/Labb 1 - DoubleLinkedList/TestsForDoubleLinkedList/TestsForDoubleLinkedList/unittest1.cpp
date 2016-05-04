#include "stdafx.h"
#include "CppUnitTest.h"

#include "Classes/DoubleLinkedList.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CU = CommonUtilities;

namespace TestsForDoubleLinkedList
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(CreateLinkedList)
		{
			CU::DoubleLinkedList<int> testLinkedList;
		}

		TEST_METHOD(GetFirst)
		{
			CU::DoubleLinkedList<int> testLinkedList;

			CU::DoubleLinkedList<int>::Node * tempTestNode;			

			tempTestNode = testLinkedList.GetFirstNode();

			Assert::IsNull(tempTestNode);
		}

		TEST_METHOD(GetLast)
		{
			CU::DoubleLinkedList<int> testLinkedList;

			CU::DoubleLinkedList<int>::Node * tempTestNode;

			tempTestNode = testLinkedList.GetLastNode();

			Assert::IsNull(tempTestNode);
		}

		TEST_METHOD(InsertNodeAfterAtNull)
		{
			CU::DoubleLinkedList<int> testLinkedList;

			CU::DoubleLinkedList<int>::Node * tempTestNode = new CU::DoubleLinkedList<int>::Node(*new int(1));

			testLinkedList.InsertNodeAfterNode(nullptr, tempTestNode);

			Assert::IsTrue(tempTestNode == testLinkedList.GetLastNode());
		}

		TEST_METHOD(InsertNodeBeforeAtNull)
		{
			CU::DoubleLinkedList<int> testLinkedList;

			CU::DoubleLinkedList<int>::Node * tempTestNode = new CU::DoubleLinkedList<int>::Node(*new int(1));

			testLinkedList.InsertNodeBeforeNode(nullptr, tempTestNode);

			Assert::IsTrue(tempTestNode == testLinkedList.GetFirstNode());
		}

		TEST_METHOD(InsertNodeAfterAnotherNode)
		{
			CU::DoubleLinkedList<int> testLinkedList;

			CU::DoubleLinkedList<int>::Node * tempTestNode1 = new CU::DoubleLinkedList<int>::Node(*new int(1));
			CU::DoubleLinkedList<int>::Node * tempTestNode2 = new CU::DoubleLinkedList<int>::Node(*new int(2));

			testLinkedList.InsertNodeAfterNode(nullptr, tempTestNode1);
			testLinkedList.InsertNodeAfterNode(tempTestNode1, tempTestNode2);

			Assert::IsTrue(tempTestNode1 == testLinkedList.GetFirstNode());
			Assert::IsTrue(tempTestNode2 == testLinkedList.GetFirstNode()->myNext);
		}

		TEST_METHOD(InsertNodeBeforeAnotherNode)
		{
			CU::DoubleLinkedList<int> testLinkedList;

			CU::DoubleLinkedList<int>::Node * tempTestNode1 = new CU::DoubleLinkedList<int>::Node(*new int(1));
			CU::DoubleLinkedList<int>::Node * tempTestNode2 = new CU::DoubleLinkedList<int>::Node(*new int(2));

			testLinkedList.InsertNodeBeforeNode(nullptr, tempTestNode1);
			testLinkedList.InsertNodeBeforeNode(tempTestNode1, tempTestNode2);

			Assert::IsTrue(tempTestNode2 == testLinkedList.GetFirstNode());
		}

		TEST_METHOD(InsertNodeAfterAnotherNodeMoreNodes)
		{
			CU::DoubleLinkedList<int> testLinkedList;

			CU::DoubleLinkedList<int>::Node * tempTestNode1 = new CU::DoubleLinkedList<int>::Node(*new int(1));
			CU::DoubleLinkedList<int>::Node * tempTestNode2 = new CU::DoubleLinkedList<int>::Node(*new int(2));
			CU::DoubleLinkedList<int>::Node * tempTestNode3 = new CU::DoubleLinkedList<int>::Node(*new int(3));
			CU::DoubleLinkedList<int>::Node * tempTestNode4 = new CU::DoubleLinkedList<int>::Node(*new int(4));
			CU::DoubleLinkedList<int>::Node * tempTestNode5 = new CU::DoubleLinkedList<int>::Node(*new int(5));

			testLinkedList.InsertNodeAfterNode(nullptr, tempTestNode1);
			testLinkedList.InsertNodeAfterNode(tempTestNode1, tempTestNode2);
			testLinkedList.InsertNodeAfterNode(tempTestNode2, tempTestNode3);
			testLinkedList.InsertNodeAfterNode(tempTestNode3, tempTestNode4);
			testLinkedList.InsertNodeAfterNode(tempTestNode4, tempTestNode5);

			Assert::IsTrue(tempTestNode1 == testLinkedList.GetFirstNode());
			Assert::IsTrue(tempTestNode2 == testLinkedList.GetFirstNode()->myNext);
			Assert::IsTrue(tempTestNode3 == testLinkedList.GetFirstNode()->myNext->myNext);
			Assert::IsTrue(tempTestNode4 == testLinkedList.GetFirstNode()->myNext->myNext->myNext);
			Assert::IsTrue(tempTestNode5 == testLinkedList.GetFirstNode()->myNext->myNext->myNext->myNext);
			Assert::IsTrue(nullptr == testLinkedList.GetFirstNode()->myNext->myNext->myNext->myNext->myNext);

			Assert::IsTrue(tempTestNode1->myPrev == nullptr);
			Assert::IsTrue(tempTestNode2->myPrev == tempTestNode1);
			Assert::IsTrue(tempTestNode3->myPrev == tempTestNode2);
			Assert::IsTrue(tempTestNode4->myPrev == tempTestNode3);
			Assert::IsTrue(tempTestNode5->myPrev == tempTestNode4);
		}

		TEST_METHOD(InsertNodeBeforeAnotherNodeMoreNodes)
		{
			CU::DoubleLinkedList<int> testLinkedList;

			CU::DoubleLinkedList<int>::Node * tempTestNode1 = new CU::DoubleLinkedList<int>::Node(*new int(1));
			CU::DoubleLinkedList<int>::Node * tempTestNode2 = new CU::DoubleLinkedList<int>::Node(*new int(2));
			CU::DoubleLinkedList<int>::Node * tempTestNode3 = new CU::DoubleLinkedList<int>::Node(*new int(3));
			CU::DoubleLinkedList<int>::Node * tempTestNode4 = new CU::DoubleLinkedList<int>::Node(*new int(4));
			CU::DoubleLinkedList<int>::Node * tempTestNode5 = new CU::DoubleLinkedList<int>::Node(*new int(5));

			testLinkedList.InsertNodeAfterNode(nullptr, tempTestNode1);
			testLinkedList.InsertNodeBeforeNode(tempTestNode1, tempTestNode2);
			testLinkedList.InsertNodeBeforeNode(tempTestNode2, tempTestNode3);
			testLinkedList.InsertNodeBeforeNode(tempTestNode3, tempTestNode4);
			testLinkedList.InsertNodeBeforeNode(tempTestNode4, tempTestNode5);

			Assert::IsTrue(tempTestNode5 == testLinkedList.GetFirstNode());
			Assert::IsTrue(tempTestNode4 == testLinkedList.GetFirstNode()->myNext);
			Assert::IsTrue(tempTestNode3 == testLinkedList.GetFirstNode()->myNext->myNext);
			Assert::IsTrue(tempTestNode2 == testLinkedList.GetFirstNode()->myNext->myNext->myNext);
			Assert::IsTrue(tempTestNode1 == testLinkedList.GetFirstNode()->myNext->myNext->myNext->myNext);
			Assert::IsTrue(nullptr == testLinkedList.GetFirstNode()->myNext->myNext->myNext->myNext->myNext);

			Assert::IsTrue(tempTestNode5->myPrev == nullptr);
			Assert::IsTrue(tempTestNode4->myPrev == tempTestNode5);
			Assert::IsTrue(tempTestNode3->myPrev == tempTestNode4);
			Assert::IsTrue(tempTestNode2->myPrev == tempTestNode3);
			Assert::IsTrue(tempTestNode1->myPrev == tempTestNode2);
		}

		TEST_METHOD(AccessNodeData)
		{
			CU::DoubleLinkedList<int> testLinkedList;

			CU::DoubleLinkedList<int>::Node * tempTestNode1 = new CU::DoubleLinkedList<int>::Node(*new int(1));
			CU::DoubleLinkedList<int>::Node * tempTestNode2 = new CU::DoubleLinkedList<int>::Node(*new int(2));

			testLinkedList.InsertNodeAfterNode(nullptr, tempTestNode1);
			testLinkedList.InsertNodeBeforeNode(tempTestNode1, tempTestNode2);

			Assert::AreEqual(testLinkedList.GetFirstNode()->myData, 2);
			Assert::AreEqual(testLinkedList.GetFirstNode()->myNext->myData, 1);
		}

		TEST_METHOD(FindNodeDataAndSucced)
		{
			CU::DoubleLinkedList<int> testLinkedList;

			CU::DoubleLinkedList<int>::Node * tempTestNode1 = new CU::DoubleLinkedList<int>::Node(*new int(1));
			CU::DoubleLinkedList<int>::Node * tempTestNode2 = new CU::DoubleLinkedList<int>::Node(*new int(2));
			CU::DoubleLinkedList<int>::Node * tempTestNode3 = new CU::DoubleLinkedList<int>::Node(*new int(3));
			CU::DoubleLinkedList<int>::Node * tempTestNode4 = new CU::DoubleLinkedList<int>::Node(*new int(4));
			CU::DoubleLinkedList<int>::Node * tempTestNode5 = new CU::DoubleLinkedList<int>::Node(*new int(5));

			testLinkedList.InsertNodeAfterNode(nullptr, tempTestNode1);
			testLinkedList.InsertNodeBeforeNode(tempTestNode1, tempTestNode2);
			testLinkedList.InsertNodeBeforeNode(tempTestNode2, tempTestNode3);
			testLinkedList.InsertNodeBeforeNode(tempTestNode3, tempTestNode4);
			testLinkedList.InsertNodeBeforeNode(tempTestNode4, tempTestNode5);

			int IWantToBeATree = testLinkedList.Find(3)->myData;

			Assert::AreEqual(IWantToBeATree, 3);
		}

		TEST_METHOD(FindNodeDataAndFail)
		{
			CU::DoubleLinkedList<int> testLinkedList;

			CU::DoubleLinkedList<int>::Node * tempTestNode1 = new CU::DoubleLinkedList<int>::Node(*new int(1));
			CU::DoubleLinkedList<int>::Node * tempTestNode2 = new CU::DoubleLinkedList<int>::Node(*new int(2));
			CU::DoubleLinkedList<int>::Node * tempTestNode3 = new CU::DoubleLinkedList<int>::Node(*new int(3));
			CU::DoubleLinkedList<int>::Node * tempTestNode4 = new CU::DoubleLinkedList<int>::Node(*new int(4));
			CU::DoubleLinkedList<int>::Node * tempTestNode5 = new CU::DoubleLinkedList<int>::Node(*new int(5));

			testLinkedList.InsertNodeAfterNode(nullptr, tempTestNode1);
			testLinkedList.InsertNodeBeforeNode(tempTestNode1, tempTestNode2);
			testLinkedList.InsertNodeBeforeNode(tempTestNode2, tempTestNode3);
			testLinkedList.InsertNodeBeforeNode(tempTestNode3, tempTestNode4);
			testLinkedList.InsertNodeBeforeNode(tempTestNode4, tempTestNode5);

			CU::DoubleLinkedList<int>::Node * findResult = testLinkedList.Find(8);

			Assert::IsNull(findResult);
		}

		TEST_METHOD(InsertSortedNode)
		{
			CU::DoubleLinkedList<int> testLinkedList;

			CU::DoubleLinkedList<int>::Node * tempTestNode1 = new CU::DoubleLinkedList<int>::Node(*new int(1));

			testLinkedList.InsertNodeSorted(tempTestNode1);

			Assert::IsTrue(testLinkedList.GetFirstNode() == tempTestNode1);
			Assert::IsTrue(testLinkedList.GetLastNode() == tempTestNode1);
		}

		TEST_METHOD(InsertSortedNodeLotsOfNodes)
		{
			CU::DoubleLinkedList<int> testLinkedList;

			CU::DoubleLinkedList<int>::Node * tempTestNode1 = new CU::DoubleLinkedList<int>::Node(*new int(1));
			CU::DoubleLinkedList<int>::Node * tempTestNode2 = new CU::DoubleLinkedList<int>::Node(*new int(2));
			CU::DoubleLinkedList<int>::Node * tempTestNode3 = new CU::DoubleLinkedList<int>::Node(*new int(3));
			CU::DoubleLinkedList<int>::Node * tempTestNode4 = new CU::DoubleLinkedList<int>::Node(*new int(4));
			CU::DoubleLinkedList<int>::Node * tempTestNode5 = new CU::DoubleLinkedList<int>::Node(*new int(5));
			CU::DoubleLinkedList<int>::Node * tempTestNode6 = new CU::DoubleLinkedList<int>::Node(*new int(6));
			CU::DoubleLinkedList<int>::Node * tempTestNode7 = new CU::DoubleLinkedList<int>::Node(*new int(7));
			CU::DoubleLinkedList<int>::Node * tempTestNode8 = new CU::DoubleLinkedList<int>::Node(*new int(8));
			CU::DoubleLinkedList<int>::Node * tempTestNode9 = new CU::DoubleLinkedList<int>::Node(*new int(9));
			CU::DoubleLinkedList<int>::Node * tempTestNode10 = new CU::DoubleLinkedList<int>::Node(*new int(10));

			testLinkedList.InsertNodeSorted(tempTestNode9);
			testLinkedList.InsertNodeSorted(tempTestNode4);
			testLinkedList.InsertNodeSorted(tempTestNode3);
			testLinkedList.InsertNodeSorted(tempTestNode8);
			testLinkedList.InsertNodeSorted(tempTestNode5);
			testLinkedList.InsertNodeSorted(tempTestNode6);
			testLinkedList.InsertNodeSorted(tempTestNode10);
			testLinkedList.InsertNodeSorted(tempTestNode2);
			testLinkedList.InsertNodeSorted(tempTestNode1);
			testLinkedList.InsertNodeSorted(tempTestNode7);

			CU::DoubleLinkedList<int>::Node * TestNode = testLinkedList.GetFirstNode();

			for (int iTest = 10; iTest > 0; --iTest)
			{
				Assert::AreEqual(iTest, TestNode->myData);
				TestNode = TestNode->myNext;
			}
		}

		TEST_METHOD(InsertSortedNodeLotsOfValues)
		{
			CU::DoubleLinkedList<int> testLinkedList;


			testLinkedList.InsertNodeSorted(9);
			testLinkedList.InsertNodeSorted(3);
			testLinkedList.InsertNodeSorted(10);
			testLinkedList.InsertNodeSorted(4);
			testLinkedList.InsertNodeSorted(5);
			testLinkedList.InsertNodeSorted(7);
			testLinkedList.InsertNodeSorted(6);
			testLinkedList.InsertNodeSorted(8);
			testLinkedList.InsertNodeSorted(1);
			testLinkedList.InsertNodeSorted(2);

			CU::DoubleLinkedList<int>::Node * TestNode = testLinkedList.GetFirstNode();

			for (int iTest = 10; iTest > 0; --iTest)
			{
				Assert::AreEqual(iTest, TestNode->myData);
				TestNode = TestNode->myNext;
			}
		}

		TEST_METHOD(InsertSortedNodeLotsOfValuesNotSequenual)
		{
			CU::DoubleLinkedList<int> testLinkedList;


			testLinkedList.InsertNodeSorted(101);
			testLinkedList.InsertNodeSorted(3);
			testLinkedList.InsertNodeSorted(102);
			testLinkedList.InsertNodeSorted(3);
			testLinkedList.InsertNodeSorted(254);
			testLinkedList.InsertNodeSorted(50);
			testLinkedList.InsertNodeSorted(530);
			testLinkedList.InsertNodeSorted(254);
			

			CU::DoubleLinkedList<int>::Node * TestNode = testLinkedList.GetFirstNode();

			Assert::AreEqual(TestNode->myData, 530);
			TestNode = TestNode->myNext;

			Assert::AreEqual(TestNode->myData, 254);
			TestNode = TestNode->myNext;

			Assert::AreEqual(TestNode->myData, 254);
			TestNode = TestNode->myNext;

			Assert::AreEqual(TestNode->myData, 102);
			TestNode = TestNode->myNext;

			Assert::AreEqual(TestNode->myData, 101);
			TestNode = TestNode->myNext;

			Assert::AreEqual(TestNode->myData, 50);
			TestNode = TestNode->myNext;

			Assert::AreEqual(TestNode->myData, 3);
			TestNode = TestNode->myNext;

			Assert::AreEqual(TestNode->myData, 3);
			TestNode = TestNode->myNext;
		}

		TEST_METHOD(DeleteWithNode)
		{
			CU::DoubleLinkedList<int> testLinkedList;

			CU::DoubleLinkedList<int>::Node * tempTestNode1 = new CU::DoubleLinkedList<int>::Node(*new int(1));
			CU::DoubleLinkedList<int>::Node * tempTestNode2 = new CU::DoubleLinkedList<int>::Node(*new int(2));
			CU::DoubleLinkedList<int>::Node * tempTestNode3 = new CU::DoubleLinkedList<int>::Node(*new int(3));
			CU::DoubleLinkedList<int>::Node * tempTestNode4 = new CU::DoubleLinkedList<int>::Node(*new int(4));
			CU::DoubleLinkedList<int>::Node * tempTestNode5 = new CU::DoubleLinkedList<int>::Node(*new int(5));

			testLinkedList.InsertNodeAfterNode(nullptr, tempTestNode1);
			testLinkedList.InsertNodeBeforeNode(tempTestNode1, tempTestNode2);
			testLinkedList.InsertNodeBeforeNode(tempTestNode2, tempTestNode3);
			testLinkedList.InsertNodeBeforeNode(tempTestNode3, tempTestNode4);
			testLinkedList.InsertNodeBeforeNode(tempTestNode4, tempTestNode5);

			testLinkedList.DeleteNode(tempTestNode3);

			Assert::IsNull(testLinkedList.Find(3));
		}

		TEST_METHOD(DeleteWithNodeOrderIsIntact)
		{
			CU::DoubleLinkedList<int> testLinkedList;

			CU::DoubleLinkedList<int>::Node * tempTestNode1 = new CU::DoubleLinkedList<int>::Node(*new int(1));
			CU::DoubleLinkedList<int>::Node * tempTestNode2 = new CU::DoubleLinkedList<int>::Node(*new int(2));
			CU::DoubleLinkedList<int>::Node * tempTestNode3 = new CU::DoubleLinkedList<int>::Node(*new int(3));
			CU::DoubleLinkedList<int>::Node * tempTestNode4 = new CU::DoubleLinkedList<int>::Node(*new int(4));
			CU::DoubleLinkedList<int>::Node * tempTestNode5 = new CU::DoubleLinkedList<int>::Node(*new int(5));
			CU::DoubleLinkedList<int>::Node * tempTestNode6 = new CU::DoubleLinkedList<int>::Node(*new int(6));
			CU::DoubleLinkedList<int>::Node * tempTestNode7 = new CU::DoubleLinkedList<int>::Node(*new int(7));
			CU::DoubleLinkedList<int>::Node * tempTestNode8 = new CU::DoubleLinkedList<int>::Node(*new int(8));
			CU::DoubleLinkedList<int>::Node * tempTestNode9 = new CU::DoubleLinkedList<int>::Node(*new int(9));
			CU::DoubleLinkedList<int>::Node * tempTestNode10 = new CU::DoubleLinkedList<int>::Node(*new int(10));

			testLinkedList.InsertNodeSorted(tempTestNode9);
			testLinkedList.InsertNodeSorted(tempTestNode4);
			testLinkedList.InsertNodeSorted(tempTestNode3);
			testLinkedList.InsertNodeSorted(tempTestNode8);
			testLinkedList.InsertNodeSorted(tempTestNode5);
			testLinkedList.InsertNodeSorted(tempTestNode6);
			testLinkedList.InsertNodeSorted(tempTestNode10);
			testLinkedList.InsertNodeSorted(tempTestNode2);
			testLinkedList.InsertNodeSorted(tempTestNode1);
			testLinkedList.InsertNodeSorted(tempTestNode7);

			testLinkedList.DeleteNode(tempTestNode5);

			CU::DoubleLinkedList<int>::Node * TestNode = testLinkedList.GetFirstNode();

			for (int iTest = 10; iTest > 0; --iTest)
			{
				if (iTest != 5)
				{
					Assert::AreEqual(iTest, TestNode->myData);
					TestNode = TestNode->myNext;
				}
			}

			TestNode = testLinkedList.GetFirstNode();

			for (int iTest = 10; iTest > 0; --iTest)
			{
				if (iTest != 5)
				{
					Assert::AreEqual(iTest, TestNode->myData);
					TestNode = TestNode->myNext;
				}
				else
				{
					Assert::AreNotEqual(iTest, TestNode->myData);
				}
			}
			
		}

		TEST_METHOD(DeleteWithValueOrderIsIntact)
		{
			CU::DoubleLinkedList<int> testLinkedList;

			CU::DoubleLinkedList<int>::Node * tempTestNode1 = new CU::DoubleLinkedList<int>::Node(*new int(1));
			CU::DoubleLinkedList<int>::Node * tempTestNode2 = new CU::DoubleLinkedList<int>::Node(*new int(2));
			CU::DoubleLinkedList<int>::Node * tempTestNode3 = new CU::DoubleLinkedList<int>::Node(*new int(3));
			CU::DoubleLinkedList<int>::Node * tempTestNode4 = new CU::DoubleLinkedList<int>::Node(*new int(4));
			CU::DoubleLinkedList<int>::Node * tempTestNode5 = new CU::DoubleLinkedList<int>::Node(*new int(5));
			CU::DoubleLinkedList<int>::Node * tempTestNode6 = new CU::DoubleLinkedList<int>::Node(*new int(6));
			CU::DoubleLinkedList<int>::Node * tempTestNode7 = new CU::DoubleLinkedList<int>::Node(*new int(7));
			CU::DoubleLinkedList<int>::Node * tempTestNode8 = new CU::DoubleLinkedList<int>::Node(*new int(8));
			CU::DoubleLinkedList<int>::Node * tempTestNode9 = new CU::DoubleLinkedList<int>::Node(*new int(9));
			CU::DoubleLinkedList<int>::Node * tempTestNode10 = new CU::DoubleLinkedList<int>::Node(*new int(10));

			testLinkedList.InsertNodeSorted(tempTestNode9);
			testLinkedList.InsertNodeSorted(tempTestNode4);
			testLinkedList.InsertNodeSorted(tempTestNode3);
			testLinkedList.InsertNodeSorted(tempTestNode8);
			testLinkedList.InsertNodeSorted(tempTestNode5);
			testLinkedList.InsertNodeSorted(tempTestNode6);
			testLinkedList.InsertNodeSorted(tempTestNode10);
			testLinkedList.InsertNodeSorted(tempTestNode2);
			testLinkedList.InsertNodeSorted(tempTestNode1);
			testLinkedList.InsertNodeSorted(tempTestNode7);

			testLinkedList.DeleteNode(5);

			CU::DoubleLinkedList<int>::Node * TestNode = testLinkedList.GetFirstNode();

			for (int iTest = 10; iTest > 0; --iTest)
			{
				if (iTest != 5)
				{
					Assert::AreEqual(iTest, TestNode->myData);
					TestNode = TestNode->myNext;
				}
			}

			TestNode = testLinkedList.GetFirstNode();

			for (int iTest = 10; iTest > 0; --iTest)
			{
				if (iTest != 5)
				{
					Assert::AreEqual(iTest, TestNode->myData);
					TestNode = TestNode->myNext;
				}
				else
				{
					Assert::AreNotEqual(iTest, TestNode->myData);
				}
			}

		}

		TEST_METHOD(DeleteWithValueOrderIsIntactShouldFail)
		{
			CU::DoubleLinkedList<int> testLinkedList;

			CU::DoubleLinkedList<int>::Node * tempTestNode1 = new CU::DoubleLinkedList<int>::Node(*new int(1));
			CU::DoubleLinkedList<int>::Node * tempTestNode2 = new CU::DoubleLinkedList<int>::Node(*new int(2));
			CU::DoubleLinkedList<int>::Node * tempTestNode3 = new CU::DoubleLinkedList<int>::Node(*new int(3));
			CU::DoubleLinkedList<int>::Node * tempTestNode4 = new CU::DoubleLinkedList<int>::Node(*new int(4));
			CU::DoubleLinkedList<int>::Node * tempTestNode5 = new CU::DoubleLinkedList<int>::Node(*new int(5));
			CU::DoubleLinkedList<int>::Node * tempTestNode6 = new CU::DoubleLinkedList<int>::Node(*new int(6));
			CU::DoubleLinkedList<int>::Node * tempTestNode7 = new CU::DoubleLinkedList<int>::Node(*new int(7));
			CU::DoubleLinkedList<int>::Node * tempTestNode8 = new CU::DoubleLinkedList<int>::Node(*new int(8));
			CU::DoubleLinkedList<int>::Node * tempTestNode9 = new CU::DoubleLinkedList<int>::Node(*new int(9));
			CU::DoubleLinkedList<int>::Node * tempTestNode10 = new CU::DoubleLinkedList<int>::Node(*new int(10));

			testLinkedList.InsertNodeSorted(tempTestNode9);
			testLinkedList.InsertNodeSorted(tempTestNode4);
			testLinkedList.InsertNodeSorted(tempTestNode3);
			testLinkedList.InsertNodeSorted(tempTestNode8);
			testLinkedList.InsertNodeSorted(tempTestNode5);
			testLinkedList.InsertNodeSorted(tempTestNode6);
			testLinkedList.InsertNodeSorted(tempTestNode10);
			testLinkedList.InsertNodeSorted(tempTestNode2);
			testLinkedList.InsertNodeSorted(tempTestNode1);
			testLinkedList.InsertNodeSorted(tempTestNode7);

			//testLinkedList.DeleteNode(500);

			//AssertFailedExceptionClass
		}

		TEST_METHOD(InsertSortedNodeLotsOfNodesWHEREINTSAREPOINTERS)
		{
			CU::DoubleLinkedList<int*> testLinkedList;

			int* tempNumber1 = new int(1);
			int* tempNumber2 = new int(2);
			int* tempNumber3 = new int(3);
			int* tempNumber4 = new int(4);
			int* tempNumber5 = new int(5);
			int* tempNumber6 = new int(6);
			int* tempNumber7 = new int(7);
			int* tempNumber8 = new int(8);
			int* tempNumber9 = new int(9);
			int* tempNumber10 = new int(10);

			CU::DoubleLinkedList<int*>::Node * tempTestNode1 = new CU::DoubleLinkedList<int*>::Node(tempNumber1);
			CU::DoubleLinkedList<int*>::Node * tempTestNode2 = new CU::DoubleLinkedList<int*>::Node(tempNumber2);
			CU::DoubleLinkedList<int*>::Node * tempTestNode3 = new CU::DoubleLinkedList<int*>::Node(tempNumber3);
			CU::DoubleLinkedList<int*>::Node * tempTestNode4 = new CU::DoubleLinkedList<int*>::Node(tempNumber4);
			CU::DoubleLinkedList<int*>::Node * tempTestNode5 = new CU::DoubleLinkedList<int*>::Node(tempNumber5);
			CU::DoubleLinkedList<int*>::Node * tempTestNode6 = new CU::DoubleLinkedList<int*>::Node(tempNumber6);
			CU::DoubleLinkedList<int*>::Node * tempTestNode7 = new CU::DoubleLinkedList<int*>::Node(tempNumber7);
			CU::DoubleLinkedList<int*>::Node * tempTestNode8 = new CU::DoubleLinkedList<int*>::Node(tempNumber8);
			CU::DoubleLinkedList<int*>::Node * tempTestNode9 = new CU::DoubleLinkedList<int*>::Node(tempNumber9);
			CU::DoubleLinkedList<int*>::Node * tempTestNode10 = new CU::DoubleLinkedList<int*>::Node(tempNumber10);

			testLinkedList.InsertNodeSorted(tempTestNode9);
			testLinkedList.InsertNodeSorted(tempTestNode4);
			testLinkedList.InsertNodeSorted(tempTestNode3);
			testLinkedList.InsertNodeSorted(tempTestNode8);
			testLinkedList.InsertNodeSorted(tempTestNode5);
			testLinkedList.InsertNodeSorted(tempTestNode6);
			testLinkedList.InsertNodeSorted(tempTestNode10);
			testLinkedList.InsertNodeSorted(tempTestNode2);
			testLinkedList.InsertNodeSorted(tempTestNode1);
			testLinkedList.InsertNodeSorted(tempTestNode7);

			CU::DoubleLinkedList<int*>::Node * TestNode = testLinkedList.GetFirstNode();

			for (int iTest = 10; iTest > 0; --iTest)
			{
				int testInt = *TestNode->myData;
				Assert::AreEqual(iTest, testInt);
				TestNode = TestNode->myNext;
			}
		}
	};
}