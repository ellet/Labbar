#include "stdafx.h"
#include "CppUnitTest.h"

#include <BinaryTree/BinaryTree.h>
#include <NameSpaceAliases.h>
#include <iostream>
#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TotalyTestForBinaryTree
{		

	bool CheckIfTreeIsSame(const CU::TreeNode<int> * aFirstTreeNode, const CU::TreeNode<int> * aSecondTreeNode)
	{
		if (aFirstTreeNode == nullptr || aSecondTreeNode == nullptr)
		{
			if (aSecondTreeNode == aFirstTreeNode)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		if (aFirstTreeNode->GetData() != aSecondTreeNode->GetData())
		{
			return false;
		}
		else
		{
			if (CheckIfTreeIsSame(aFirstTreeNode->GetLeftChild(), aSecondTreeNode->GetLeftChild()) == true &&
				CheckIfTreeIsSame(aFirstTreeNode->GetRightChild(), aSecondTreeNode->GetRightChild()) == true)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}

	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(CreateBinaryTree)
		{
			CU::BinaryTree<int> tempTree;
		}

		TEST_METHOD(AccesRootNodeThatIsNull)
		{
			CU::BinaryTree<int> tempTree;

			Assert::IsNull(tempTree.GetRootNode());
		}

		TEST_METHOD(ConstructNode)
		{
			CU::TreeNode<int> * tempNode = new CU::TreeNode<int>(10);
		}

		TEST_METHOD(AccessNodeData)
		{
			CU::TreeNode<int> * tempNode = new CU::TreeNode<int>(10);

			Assert::AreEqual(tempNode->GetData(), 10);
		}

		TEST_METHOD(InsertNodeAndTestFirstNode)
		{
			CU::BinaryTree<int> tempTree;

			CU::TreeNode<int> * tempNode = new CU::TreeNode<int>(10);

			tempTree.InsertNode(tempNode);

			Assert::IsTrue(tempNode == tempTree.GetRootNode());
		}

		TEST_METHOD(InsertNodeTakeLotsTestOnlyRoot)
		{
			CU::BinaryTree<int> tempTree;

			CU::TreeNode<int> * tempNode1 = new CU::TreeNode<int>(1);
			CU::TreeNode<int> * tempNode2 = new CU::TreeNode<int>(2);
			CU::TreeNode<int> * tempNode3 = new CU::TreeNode<int>(3);
			CU::TreeNode<int> * tempNode4 = new CU::TreeNode<int>(4);

			tempTree.InsertNode(tempNode1);
			tempTree.InsertNode(tempNode2);
			tempTree.InsertNode(tempNode3);
			tempTree.InsertNode(tempNode4);

			Assert::IsTrue(tempNode1 == tempTree.GetRootNode());
		}

		TEST_METHOD(FINdStuff)
		{
			CU::BinaryTree<int> tempTree;

			CU::TreeNode<int> * tempNode1 = new CU::TreeNode<int>(1);
			CU::TreeNode<int> * tempNode2 = new CU::TreeNode<int>(2);
			CU::TreeNode<int> * tempNode3 = new CU::TreeNode<int>(3);
			CU::TreeNode<int> * tempNode4 = new CU::TreeNode<int>(4);

			tempTree.InsertNode(tempNode1);
			tempTree.InsertNode(tempNode2);
			tempTree.InsertNode(tempNode4);
			tempTree.InsertNode(tempNode3);

			Assert::IsTrue(tempNode1 == tempTree.Find(1));
			Assert::IsTrue(tempNode2 == tempTree.Find(2));
			Assert::IsTrue(tempNode3 == tempTree.Find(3));
			Assert::IsTrue(tempNode4 == tempTree.Find(4));

		}

		TEST_METHOD(FINdLOTSOFSTFFSSSsStuffsss)
		{
			CU::BinaryTree<int> tempTree;

			CU::TreeNode<int> * tempNode1 = new CU::TreeNode<int>(1);
			CU::TreeNode<int> * tempNode2 = new CU::TreeNode<int>(2);
			CU::TreeNode<int> * tempNode3 = new CU::TreeNode<int>(3);
			CU::TreeNode<int> * tempNode4 = new CU::TreeNode<int>(4);
			CU::TreeNode<int> * tempNode5 = new CU::TreeNode<int>(5);
			CU::TreeNode<int> * tempNode6 = new CU::TreeNode<int>(6);
			CU::TreeNode<int> * tempNode7 = new CU::TreeNode<int>(7);
			CU::TreeNode<int> * tempNode8 = new CU::TreeNode<int>(8);
			CU::TreeNode<int> * tempNode9 = new CU::TreeNode<int>(9);
			CU::TreeNode<int> * tempNode10 = new CU::TreeNode<int>(10);
			CU::TreeNode<int> * tempNode11 = new CU::TreeNode<int>(11);
			CU::TreeNode<int> * tempNode12 = new CU::TreeNode<int>(12);
			CU::TreeNode<int> * tempNode13 = new CU::TreeNode<int>(13);
			CU::TreeNode<int> * tempNode14 = new CU::TreeNode<int>(14);
			CU::TreeNode<int> * tempNode15 = new CU::TreeNode<int>(15);
			CU::TreeNode<int> * tempNode16 = new CU::TreeNode<int>(16);
			CU::TreeNode<int> * tempNode17 = new CU::TreeNode<int>(17);
			CU::TreeNode<int> * tempNode18 = new CU::TreeNode<int>(18);
			CU::TreeNode<int> * tempNode19 = new CU::TreeNode<int>(19);
			CU::TreeNode<int> * tempNode20 = new CU::TreeNode<int>(20);

			tempTree.InsertNode(tempNode10);
			tempTree.InsertNode(tempNode11);
			tempTree.InsertNode(tempNode12);
			tempTree.InsertNode(tempNode13);
			tempTree.InsertNode(tempNode14);
			tempTree.InsertNode(tempNode15);
			tempTree.InsertNode(tempNode16);
			tempTree.InsertNode(tempNode17);
			tempTree.InsertNode(tempNode1);
			tempTree.InsertNode(tempNode2);
			tempTree.InsertNode(tempNode3);
			tempTree.InsertNode(tempNode4);
			tempTree.InsertNode(tempNode5);
			tempTree.InsertNode(tempNode6);
			tempTree.InsertNode(tempNode7);
			tempTree.InsertNode(tempNode8);
			tempTree.InsertNode(tempNode9);
			tempTree.InsertNode(tempNode18);
			tempTree.InsertNode(tempNode19);
			tempTree.InsertNode(tempNode20);


			Assert::IsTrue(tempNode1 == tempTree.Find(1));
			Assert::IsTrue(tempNode2 == tempTree.Find(2));
			Assert::IsTrue(tempNode3 == tempTree.Find(3));
			Assert::IsTrue(tempNode4 == tempTree.Find(4));
			Assert::IsTrue(tempNode5 == tempTree.Find(5));
			Assert::IsTrue(tempNode6 == tempTree.Find(6));
			Assert::IsTrue(tempNode7 == tempTree.Find(7));
			Assert::IsTrue(tempNode8 == tempTree.Find(8));
			Assert::IsTrue(tempNode9 == tempTree.Find(9));
			Assert::IsTrue(tempNode10 == tempTree.Find(10));
			Assert::IsTrue(tempNode11 == tempTree.Find(11));
			Assert::IsTrue(tempNode12 == tempTree.Find(12));
			Assert::IsTrue(tempNode13 == tempTree.Find(13));
			Assert::IsTrue(tempNode14 == tempTree.Find(14));
			Assert::IsTrue(tempNode15 == tempTree.Find(15));
			Assert::IsTrue(tempNode16 == tempTree.Find(16));
			Assert::IsTrue(tempNode17 == tempTree.Find(17));
			Assert::IsTrue(tempNode18 == tempTree.Find(18));
			Assert::IsTrue(tempNode19 == tempTree.Find(19));
			Assert::IsTrue(tempNode20 == tempTree.Find(20));

		}

		TEST_METHOD(InsertDoubles)
		{
			CU::BinaryTree<double> tempTree;

			CU::TreeNode<double> * tempNode1 = new CU::TreeNode<double>(1.3);
			CU::TreeNode<double> * tempNode2 = new CU::TreeNode<double>(2.2);
			CU::TreeNode<double> * tempNode3 = new CU::TreeNode<double>(3.7);
			CU::TreeNode<double> * tempNode4 = new CU::TreeNode<double>(4.2);

			tempTree.InsertNode(tempNode1);
			tempTree.InsertNode(tempNode2);
			tempTree.InsertNode(tempNode4);
			tempTree.InsertNode(tempNode3);

			Assert::IsTrue(tempNode1 == tempTree.Find(1.3));
			Assert::IsTrue(tempNode2 == tempTree.Find(2.2));
			Assert::IsTrue(tempNode3 == tempTree.Find(3.7));
			Assert::IsTrue(tempNode4 == tempTree.Find(4.2));

		}

		TEST_METHOD(InsertUnsignedShort)
		{
			CU::BinaryTree<unsigned short> tempTree;

			CU::TreeNode<unsigned short> * tempNode1 = new CU::TreeNode<unsigned short>(13);
			CU::TreeNode<unsigned short> * tempNode2 = new CU::TreeNode<unsigned short>(22);
			CU::TreeNode<unsigned short> * tempNode3 = new CU::TreeNode<unsigned short>(37);
			CU::TreeNode<unsigned short> * tempNode4 = new CU::TreeNode<unsigned short>(42);

			tempTree.InsertNode(tempNode1);
			tempTree.InsertNode(tempNode2);
			tempTree.InsertNode(tempNode4);
			tempTree.InsertNode(tempNode3);

			Assert::IsTrue(tempNode1 == tempTree.Find(13));
			Assert::IsTrue(tempNode2 == tempTree.Find(22));
			Assert::IsTrue(tempNode3 == tempTree.Find(37));
			Assert::IsTrue(tempNode4 == tempTree.Find(42));

		}

		TEST_METHOD(InsertUnsignedShortPointer)
		{
			CU::BinaryTree<unsigned short*> tempTree;

			CU::TreeNode<unsigned short*> * tempNode1 = new CU::TreeNode<unsigned short*>(new unsigned short(13));
			CU::TreeNode<unsigned short*> * tempNode2 = new CU::TreeNode<unsigned short*>(new unsigned short(22));
			CU::TreeNode<unsigned short*> * tempNode3 = new CU::TreeNode<unsigned short*>(new unsigned short(37));
			CU::TreeNode<unsigned short*> * tempNode4 = new CU::TreeNode<unsigned short*>(new unsigned short(42));

			tempTree.InsertNode(tempNode1);
			tempTree.InsertNode(tempNode2);
			tempTree.InsertNode(tempNode4);
			tempTree.InsertNode(tempNode3);

			Assert::IsTrue(tempNode1 == tempTree.Find(tempNode1->GetData()));
			Assert::IsTrue(tempNode2 == tempTree.Find(tempNode2->GetData()));
			Assert::IsTrue(tempNode3 == tempTree.Find(tempNode3->GetData()));
			Assert::IsTrue(tempNode4 == tempTree.Find(tempNode4->GetData()));

		}

		TEST_METHOD(InsertValue)
		{
			CU::BinaryTree<int> tempTree;

			tempTree.InsertNode(1);
			tempTree.InsertNode(2);
			tempTree.InsertNode(3);
			tempTree.InsertNode(4);

			Assert::IsTrue(1 == tempTree.Find(1)->GetData());
			Assert::IsTrue(2 == tempTree.Find(2)->GetData());
			Assert::IsTrue(3 == tempTree.Find(3)->GetData());
			Assert::IsTrue(4 == tempTree.Find(4)->GetData());
		}

		TEST_METHOD(FindMissingValue)
		{
			CU::BinaryTree<int> tempTree;

			tempTree.InsertNode(1);
			tempTree.InsertNode(2);
			tempTree.InsertNode(4);

			Assert::IsTrue(1 == tempTree.Find(1)->GetData());
			Assert::IsTrue(2 == tempTree.Find(2)->GetData());
			Assert::IsTrue(nullptr == tempTree.Find(3));
			Assert::IsTrue(4 == tempTree.Find(4)->GetData());
		}

		TEST_METHOD(DeleteNode)
		{
			CU::BinaryTree<int> tempTree;

			CU::TreeNode<int> * tempNode1 = new CU::TreeNode<int>(1);
			CU::TreeNode<int> * tempNode2 = new CU::TreeNode<int>(2);
			CU::TreeNode<int> * tempNode3 = new CU::TreeNode<int>(3);
			CU::TreeNode<int> * tempNode4 = new CU::TreeNode<int>(4);

			tempTree.InsertNode(tempNode1);
			tempTree.InsertNode(tempNode2);
			tempTree.InsertNode(tempNode3);
			tempTree.InsertNode(tempNode4);

			Assert::IsTrue(tempNode1 == tempTree.Find(1));
			Assert::IsTrue(tempNode2 == tempTree.Find(2));
			Assert::IsTrue(tempNode3 == tempTree.Find(3));
			Assert::IsTrue(tempNode4 == tempTree.Find(4));

			tempTree.DeleteNode(tempNode3);

			Assert::IsTrue(nullptr == tempTree.Find(3));
			
		}

		TEST_METHOD(DeleteNodeFindEvenMoar)
		{
			CU::BinaryTree<int> tempTree;

			CU::TreeNode<int> * tempNode5 = new CU::TreeNode<int>(5);
			CU::TreeNode<int> * tempNode3 = new CU::TreeNode<int>(3);
			CU::TreeNode<int> * tempNode2 = new CU::TreeNode<int>(2);
			CU::TreeNode<int> * tempNode4 = new CU::TreeNode<int>(4);

			tempTree.InsertNode(tempNode5);
			tempTree.InsertNode(tempNode3);
			tempTree.InsertNode(tempNode2);
			tempTree.InsertNode(tempNode4);

			Assert::IsTrue(tempNode5 == tempTree.Find(5));
			Assert::IsTrue(tempNode3 == tempTree.Find(3));
			Assert::IsTrue(tempNode2 == tempTree.Find(2));
			Assert::IsTrue(tempNode4 == tempTree.Find(4));

			tempTree.DeleteNode(tempNode3);

			Assert::IsTrue(nullptr == tempTree.Find(3));
			Assert::IsTrue(tempNode4 == tempTree.Find(4));

		}

		TEST_METHOD(DeleteNodeWithValueFindEvenMoar)
		{
			CU::BinaryTree<int> tempTree;

			CU::TreeNode<int> * tempNode5 = new CU::TreeNode<int>(5);
			CU::TreeNode<int> * tempNode3 = new CU::TreeNode<int>(3);
			CU::TreeNode<int> * tempNode2 = new CU::TreeNode<int>(2);
			CU::TreeNode<int> * tempNode4 = new CU::TreeNode<int>(4);

			tempTree.InsertNode(tempNode5);
			tempTree.InsertNode(tempNode3);
			tempTree.InsertNode(tempNode2);
			tempTree.InsertNode(tempNode4);

			Assert::IsTrue(tempNode5 == tempTree.Find(5));
			Assert::IsTrue(tempNode3 == tempTree.Find(3));
			Assert::IsTrue(tempNode2 == tempTree.Find(2));
			Assert::IsTrue(tempNode4 == tempTree.Find(4));

			tempTree.DeleteNode(3);

			Assert::IsTrue(nullptr == tempTree.Find(3));
			Assert::IsTrue(tempNode4 == tempTree.Find(4));

		}

		TEST_METHOD(TraverseInorderOutput)
		{
			CU::BinaryTree<int> tempTree;

			tempTree.InsertNode(6);
			tempTree.InsertNode(3);
			tempTree.InsertNode(4);
			tempTree.InsertNode(2);
			tempTree.InsertNode(10);
			tempTree.InsertNode(100);

			std::stringstream test;

			tempTree.InOrderTraverseStream(test, *tempTree.GetRootNode());

			std::string tempstring1;
			std::string tempstring2; 
			std::string tempstring3;
			std::string tempstring4;
			std::string tempstring5;
			std::string tempstring6;

			test >> tempstring1;
			test >> tempstring2;
			test >> tempstring3;
			test >> tempstring4;
			test >> tempstring5;
			test >> tempstring6;
			
			Assert::IsTrue(tempstring1 == "2");
			Assert::IsTrue(tempstring2 == "3");
			Assert::IsTrue(tempstring3 == "4");
			Assert::IsTrue(tempstring4 == "6");
			Assert::IsTrue(tempstring5 == "10");
			Assert::IsTrue(tempstring6 == "100");
		}

		TEST_METHOD(DeleteRootNodeThatHasTwoLeaves)
		{
			CU::BinaryTree<int> tempTree;

			tempTree.InsertNode(6);
			tempTree.InsertNode(3);
			tempTree.InsertNode(4);
			tempTree.InsertNode(2);
			tempTree.InsertNode(10);
			tempTree.InsertNode(100);

			tempTree.DeleteNode(6);

			Assert::IsTrue(tempTree.Find(3) != nullptr);
			Assert::IsTrue(tempTree.Find(10) != nullptr);
		}


		TEST_METHOD(TraverseInorderIsWorkuing)
		{
			CU::BinaryTree<int> tempTree;

			tempTree.InsertNode(6);
			tempTree.InsertNode(3);
			tempTree.InsertNode(4);
			tempTree.InsertNode(2);
			tempTree.InsertNode(10);
			tempTree.InsertNode(100);

			tempTree.InOrderTraverse();
		}

		TEST_METHOD(TraversePostOrderTraverse)
		{
			CU::BinaryTree<int> tempTree;

			tempTree.InsertNode(13);
			tempTree.InsertNode(10);
			tempTree.InsertNode(2);
			tempTree.InsertNode(12);
			tempTree.InsertNode(25);
			tempTree.InsertNode(20);
			tempTree.InsertNode(29);
			tempTree.InsertNode(31);

			std::stringstream test;

			tempTree.PostOrderTraverseStream(test, *tempTree.GetRootNode());

			std::string tempstring1;
			std::string tempstring2;
			std::string tempstring3;
			std::string tempstring4;
			std::string tempstring5;
			std::string tempstring6;
			std::string tempstring7;
			std::string tempstring8;

			test >> tempstring1;
			test >> tempstring2;
			test >> tempstring3;
			test >> tempstring4;
			test >> tempstring5;
			test >> tempstring6;
			test >> tempstring7;
			test >> tempstring8;

			Assert::IsTrue(tempstring1 == "2");
			Assert::IsTrue(tempstring2 == "12");
			Assert::IsTrue(tempstring3 == "10");
			Assert::IsTrue(tempstring4 == "20");
			Assert::IsTrue(tempstring5 == "31");
			Assert::IsTrue(tempstring6 == "29");
			Assert::IsTrue(tempstring7 == "25");
			Assert::IsTrue(tempstring8 == "13");
		}

		TEST_METHOD(CheckIfTestMethodWorks)
		{
			CU::BinaryTree<int> tempTree1;
			CU::BinaryTree<int> tempTree2;
			CU::BinaryTree<int> tempTree3;

			tempTree1.InsertNode(13);
			tempTree1.InsertNode(10);
			tempTree1.InsertNode(2);
			tempTree1.InsertNode(12);
			tempTree1.InsertNode(25);
			tempTree1.InsertNode(20);
			tempTree1.InsertNode(29);
			tempTree1.InsertNode(31);

			tempTree2.InsertNode(13);
			tempTree2.InsertNode(10);
			tempTree2.InsertNode(2);
			tempTree2.InsertNode(12);
			tempTree2.InsertNode(25);
			tempTree2.InsertNode(20);
			tempTree2.InsertNode(29);
			tempTree2.InsertNode(31);

			tempTree3.InsertNode(13);
			tempTree3.InsertNode(10);
			tempTree3.InsertNode(2);
			tempTree3.InsertNode(99);
			tempTree3.InsertNode(25);
			tempTree3.InsertNode(20);
			tempTree3.InsertNode(29);
			tempTree3.InsertNode(31);

			Assert::IsTrue(CheckIfTreeIsSame(tempTree1.GetRootNode(), tempTree2.GetRootNode()));
			Assert::IsTrue(CheckIfTreeIsSame(tempTree2.GetRootNode(), tempTree1.GetRootNode()));

			Assert::IsFalse(CheckIfTreeIsSame(tempTree2.GetRootNode(), tempTree3.GetRootNode()));
			Assert::IsFalse(CheckIfTreeIsSame(tempTree3.GetRootNode(), tempTree1.GetRootNode()));
		}

		TEST_METHOD(TestBalance)
		{
			CU::BinaryTree<int> tempCompareTree;
			CU::BinaryTree<int> tempTestTree;

			/*CU::TreeNode<int> * tempNode1 = new CU::TreeNode<int>(25);
			CU::TreeNode<int> * tempNode2 = new CU::TreeNode<int>(20);
			CU::TreeNode<int> * tempNode3 = new CU::TreeNode<int>(10);
			CU::TreeNode<int> * tempNode4 = new CU::TreeNode<int>(23);
			CU::TreeNode<int> * tempNode5 = new CU::TreeNode<int>(15);
			CU::TreeNode<int> * tempNode6 = new CU::TreeNode<int>(5);
			CU::TreeNode<int> * tempNode7 = new CU::TreeNode<int>(30);
			CU::TreeNode<int> * tempNode8 = new CU::TreeNode<int>(28);
			CU::TreeNode<int> * tempNode9 = new CU::TreeNode<int>(40);*/

			tempCompareTree.InsertNode(25);
			tempCompareTree.InsertNode(20);
			tempCompareTree.InsertNode(10);
			tempCompareTree.InsertNode(23);
			tempCompareTree.InsertNode(15);
			tempCompareTree.InsertNode(5);
			tempCompareTree.InsertNode(30);
			tempCompareTree.InsertNode(28);
			tempCompareTree.InsertNode(40);

			tempTestTree.InsertNode(5);
			tempTestTree.InsertNode(10);
			tempTestTree.InsertNode(20);

			tempTestTree.InsertNode(15);
			tempTestTree.InsertNode(30);
			tempTestTree.InsertNode(25);

			tempTestTree.InsertNode(40);
			tempTestTree.InsertNode(23);
			tempTestTree.InsertNode(28);

			Assert::IsFalse(CheckIfTreeIsSame(tempTestTree.GetRootNode(), tempCompareTree.GetRootNode()));

			tempTestTree.DSW_Balance();

			Assert::IsTrue(CheckIfTreeIsSame(tempTestTree.GetRootNode(), tempCompareTree.GetRootNode()));
		}

		TEST_METHOD(BackBone)
		{
			CU::BinaryTree<int> tempTestTree;
			CU::BinaryTree<int> tempCompareTree;

			tempTestTree.InsertNode(20);
			tempTestTree.InsertNode(10);
			tempTestTree.InsertNode(50);
			tempTestTree.InsertNode(100);
			tempTestTree.InsertNode(22);
			tempTestTree.InsertNode(5);
			tempTestTree.InsertNode(80);
			tempTestTree.InsertNode(400);
			tempTestTree.InsertNode(2);

			tempCompareTree.InsertNode(2);
			tempCompareTree.InsertNode(5);
			tempCompareTree.InsertNode(10);
			tempCompareTree.InsertNode(20);
			tempCompareTree.InsertNode(22);
			tempCompareTree.InsertNode(50);
			tempCompareTree.InsertNode(80);
			tempCompareTree.InsertNode(100);
			tempCompareTree.InsertNode(400);

			tempTestTree.ChangeToBackBone();

			Assert::IsTrue(CheckIfTreeIsSame(tempTestTree.GetRootNode(), tempCompareTree.GetRootNode()));

			const CU::TreeNode<int> * testNode = tempTestTree.GetRootNode();

			while (testNode != nullptr)
			{
				Assert::IsTrue(testNode->GetLeftChild() == nullptr);

				if (testNode->GetLeftChild() != nullptr)
				{
					Assert::IsTrue(testNode->GetData() < testNode->GetRightChild()->GetData());
				}

				testNode = testNode->GetRightChild();
			}
		}

		TEST_METHOD(InOrderTraverseFunction)
		{
			CU::BinaryTree<size_t> tempTestTree;

			tempTestTree.InsertNode(2);
			tempTestTree.InsertNode(5);
			tempTestTree.InsertNode(10);
			tempTestTree.InsertNode(20);
			tempTestTree.InsertNode(22);
			tempTestTree.InsertNode(50);
			tempTestTree.InsertNode(80);
			tempTestTree.InsertNode(100);
			tempTestTree.InsertNode(400);

			Assert::AreEqual(9, tempTestTree.GetSize());

		}
	};
}