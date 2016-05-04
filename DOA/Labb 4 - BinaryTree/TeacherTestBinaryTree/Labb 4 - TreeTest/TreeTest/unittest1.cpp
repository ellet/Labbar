#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
#include <vector>
#include <iostream>
#include <sstream>
#include <assert.h>

#include "BinaryTree.h"

using namespace CommonUtilities;

static const int seqLen = 8;
static const int seqMax = 7;
static double insertSeq[] = { 13.01, 25.02, 20.03, 10.04, 29.05, 2.06, 31.07, 12.08, };
static double inorderSeq[] = { 2.06, 10.04, 12.08, 13.01, 20.03, 25.02, 29.05, 31.07, };
static double postorderSeq[] = { 2.06, 12.08, 10.04, 20.03, 31.07, 29.05, 25.02, 13.01, };

namespace TreeTest
{		

	using namespace std;
	class OutputCatcher
	{
	public:
		OutputCatcher() : output(stringstream::in | stringstream::out), backup(nullptr)
		{
			backup = cout.rdbuf(output.rdbuf());
		}
		~OutputCatcher()
		{
			cout.rdbuf(backup);
		}
		stringstream& Output() 
		{
			return output;
		}
	private:
		stringstream output;
		streambuf *backup;
	};


	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestConstruct)
		{
			BinaryTree<double> t;
			assert( nullptr == t.GetRootNode() );
			assert( nullptr == t.Find(insertSeq[0]) );
		}

		TEST_METHOD(TestInsertFindRoot)
		{
			BinaryTree<double> t;
			t.InsertNode(insertSeq[0]);
			assert( nullptr != t.GetRootNode() );
			assert( t.Find(insertSeq[0]) == t.GetRootNode() );
			assert( nullptr == t.Find(insertSeq[1]) );
		}
		TEST_METHOD(TestInsertFindValues)
		{
			BinaryTree<double> t;
			for (int i = 0; i < seqLen; i++) 
			{
				t.InsertNode(insertSeq[i]);
			}
			for (int i = 0; i < seqLen; i++) 
			{
				assert( nullptr != t.Find(insertSeq[i]) );
			}
		}
		TEST_METHOD(TestInsertDeleteRootValue)
		{
			BinaryTree<double> t;
			t.InsertNode(insertSeq[0]);
			t.DeleteNode(insertSeq[0]);
			assert( nullptr == t.GetRootNode() );
			assert( nullptr == t.Find(insertSeq[0]) );
		}

		TEST_METHOD(TestInsertDeleteRootNode)
		{
			BinaryTree<double> t;
			t.InsertNode(insertSeq[0]);
			t.DeleteNode(t.GetRootNode());
			assert( nullptr == t.GetRootNode() );
			assert( nullptr == t.Find(insertSeq[0]) );
			t.InsertNode(insertSeq[0]);
			t.DeleteNode(insertSeq[0]);
			assert( nullptr == t.GetRootNode() );
			assert( nullptr == t.Find(insertSeq[0]) );
		}		
		
		void TestInsertDeleteValue(double val)
		{
			BinaryTree<double> t;
			for (int i = 0; i < seqLen; i++) 
			{
				t.InsertNode(insertSeq[i]);
			}
			t.DeleteNode(val);
			for (int i = 0; i < seqLen; i++) 
			{
				if (insertSeq[i] != val)
					assert( nullptr != t.Find(insertSeq[i]) );
				else
					assert( nullptr == t.Find(insertSeq[i]) );
			}
		}		
		
		TEST_METHOD(TestInsertDeleteRootNodeWithTwoLeaves)
		{
			BinaryTree<double> t;
			t.InsertNode(20);
			t.InsertNode(30);
			t.InsertNode(10);
			t.DeleteNode(20);
			assert (nullptr != t.Find(10));
			assert (nullptr != t.Find(30));
		}

		
		TEST_METHOD(TestInsertDeleteParentFindChild)
		{
			BinaryTree<double> t;
			t.InsertNode(50);
			t.InsertNode(40);
			t.InsertNode(45);
			t.InsertNode(30);
			t.InsertNode(20);
			t.DeleteNode(30);
			assert (nullptr != t.Find(20));
		}

				
		TEST_METHOD(TestInsertDeleteNodeWithParentAndTwoChilds)
		{
			BinaryTree<double> t;
			t.InsertNode(50);
			t.InsertNode(40);
			t.InsertNode(45);
			t.InsertNode(30);
			t.InsertNode(20);
			t.DeleteNode(40);
			assert (nullptr != t.Find(50));
			assert (nullptr != t.Find(45));
			assert (nullptr != t.Find(30));
		}

				
		TEST_METHOD(TestInsertDeleteNodeWithOneLeaf)
		{
			BinaryTree<double> t;
			t.InsertNode(30);
			t.InsertNode(20);
			t.InsertNode(10);
			t.InsertNode(5);
			t.DeleteNode(20);

			assert (nullptr != t.Find(5));
			assert (nullptr != t.Find(10));
		}

		void TestInsertDeleteNode(double val) 
		{
			BinaryTree<double> t;
			for (int i = 0; i < seqLen; i++) 
			{
				t.InsertNode(insertSeq[i]);
			}
			t.DeleteNode(t.Find(val));
			for (int i = 0; i < seqLen; i++) 
			{
				if (insertSeq[i] != val)
					assert( nullptr != t.Find(insertSeq[i]) );
				else
					assert( nullptr == t.Find(insertSeq[i]) );
			}
		}

		
	TEST_METHOD(TestInsertDeleteValueLeaf) 
	{
		TestInsertDeleteValue(20.03);
	}

	TEST_METHOD(TestInsertDeleteNodeLeaf) 
	{
		TestInsertDeleteNode(20.03);
	}

	TEST_METHOD(TestInsertDeleteValueSingle) 
	{
		TestInsertDeleteValue(29.05);
	}

	TEST_METHOD(TestInsertDeleteNodeSingle) 
	{
		TestInsertDeleteNode(29.05);
	}

	TEST_METHOD(TestInsertDeleteValueDouble) 
	{
		TestInsertDeleteValue(29.05);
	}

	TEST_METHOD(TestInsertDeleteNodeDouble) 
	{
		TestInsertDeleteNode(29.05);
	}

	TEST_METHOD(TestPostOrderNull) 
	{
		BinaryTree<double> t;
		t.PostOrderTraverse();
	}

	TEST_METHOD(TestInOrderNull) 
	{
		BinaryTree<double> t;
		t.InOrderTraverse();
	}

	void CheckTraverseSequence(stringstream& output, double seq[], int seqLen)
	{
		double val = 0.0;
		for (int i = 0; i < seqLen; i++) 
		{
			output >> val;
			assert( val == seq[i] );
		}
	}

	TEST_METHOD(TestPostOrder) 
	{
		BinaryTree<double> t;
		for (int i = 0; i < seqLen; i++) 
		{
			t.InsertNode(insertSeq[i]);
		}

		OutputCatcher oc;
		t.PostOrderTraverse();
		CheckTraverseSequence(oc.Output(), postorderSeq , seqLen);

	}

	TEST_METHOD(TestInOrder) 
	{
		BinaryTree<double> t;
		for (int i = 0; i < seqLen; i++) 
		{
			t.InsertNode(insertSeq[i]);
		}

		OutputCatcher oc;
		t.InOrderTraverse();
		CheckTraverseSequence(oc.Output(), inorderSeq , seqLen);
	}



	};
}