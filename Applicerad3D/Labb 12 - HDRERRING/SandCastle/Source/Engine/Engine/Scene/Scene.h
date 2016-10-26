#pragma once
#include "Utilities\Container\GrowingArray.h"

namespace ENGINE_NAMESPACE
{

	enum class eSceneType
	{
		eMajor,
		eSub
	};

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

	class RootGUIElement;

	class Scene
	{
	public:
		Scene(const char* aName = "", const char* aSkyboxPath = nullptr);
		virtual ~Scene();

		virtual void Update(const Time & aDeltaTime);
		virtual void Render();

		void PushCameraController(const std::shared_ptr<CameraController> & aCameraController);

		template <typename TComponentType>
		void PreCreateComponentFactory();

		template <typename TComponentType>
		void PreCreateComponentFactory(const unsigned short aAmountOfComponents);

		void UpdatePerspective(float aFoV, float aWidth, float aHeight, float aNearPlane, float aFarPlane) const;

		ObjectPtr CreateAndAddModel(const std::string & aIdentifier, const std::string & aPath, const Vector3f & aPosition, const Vector3f & aScale = Vector3f::One, const Quaternion & aOrientation = Quaternion());
		ObjectPtr CreateObjectWithModel(const std::string & aIdentifier, const std::shared_ptr<Model> & aModel, const Vector3f & aPosition, const Vector3f & aScale = Vector3f::One, const Quaternion & aOrientation = Quaternion());
		
		Camera& GetCamera();
		const Camera & GetCamera() const;

		void CreateGameObjectBuffer(const unsigned short aObjectCount);

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


		template <typename TComponentType>
		std::shared_ptr<ComponentFactory<TComponentType>> GetComponentFactory();

		template <typename TComponentType>
		const std::shared_ptr<ComponentFactory<TComponentType>> GetComponentFactory()const;

		ObjectPtr FindObject(const std::string & aObjectIdentifier);

		std::shared_ptr<RootGUIElement> GetGUI();
		void IncrementRemovalCounter();
		unsigned short GetNumberOfObjects();
	protected:
		void SetCameraOrientation(const Vector3f & aCameraPosition, const Vector3f & aLookDirection = Vector3f(0.f, 0.f, 1.f));
		std::shared_ptr<RootGUIElement> myGUI;
		std::unordered_map<std::string, std::function<void()>> myBoundGUIFunctions;
		std::unique_ptr<GameObjectFactory> myGameObjectFactory;
		GrowingArray<std::shared_ptr<BaseComponentFactory>, size_t> myFactories;

		std::unique_ptr<ModelInstance> mySkybox;

		std::unique_ptr<Camera> myCamera;
		
		Stack<std::shared_ptr<CameraController>> myCameraControllers;
		
		Time myTime;
		std::string myName;

		virtual void BindGUIFunctions();

	private:
		std::unique_ptr<PhysicsManager> myPhysicsManager;
		GrowingArray<ObjectPtr> myObjects;
		std::unordered_map<std::string, ObjectPtr> myObjectDictionary;

		int myScheduledRemovals;
		unsigned short myDefaultComponentAmountSize;
	};
	template<typename TComponentType>
	inline void Scene::PreCreateComponentFactory()
	{
		size_t id = UniqeIdentifier<BaseComponentFactory>::GetID<ComponentFactory<TComponentType>>();
		size_t nextID = UniqeIdentifier<BaseComponentFactory>::nextTypeIndex;
		if (myFactories.Size() < nextID)
		{
			myFactories.Resize(nextID);
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
			myFactories.Resize(nextID);
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
