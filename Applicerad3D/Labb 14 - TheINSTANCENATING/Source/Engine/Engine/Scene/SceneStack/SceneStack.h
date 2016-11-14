#pragma once
#include "Engine/Scene/Messages/PopSceneMessage.h"
#include "Engine/Scene/Messages/CreateSceneMessage.h"

namespace ENGINE_NAMESPACE
{
	struct EndOfFrameMessage;

	class SceneStack 
	{
	public:
		SceneStack();
		~SceneStack();

		void AddScene(std::shared_ptr<Scene> aScene, eSceneType aType);

		bool IsEmpty() const;

		void AddPopCommand(const ePopType & aPopType);
		void HandleQueuedCommands();

		inline std::shared_ptr<Scene> GetCurrentScene();
		inline std::shared_ptr<Scene> GetCurrentScene() const;

	private:
		struct QueuedStackEvent
		{
			std::shared_ptr<Scene> myScene = nullptr;
			eSceneType mySceneType;
			ePopType myPopType;
		};

		void AddMajorScene(std::shared_ptr<Scene> aScene);
		void AddSubScene(std::shared_ptr<Scene> aScene, bool aIsMajor = false);

		void PopSubScene();
		void PopMajorScene();
		void PopToFirst();
		void PopAll();

		void HandlePoppedMajor();

		GrowingArray<QueuedStackEvent> myQueuedCommands;
		GrowingArray<GrowingArray<std::shared_ptr<Scene>>> myStack; //Outer is major, inner is sub
	};

	inline std::shared_ptr<Scene> SceneStack::GetCurrentScene()
	{
		if (IsEmpty() == true)
		{
			Error("Scenestack Error - Tried to get scene from an empty Scenestack!");
		}
		return myStack.GetLast().GetLast();
	}

	inline std::shared_ptr<Scene> SceneStack::GetCurrentScene() const
	{
		if (IsEmpty() == true)
		{
			Error("Scenestack Error - Tried to get scene from an empty Scenestack!");
		}
		return myStack.GetLast().GetLast();
	}
};