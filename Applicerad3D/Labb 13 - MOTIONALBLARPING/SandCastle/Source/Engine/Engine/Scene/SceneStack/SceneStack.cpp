#include "stdafx.h"
#include "SceneStack.h"
#include "Engine/GenericGameMessages.h"

namespace ENGINE_NAMESPACE
{

	SceneStack::SceneStack()
	{
		myStack.Reserve(8);
	}

	SceneStack::~SceneStack()
	{
	}

	void SceneStack::AddScene(std::shared_ptr<Scene> aScene, eSceneType aType)
	{
		if (IsEmpty() == true)
		{
			AddMajorScene(aScene);
		}
		else
		{
			QueuedStackEvent temp;

			temp.myScene = aScene;
			temp.mySceneType = aType;

			myQueuedCommands.Add(temp);
		}
	}

	bool SceneStack::IsEmpty() const
	{
		return (myStack.Size() == 0);
	}

	ReceiveResult SceneStack::Receive(const PopSceneMessage & aMessage)
	{
		QueuedStackEvent temp;
		temp.myPopType = aMessage.myPop;
		myQueuedCommands.Add(temp);

		return ReceiveResult::eContinue;
	}

	ENGINE_NAMESPACE::ReceiveResult SceneStack::Receive(const EndOfFrameMessage & aMessage)
	{
		HandleQueuedCommands();
		return ReceiveResult::eContinue;
	}

	//PRIVATE FUNCTIONS ---------------------

	void SceneStack::HandleQueuedCommands()
	{
		for (unsigned short i = 0; i < myQueuedCommands.Size() ; ++i)
		{
			if (myQueuedCommands[i].myScene != nullptr)
			{
				switch (myQueuedCommands[i].mySceneType)
				{
				case eSceneType::eSub:
					AddSubScene(myQueuedCommands[i].myScene);
					break;
				case eSceneType::eMajor:
					AddMajorScene(myQueuedCommands[i].myScene);
					break;
				default:
					break;
				}
			}
			else
			{
				switch (myQueuedCommands[i].myPopType)
				{
				case ePopType::eCurrent:
					PopSubScene();
					break;
				case ePopType::eMajor:
					PopMajorScene();
					break;
				case ePopType::eAll:
					PopAll();
					break;
				default:
					Error("Error Scenestack - Unknown Pop Scene Type!");
					break;
				}
				HandlePoppedMajor();
			}
		}

		if (IsEmpty() == true)
		{
			SB::PostMaster::Post(SB::CloseGameMessage());
		}
	}

	void SceneStack::AddMajorScene(std::shared_ptr<Scene> aScene)
	{
		GrowingArray<std::shared_ptr<Scene>> temp;
		temp.Reserve(8);
		myStack.Add(temp);	
		AddSubScene(aScene);
	}

	void SceneStack::AddSubScene(std::shared_ptr<Scene> aScene)
	{
		if (myStack.Size() == 0)
		{
			Error("Tried to add first scene as a subscene, must be major scene!");
		}
		myStack.GetLast().Add(aScene);
	}

	void SceneStack::PopSubScene()
	{
		myStack.GetLast().RemoveAtIndex(myStack.Size() - 1);
	}

	void SceneStack::PopMajorScene()
	{
		for (unsigned short i = 0; i < myStack.GetLast().Size(); ++i)
		{
			PopSubScene();
		}
		HandlePoppedMajor();
	}

	void SceneStack::PopAll()
	{
		for (unsigned short i = 0; i < myStack.Size(); ++i)
		{
			PopMajorScene();
		}
	}

	void SceneStack::HandlePoppedMajor()
	{
		if (myStack.GetLast().Size() == 0)
		{
			myStack.RemoveAtIndex(myStack.Size() - 1);
		}
	}

};