#pragma once
#include "Messages\SaveSceneMessage.h"
namespace ENGINE_NAMESPACE
{
	class GameObject;
	class ObjectPtr;
	class BaseComponentFactory;

	class GameObjectFactory;
	template <typename TComponentFactoryType>
	class ComponentFactory;

	class Camera;
	class CameraController;

	class PhysicsManager;
	class PhysicsComponent;
	class SphereCollider;

	class Model;
	class ModelInstance;
	struct ColliderData;
	struct CollisionData;

	class RootGUIElement;
	class GUILoader;

	class ParticleSystem;

	class Scene : public JsonObject, public Subscriber<SaveLevelMessage>
	{
	public:
		Scene(PostMasterState & aPostMasterState, const char* aName, const char* aSkyboxPath = "Assets/Skyboxes/skybox4_16f.dds");
		virtual ~Scene();

		virtual void Update(const Time & aDeltaTime);
		virtual void Render();
		virtual void DebugRender();
		virtual void RenderGui();

		virtual void OnEnter();
		virtual void OnExit();

		void PushCameraController(const std::shared_ptr<CameraController> & aCameraController);
		void PopCameraController();
		bool IsCameraControllerActive(const std::shared_ptr<CameraController>& aCameraController) const;

		template <typename TComponentType>
		void PreCreateComponentFactory();

		template <typename TComponentType>
		void PreCreateComponentFactory(const unsigned short aAmountOfComponents);

		void UpdatePerspective(float aFoV, float aWidth, float aHeight, float aNearPlane, float aFarPlane) const;

		ObjectPtr CreateAndAddModel(const std::string & aIdentifier, const std::string & aPath, const Vector3f & aPosition, const Vector3f & aScale = Vector3f::One, const Quaternion & aOrientation = Quaternion());
		ObjectPtr CreateObjectWithModel(const std::string & aIdentifier, const std::shared_ptr<Model> & aModel, const Vector3f & aPosition, const Vector3f & aScale = Vector3f::One, const Quaternion & aOrientation = Quaternion());
		
		const Camera & GetCamera() const;
		const std::string & GetName() const;

		void CreateGameObjectBuffer(const unsigned short aObjectCount);

		ObjectPtr CreateGameObjectFromPrefab(const std::string aIdentifier);
		ObjectPtr  CreateGameObject(const std::string & aIdentifier);
		void NotifyObjectInitialization(const ObjectPtr& aObject);
		void ReturnObject(GameObject & aPointer);

		void SetDefaultFactoryComponentAmount(const unsigned short aAmount);

		void AddPhysicsComponentToPhysicsManager(PhysicsComponent & aPhysicsComponentToAdd );
		void RemovePhysicsComponentToPhysicsManager(PhysicsComponent & aPhysicsComponentToRemove);

		void AddTriggerColliderToCollisionManager(const ColliderData & aColliderData);
		void RemoveTriggerColliderFromCollisionManager(const ColliderData & aColliderData);

		void AddCollisionColliderToCollisionManager(const ColliderData & aColliderData);
		void RemoveCollisionColliderFromCollisionManager(const ColliderData & aColliderData);

		bool RayTraceAllObjectsInScene(const RayCollider & aCollider, CollisionData & aCollisionDataToBuild);
		bool RayTraceAllObjectsInScene(const RayCollider & aCollider, GrowingArray<CollisionData> & aCollisionDataToBuild);

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
		
		virtual void ToJson()const override;

		virtual ReceiveResult Receive(const SaveLevelMessage & aMessage) override;

	protected:
		void SetSkyBox(const std::string & aSkyboxPath);
		void SetCameraOrientation(const Vector3f & aCameraPosition, const Vector3f & aLookDirection = Vector3f(0.f, 0.f, 1.f));
		std::shared_ptr<RootGUIElement> myGUI;
		std::shared_ptr<ParticleSystem> myParticleSystem;
		std::unordered_map<std::string, std::function<void()>> myBoundGUIFunctions;
		std::unique_ptr<GameObjectFactory> myGameObjectFactory;
		GrowingArray<std::shared_ptr<BaseComponentFactory>, size_t> myFactories;

		std::unique_ptr<ModelInstance> mySkybox;
		std::unique_ptr<Camera> myCamera;
		
		Stack<std::shared_ptr<CameraController>> myCameraControllers;
		
		Time myTime;
		std::string myName;

		virtual void BindGUIFunctions();

		std::unique_ptr<PhysicsManager> myPhysicsManager;

	private:
		
		GrowingArray<ObjectPtr> myObjects;
		std::unordered_map<std::string, ObjectPtr> myObjectDictionary;

		int myScheduledRemovals;
		unsigned short myDefaultComponentAmountSize;

		PostMasterState * myPostMasterState;
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
		return std::static_pointer_cast<ComponentFactory<TComponentType>>(myFactories[id]);

	}

	inline void Scene::SetDefaultFactoryComponentAmount(const unsigned short aAmount)
	{
		myDefaultComponentAmountSize = aAmount;
	}
}
