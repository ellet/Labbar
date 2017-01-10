#pragma once
#include "Messages\SaveSceneMessage.h"
#include "Messages\EnterSceneMessage.h"
#include "Messages\ExitSceneMessage.h"
#include "Engine\Scene\SceneSystems\SceneSystems.h"

namespace SB
{
	class GameObject;
	class ObjectPtr;
	class BaseComponentFactory;

	class GameObjectFactory;
	template <typename TComponentFactoryType>
	class ComponentFactory;

	class Camera;
	class CameraController;

	class Model;
	class ModelInstance;

	class RootGUIElement;
	class GUILoader;

	class ParticleSystem;
	class GuiRenderTarget;

	class SceneSystems;
	class PhysicsManager;

	struct WindowSizeChangedMessage;

	struct TimeData
	{
		Vector4f timer;
	};

	struct SunThings
	{
		Sprite sprite;
		float offsetAmount;
	};

	class Scene : public JsonObject, public Subscriber<SaveLevelMessage>, public Subscriber<WindowSizeChangedMessage>
	{
	public:
		Scene(PostMasterState & aPostMasterState, const char* aName, const char* aSkyboxPath = "");
		virtual ~Scene();

		virtual void Update(const Time & aDeltaTime);
		virtual void Render();
		virtual void DebugRender();
		virtual void RenderGui();
		virtual void OnEnter();
		virtual void OnExit();

		void CopyToBackbuffer();

		void PushCameraController(const std::shared_ptr<CameraController> & aCameraController);
		void PopCameraController();
		bool IsCameraControllerActive(const std::shared_ptr<CameraController>& aCameraController) const;

		template <typename TComponentType>
		void PreCreateComponentFactory();

		template <typename TComponentType>
		void PreCreateComponentFactory(const unsigned short aAmountOfComponents);

		ObjectPtr CreateAndAddModel(const std::string & aIdentifier, const std::string & aPath, const Vector3f & aPosition, const Vector3f & aScale = Vector3f::One, const Quaternion & aOrientation = Quaternion());
		ObjectPtr CreateObjectWithModel(const std::string & aIdentifier, const std::shared_ptr<Model> & aModel, const Vector3f & aPosition, const Vector3f & aScale = Vector3f::One, const Quaternion & aOrientation = Quaternion());
		
		const Camera & GetCamera() const;
		const std::string & GetName() const;

		void CreateGameObjectBuffer(const unsigned short aObjectCount);

		ObjectPtr CreateGameObjectFromPrefab(const std::string aIdentifier, const Vector3f & aPosition);
		ObjectPtr  CreateGameObject(const std::string & aIdentifier);
		void NotifyObjectInitialization(const ObjectPtr& aObject);
		void ReturnObject(GameObject & aPointer);

		void SetDefaultFactoryComponentAmount(const unsigned short aAmount);

		SceneSystems & GetSystems()
		{
			return *mySystems;
		}

		SP::PhysicsManager & GetPhysicsManager()
		{
			return GetSystems().GetPhysicsManager();
		}

		inline std::shared_ptr<GuiRenderTarget> GetGUIRenderTarget()
		{
			return myGuiRenderTarget;
		}

		std::shared_ptr<ParticleSystem> GetParticleSystem();

		template <typename TComponentType>
		std::shared_ptr<ComponentFactory<TComponentType>> GetComponentFactory();

		template <typename TComponentType>
		const std::shared_ptr<ComponentFactory<TComponentType>> GetComponentFactory()const;

		ObjectPtr FindObject(const std::string & aObjectIdentifier);

		std::shared_ptr<RootGUIElement> GetGUI();
		void IncrementRemovalCounter();

		unsigned short GetNumberOfObjects();

		// Prepares all components and resources in the scene added to the scene
		// Returns immediately if aLoadasynchronously is true
		// Returns true if the scene is ready for playing or false if something is still not loaded
		// Always returns true if aLoadAsynchronously is false
		bool Prepare(bool aLoadAsynchronously);

		operator PostMasterState&() const;
		
		virtual void ToJson(JsonSerializer &aSerializer)const override;

		ReceiveResult Receive(const SaveLevelMessage & aMessage) override;
		ReceiveResult Receive(const WindowSizeChangedMessage& aMessage) override;

		bool ShouldLetThroughUpdate() const;
		bool ShouldLetThroughRender() const;

		void RegisterLightComponent(const PointLightComponent& aPointLightComponent);
		void RemoveLightComponent(const PointLightComponent& aPointLightComponent);

		template <typename TCallback>
		void WithAllComponentFactories(const TCallback & aCallback) const;

	protected:
		void SetSkybox(const char * aSkyboxPath);
		void SetCameraOrientation(const Vector3f & aCameraPosition, const Vector3f & aLookDirection = Vector3f(0.f, 0.f, 1.f));
		
		std::shared_ptr<RootGUIElement> myGUI;
		std::shared_ptr<GuiRenderTarget> myGuiRenderTarget;
		
		std::shared_ptr<ParticleSystem> myParticleSystem;
		std::unique_ptr<GameObjectFactory> myGameObjectFactory;
		GrowingArray<std::shared_ptr<BaseComponentFactory>, size_t> myFactories;

		std::unique_ptr<Camera> myCamera;
		
		Stack<std::shared_ptr<CameraController>> myCameraControllers;
		
		Time myTime;
		std::string myName;
		virtual void BindGUIFunctions();

		bool myShouldLetThroughUpdate;
		bool myShouldLetThroughRender;

		std::unique_ptr<SceneSystems> mySystems;

	private:
		
		GrowingArray<ObjectPtr> myObjects;
		std::unordered_map<std::string, ObjectPtr> myObjectDictionary;
		std::unordered_map<std::string, size_t> myObjectNameCounter;

		int myScheduledRemovals;
		unsigned short myDefaultComponentAmountSize;

		PostMasterState * myPostMasterState;

		std::shared_ptr<ConstantBuffer<TimeData>> myTimerBuffer;
		TimeData myTimerData;
	};

	static bool loadedSecondLevel = false;
	template<typename TComponentType>
	inline void Scene::PreCreateComponentFactory()
	{
		size_t id = UniqeIdentifier<BaseComponentFactory>::GetID<ComponentFactory<TComponentType>>();
		size_t nextID = UniqeIdentifier<BaseComponentFactory>::nextTypeIndex;
		if (myName == "Assets/Data/secondLevel.json")
		{
			loadedSecondLevel = true;
		}
		if (loadedSecondLevel == true && myName == "Assets/Data/tutorialLevel.json")
		{
			int a = 0;
			a;
		}
		if (myFactories.Size() < nextID)
		{
			myFactories.Resize(nextID, nullptr);
		}
		if (myFactories[id] != nullptr)
		{
			return;
		}
		myFactories[id] = std::make_shared<ComponentFactory<TComponentType>>(myDefaultComponentAmountSize);
	}

	template<typename TComponentType>
	inline void Scene::PreCreateComponentFactory(const unsigned short aAmountOfComponents)
	{
		size_t id = UniqeIdentifier<BaseComponentFactory>::GetID<ComponentFactory<TComponentType>>();
		size_t nextID = UniqeIdentifier<BaseComponentFactory>::nextTypeIndex;
		if (myFactories.Size() < nextID)
		{
			myFactories.Resize(nextID, nullptr);
		}
		if (myFactories[id] != nullptr)
		{
			return;
		}
		myFactories[id] = std::make_shared<ComponentFactory<TComponentType>>(aAmountOfComponents);
	}


	template <typename TComponentType>
	std::shared_ptr<ComponentFactory<TComponentType>> Scene::GetComponentFactory()
	{
		size_t id = UniqeIdentifier<BaseComponentFactory>::GetID<ComponentFactory<TComponentType>>();
		size_t nextID = UniqeIdentifier<BaseComponentFactory>::nextTypeIndex;
		if (myFactories.Size() < nextID || myFactories[id] == nullptr)
		{
			PreCreateComponentFactory<TComponentType>();
		}
		return std::static_pointer_cast<ComponentFactory<TComponentType>>(myFactories[id]);
	}

	template <typename TComponentType>
	const std::shared_ptr<ComponentFactory<TComponentType>> Scene::GetComponentFactory() const
	{
		size_t id = UniqeIdentifier<BaseComponentFactory>::GetID<ComponentFactory<TComponentType>>();
		if (id >= myFactories.Size())
		{
			return nullptr;
		}
		return std::static_pointer_cast<ComponentFactory<TComponentType>>(myFactories[id]);

	}

	template <typename TCallback>
	void Scene::WithAllComponentFactories(const TCallback& aCallback) const
	{
		for (unsigned short i=0; i<myFactories.Size(); i++)
		{
			if (myFactories[i] != nullptr)
			{
				aCallback(*myFactories[i]);
			}
		}
	}

	inline void Scene::SetDefaultFactoryComponentAmount(const unsigned short aAmount)
	{
		myDefaultComponentAmountSize = aAmount;
	}
}
