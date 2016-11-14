#include "stdafx.h"
#include "SceneStack.h"
#include "Engine/GenericEngineMessages.h"
#include "Engine/Scene/Scene.h"

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

	void SceneStack::AddPopCommand(const ePopType & aPopType)
	{
		QueuedStackEvent temp;
		temp.myPopType = aPopType;
		myQueuedCommands.Add(temp);
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
					if (myStack.GetLast().Empty() == false)
					{
						myStack.GetLast().GetLast()->OnExit();
					}
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
				case ePopType::eToFirst:
					PopToFirst();
					break;
				case ePopType::eAll:
					PopAll();
					break;
				default:
					Error("Error Scenestack - Either tried to create a scene without support in SceneManager,\nor you forgot to add support for a scene pop message enum type.");
					break;
				}
				HandlePoppedMajor();
			}
		}

		myQueuedCommands.RemoveAll();

		if (IsEmpty() == true)
		{
			SB::PostMaster::Post(SB::CloseGameMessage());
		}
	}

	void SceneStack::AddMajorScene(std::shared_ptr<Scene> aScene)
	{
		PostMasterStateBinding bind = PostMaster::Push(*aScene);

		GrowingArray<std::shared_ptr<Scene>> temp;
		temp.Reserve(8);
		if (myStack.GetLast().Empty() == false)
		{
			PostMasterStateBinding binding = PostMaster::Push(*myStack.GetLast().GetLast());
			myStack.GetLast().GetLast()->OnExit();
		}
		myStack.Add(temp);	
		AddSubScene(aScene);
	}

	void SceneStack::AddSubScene(std::shared_ptr<Scene> aScene, bool aIsMajor/* = false*/)
	{
		PostMasterStateBinding bind = PostMaster::Push(*aScene);

		if (myStack.Size() == 0)
		{
			Error("Tried to add first scene as a subscene, must be major scene!");
		}
/*
		if ((myStack.Size() > 1 && aIsMajor == true) || myStack.GetLast().Size() > 0)
		{
			myStack.GetLast().GetLast()->OnExit();
		}*/
		myStack.GetLast().Add(aScene);
		myStack.GetLast().GetLast()->OnEnter();
	}

	void SceneStack::PopSubScene()
	{
		{
			PostMasterStateBinding bind = PostMaster::Push(*myStack.GetLast().GetLast());
			myStack.GetLast().GetLast()->OnExit();
		}
		myStack.GetLast().RemoveAtIndex(myStack.GetLast().Size() - 1);
	}

	void SceneStack::PopMajorScene()
	{
		for (unsigned short i = 0; i < myStack.GetLast().Size(); ++i)
		{
			PopSubScene();
		}
		HandlePoppedMajor();
	}

	void SceneStack::PopToFirst()
	{
		for (unsigned short i = 0; i < myStack.Size(); ++i)
		{
			PopMajorScene();
		}
	}

	void SceneStack::PopAll()
	{
		PopToFirst();
		PopMajorScene();
	}

	void SceneStack::HandlePoppedMajor()
	{
		if (myStack.GetLast().Size() == 0 && myStack.Size() != 0)
		{
			myStack.RemoveAtIndex(myStack.Size() - 1);
		}
		if (myStack.GetLast().Empty() == false)
		{
			PostMasterStateBinding bind = PostMaster::Push(*myStack.GetLast().GetLast());
			myStack.GetLast().GetLast()->OnEnter();
		}
	}

};