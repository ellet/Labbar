#include "stdafx.h"
#include "Engine\Scene\Scene.h"
#include "Engine\Model\ModelInstance.h"
#include "Engine\Texture\Texture.h"
#include "Engine\Camera\Skybox.h"
#include "Engine\Camera\Camera.h"
#include "Engine\Rendering\DXRenderer.h"
#include "Engine\Texture\RenderTexture.h"
#include "Engine\Buffer\DepthBuffer.h"
#include "Engine\Component\Factory\BaseComponentFactory.h"
#include "Engine\Camera\CameraController.h"
#include "Engine/Component\ModelComponent.h"
#include "Engine/Model/AssimpModel.h"
#include "Engine/Component/Factory/ComponentFactory.h"
#include "Engine/GameObject/GameObject.h"
#include <imgui.h>
#include <Engine/Effect/SkyboxEffect.h>
#include "..\Component\Collider\ColliderComponent.h"
#include "Engine\CollisionHandling\CollisionManager.h"
#include "Engine/GameObject/GameObjectFactory.h"
#include "Engine\Physics\PhysicsManager.h"
#include "..\CollisionHandling\ColliderData.h"
#include "..\GUI\GUILoader.h"
#include "Engine\GUI\RootGUIElement.h"

namespace ENGINE_NAMESPACE
{

	Scene::Scene(const char* aName, const char * aSkyboxPath)
	{
		myCamera = std::make_unique<Camera>();

		myName = aName;
		if (aSkyboxPath != nullptr)
		{
			std::shared_ptr<Effect> skyboxShader = std::make_shared<SkyboxEffect>();
			mySkybox = std::make_unique<ModelInstance>(std::make_shared<Skybox>(std::make_shared<Texture>(aSkyboxPath)));
			mySkybox->SetEffect(skyboxShader);
		}
		else
		{
			mySkybox = nullptr;
		}

		myScheduledRemovals = 0;

		myDefaultComponentAmountSize = 1024;

		myGameObjectFactory = std::make_unique<GameObjectFactory>();
		myFactories.Reserve(8);
		myPhysicsManager = std::make_unique<PhysicsManager>();

		GUILoader guildr(myBoundGUIFunctions);
		myGUI = guildr.LoadGUI("Assets/Data/Gui/TestGUI.json");

	}

	Scene::~Scene()
	{
		myObjectDictionary.clear();
		
		for (int i = static_cast<int>(myObjects.Size()) - 1; i >= 0; i--)
		{
			auto obj = myObjects[static_cast<unsigned short>(i)];
			obj->Remove();
		}
		
		myObjects.RemoveAll();
	}

	void DebugObject(GameObject & obj)
	{
		ImGui::Text(FormatString("Local Position {0};{1};{2}", obj.GetPosition().x, obj.GetPosition().y, obj.GetPosition().z).c_str());
		Matrix44f m = obj.GetTransformation();
		ImGui::Text(FormatString("World Position {0};{1};{2}", m.GetPosition().x, m.GetPosition().y, m.GetPosition().z).c_str());
		ImGui::Text(FormatString("Local Scale {0};{1};{2}", obj.GetScale().x, obj.GetScale().y, obj.GetScale().z).c_str());
		
		const GrowingArray<GameObject*> & children = obj.GetChildren();
		for (unsigned short i = 0; i < children.Size(); i++)
		{
			if (ImGui::CollapsingHeader(children[i]->GetIdentifier().c_str()))
			{
				DebugObject(*children[i]);
			}
		}
	}

	void Scene::Update(const Time & aDeltaTime)
	{
		myGUI->Update();
		if (myScheduledRemovals > 0)
		{
			for (int i = static_cast<int>(myObjects.Size()) - 1; i >= 0; i--)
			{
				if (myObjects[static_cast<unsigned short>(i)]->IsRemoved())
				{
					auto obj = myObjects[static_cast<unsigned short>(i)];

					myObjectDictionary.erase(myObjectDictionary.find(obj->GetIdentifier()));

					myObjects.RemoveCyclicAtIndex(static_cast<unsigned short>(i));

					myScheduledRemovals--;

					if (myScheduledRemovals == 0)
					{
						break;
					}
				}
			}

			myScheduledRemovals = 0;
		}

		if (ImGui::Begin("Objects in scene"))
		{
			for (unsigned short i = 0; i < myObjects.Size(); i++)
			{
				const ObjectPtr & obj = myObjects[i];
				if (obj->IsRemoved() == false)
				{
					if (obj->GetParent() == nullptr)
					{
						if (ImGui::CollapsingHeader(obj->GetIdentifier().c_str()))
						{
							DebugObject(*obj);
						}
					}
				}
			}
		}
		ImGui::End();

		for (size_t iFactory = 0; iFactory < myFactories.Size(); ++iFactory)
		{
			if (myFactories[iFactory] != nullptr)
			{
				myFactories[iFactory]->Update(aDeltaTime);
			}
		}

#ifdef DEBUG

		for (size_t iFactory = 0; iFactory < myFactories.Size(); ++iFactory)
		{
			if (myFactories[iFactory] != nullptr)
			{
				myFactories[iFactory]->DebugUpdate(aDeltaTime);
			}
		}

#endif // DEBUG

		myPhysicsManager->Update();

		if (myCameraControllers.Size() > 0)
		{
			std::shared_ptr<CameraController> & cc = myCameraControllers.Top();
			if (cc != nullptr)
			{
				CameraControllerResult result = cc->Update(aDeltaTime, *myCamera);
				if (result == CameraControllerResult::ePassControl)
				{
					myCameraControllers.Pop();
				}
			}
		}

		myTime += aDeltaTime;
	}

	void Scene::Render()
	{
		Engine::GetRenderer().ClearRenderTarget();
		Engine::GetRenderer().SetRenderTarget();
		myCamera->ApplyToVS();

		if (mySkybox != nullptr)
		{
			Engine::GetRenderer().DisableDepthWrite();
			mySkybox->SetMatrix(Matrix44f::CreateTranslation(myCamera->GetPosition()));
			mySkybox->InstantRender();
			Engine::GetRenderer().EnableDepth();
		}

		for (size_t iFactory = 0; iFactory < myFactories.Size(); ++iFactory)
		{
			if (myFactories[iFactory] != nullptr)
			{
				myFactories[iFactory]->Render();
			}
		}

#ifdef DEBUG

		for (size_t iFactory = 0; iFactory < myFactories.Size(); ++iFactory)
		{
			if (myFactories[iFactory] != nullptr)
			{
				myFactories[iFactory]->DebugRender();
			}
		}

#endif // DEBUG
		
		
		Engine::GetRenderer().Render();
		myGUI->Render();
	}

	void Scene::PushCameraController(const std::shared_ptr<CameraController> & aCameraController)
	{
		myCameraControllers.Push(aCameraController);
	}

	void Scene::SetCameraOrientation(const Vector3f & aCameraPosition, const Vector3f & aLookDirection /*= Vector3f(0.f, 0.f, 1.f)*/)
	{
		myCamera->SetPosition(aCameraPosition);
		myCamera->LookAt(aCameraPosition + aLookDirection);
	}

	void Scene::BindGUIFunctions()
	{

	}

	Camera& Scene::GetCamera()
	{
		return *myCamera;
	}
	const Camera & Scene::GetCamera() const
	{
		return *myCamera;
	}
	void Scene::CreateGameObjectBuffer(const unsigned short aObjectCount)
	{
		myObjects.Reserve(aObjectCount);
	}

	ObjectPtr Scene::CreateGameObject(const std::string & aIdentifier)
	{
		ObjectPtr gameObject;
		std::string id = aIdentifier;
		int counter = 0;
		while (myObjectDictionary.find(id) != myObjectDictionary.end())
		{
			id = aIdentifier + std::string(" (") + std::to_string(++counter) + std::string(")");
		}
		gameObject = myGameObjectFactory->CreateObject(*this, id);
		myObjectDictionary.emplace(id, gameObject);
		return gameObject;
	}

	void Scene::NotifyObjectInitialization(const ObjectPtr& aObject)
	{
		if (aObject->IsInitialized() == false)
		{
			Error("Tried to add uninitialized object to scene!");
		}
		myObjects.Add(aObject);
	}

	void Scene::ReturnObject(GameObject& aPointer)
	{
		myGameObjectFactory->ReturnMemory(aPointer.GetIndexInFactory());
	}


	void Scene::AddPhysicsComponentToPhysicsManager(PhysicsComponent & aPhysicsComponentToAdd)
	{
		myPhysicsManager->AddPhysicsComponent(aPhysicsComponentToAdd);
	}

	void Scene::RemovePhysicsComponentToPhysicsManager(PhysicsComponent & aPhysicsComponentToRemove)
	{
		myPhysicsManager->RemovePhysicsComponent(aPhysicsComponentToRemove);
	}

	void Scene::AddTriggerColliderToCollisionManager(const ColliderData & aColliderData)
	{
		myPhysicsManager->AddTriggerCollider(aColliderData);
	}

	void Scene::RemoveTriggerColliderFromCollisionManager(const ColliderData & aColliderData)
	{
		myPhysicsManager->RemoveTriggerCollider(aColliderData);
	}

	void Scene::AddCollisionColliderToCollisionManager(const ColliderData & aColliderData)
	{
		myPhysicsManager->AddCollisionCollider(aColliderData);
	}

	void Scene::RemoveCollisionColliderFromCollisionManager(const ColliderData & aColliderData)
	{
		myPhysicsManager->RemoveCollisionCollider(aColliderData);
	}

	ObjectPtr Scene::FindObject(const std::string& aObjectIdentifier)
	{
		auto && it = myObjectDictionary.find(aObjectIdentifier);

		if (it != myObjectDictionary.end())
		{
			return it->second;
		}

		return ObjectPtr();
	}

	std::shared_ptr<RootGUIElement> Scene::GetGUI()
	{
		return myGUI;
	}

	void Scene::IncrementRemovalCounter()
	{
		myScheduledRemovals++;
	}

	unsigned short Scene::GetNumberOfObjects()
	{
		return myObjects.Size();
	}

	ObjectPtr Scene::CreateAndAddModel(const std::string & aIdentifier, const std::string & aPath, const Vector3f & aPosition, const Vector3f & aScale /*= Vector3f::One*/, const Quaternion & aOrientation /*= Quaternion()*/)
	{
		return CreateObjectWithModel(aIdentifier, Engine::GetResourceManager().Get<AssimpModel>(aPath), aPosition, aScale, aOrientation);
	}

	ObjectPtr Scene::CreateObjectWithModel(const std::string & aIdentifier, const std::shared_ptr<Model> & aModel, const Vector3f & aPosition, const Vector3f & aScale /*= Vector3f::One*/, const Quaternion & aOrientation /*= Quaternion()*/)
	{
		ObjectPtr object = CreateGameObject(aIdentifier);
		object->SetPosition(aPosition);
		object->SetScale(aScale / 100.f);
		object->SetRotation(aOrientation);

		object->CreateComponent<ModelComponent>()->SetModel(aModel);

		return object;
	}

	void Scene::UpdatePerspective(float aFoV, float aWidth, float aHeight, float aNearPlane, float aFarPlane) const
	{
		myCamera->CreatePerspective(aFoV, aWidth, aHeight, aNearPlane, aFarPlane);
	}

}
