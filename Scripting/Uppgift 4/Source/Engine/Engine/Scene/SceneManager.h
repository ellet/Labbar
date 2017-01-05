#pragma once
#include "Engine/GameObject/GameObject.h"
#include "Engine/Scene/SceneStack/SceneStack.h"
#include "Engine/Scene/Messages/CreateSceneMessage.h"
#include "Engine/Scene/Messages/PopSceneMessage.h"


namespace SB
{
	template<typename TSceneType, typename ...TArgs>
	std::shared_ptr<TSceneType> NewSceneBindBeforeDeletion(TArgs && ...aArgs)
	{
		auto deleter = [](TSceneType* o) -> void
		{
			PostMasterState * state = &static_cast<PostMasterState&>(*o);
			{
				PostMasterStateBinding binding = PostMaster::Push(*state);
				delete o;
			}
			delete state;
		};

		PostMasterState * state = new PostMasterState();
		PostMasterStateBinding binding = PostMaster::Push(*state);
		TSceneType * scene = new TSceneType(*state, aArgs...);
		return std::shared_ptr<TSceneType>(scene, deleter);
	}

	class JsonScene;
	class Scene;
	class StandardEffect;
	class PrefabScene;
	struct CreateSceneMessage;
	struct PushSceneMessage;

	class SceneManager : public Subscriber<CreateSceneMessage>, public Subscriber<PopSceneMessage>, public Subscriber<EndOfFrameMessage>, public Subscriber<PushSceneMessage>
	{
	public:
		SceneManager();
		~SceneManager();

		void Update(const SB::Time &aDeltaTime);
		void Render();
		void RenderGui();
		void CopyToBackbuffer();

		void LoadPrefabs();

		std::shared_ptr<Scene> LoadJsonScene(const char* aFilePath, const eSceneType aType = eSceneType::eMajor, const char* aSkyBoxPath = "");

		template<typename TSceneType, typename ...TArgs>
		std::shared_ptr<Scene> LoadScene(const eSceneType aType, const TArgs & ...aArgs);

		inline std::shared_ptr<Scene> GetCurrentScene() const
		{
			return mySceneStack.GetCurrentScene();
		}

		void AddPreChachedScene(std::shared_ptr<Scene> aSceneToAdd, const eSceneClass aSceneTypeAdd);

		virtual ReceiveResult Receive(const CreateSceneMessage & aMessage) override;
		virtual ReceiveResult Receive(const PopSceneMessage & aMessage) override;
		virtual ReceiveResult Receive(const EndOfFrameMessage & aMessage) override;
		virtual ReceiveResult Receive(const PushSceneMessage & aMessage) override;

	private:
		std::shared_ptr<JsonScene> CreateScene(const char* aFilePath, const char* aSkyBoxPath = "");
		std::shared_ptr<PrefabScene> myPrefabScene;
		ObjectPtr LoadGameObject(DataNode aObjectNode, std::shared_ptr<Scene> aScene, GrowingArray<ObjectPtr>& aLoadedObjectList);
		//std::unordered_map<const char*, std::shared_ptr<Scene>> myScenes;
		SceneStack mySceneStack;
		StaticList<std::shared_ptr<Scene>, static_cast<unsigned short>(eSceneClass::enumlength)> myCachedScenes;

		std::string myCurrentSaveFile;

	};

	template<typename TSceneType, typename ...TArgs>
	std::shared_ptr<Scene> SceneManager::LoadScene(const eSceneType aType, const TArgs & ...aArgs)
	{
		mySceneStack.AddScene(NewSceneBindBeforeDeletion<TSceneType>(aArgs...), aType);
		return mySceneStack.GetCurrentScene();
	}

}
