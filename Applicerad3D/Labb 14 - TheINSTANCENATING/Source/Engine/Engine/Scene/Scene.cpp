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
#include "Engine/ParticleSystem/ParticleSystem.h"

namespace ENGINE_NAMESPACE
{

	Scene::Scene(PostMasterState & aPostMasterState, const char* aName, const char * aSkyboxPath)
	{
		myPostMasterState = &aPostMasterState;

		myCamera = std::make_unique<Camera>();

		myName = aName;
		if (aSkyboxPath != nullptr)
		{
			SetSkyBox(aSkyboxPath);
		}
		else
		{
			mySkybox = nullptr;
		}

		myScheduledRemovals = 0;

		myDefaultComponentAmountSize = 1024;

		myGameObjectFactory = std::make_unique<GameObjectFactory>();
		myParticleSystem = std::make_shared<ParticleSystem>(*this);
		myFactories.Reserve(8);
		myPhysicsManager = std::make_unique<PhysicsManager>();
	}

	Scene::~Scene()
	{
		for (unsigned short i = 0; i < myObjects.Size(); i++)
		{
			if (myObjects[i]->GetParent() == nullptr)
			{
				myObjects[i]->Remove();
			}
		}

		for (unsigned short i = 0; i < myObjects.Size(); i++)
		{
			if (myObjects[i]->IsRemoved() == false)
			{
				Error("Something went wrong");
			}
		}
		myObjects.RemoveAll();
		myObjectDictionary.clear();

		myGameObjectFactory = nullptr;
		myFactories.RemoveAll();
	}

	void DebugObject(GameObject & obj)
	{
		ImGui::Text(FormatString("Local Position {0};{1};{2}", obj.GetPosition().x, obj.GetPosition().y, obj.GetPosition().z).c_str());
		Matrix44f m = obj.GetTransformation();
		ImGui::Text(FormatString("World Position {0};{1};{2}", m.GetPosition().x, m.GetPosition().y, m.GetPosition().z).c_str());
		ImGui::Text(FormatString("Local Scale {0};{1};{2}", obj.GetScale().x, obj.GetScale().y, obj.GetScale().z).c_str());
		
		const GrowingArray<ObjectPtr> & children = obj.GetChildren();
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
		PostMasterStateBinding bind = PostMaster::Push(*this);

		if (myGUI != nullptr)
		{
			myGUI->Update();
		}
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

		//if (ImGui::Begin("Objects in scene"))
		//{
		//	for (unsigned short i = 0; i < myObjects.Size(); i++)
		//	{
		//		const ObjectPtr & obj = myObjects[i];
		//		if (obj->IsRemoved() == false)
		//		{
		//			if (obj->GetParent() == nullptr)
		//			{
		//				if (ImGui::CollapsingHeader(obj->GetIdentifier().c_str()))
		//				{
		//					DebugObject(*obj);
		//				}
		//			}
		//		}
		//	}
		//}
		//ImGui::End();

		for (size_t iFactory = 0; iFactory < myFactories.Size(); ++iFactory)
		{
			if (myFactories[iFactory] != nullptr)
			{
				myFactories[iFactory]->Update(aDeltaTime);
			}
		}

#ifdef LD

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

		myParticleSystem->Update(aDeltaTime);

		myTime += aDeltaTime;
	}

	void Scene::RenderGui()
	{
		if (myGUI != nullptr)
		{
			myGUI->Render();
		}
	}

	void Scene::Render()
	{
		PostMasterStateBinding bind = PostMaster::Push(*this);

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


		

		Engine::GetRenderer().GetModelRenderer().RenderBuffer();

		myParticleSystem->Render();
	}


	void Scene::DebugRender()
	{
		for (size_t iFactory = 0; iFactory < myFactories.Size(); ++iFactory)
		{
			if (myFactories[iFactory] != nullptr)
			{
				myFactories[iFactory]->DebugRender();
			}
		}
	}

	void Scene::OnEnter()
	{
		PostMaster::Post<>(SaveLevelMessage());


		PostMaster::AssertState(*this);
		SB::Engine::GetGUILoader().SetFunctions(myBoundGUIFunctions);
		PostMaster::Post<ShowCursorMessage>(ShowCursorMessage(true));
		PostMaster::Post<ChangeCursorMessage>(ChangeCursorMessage(eCursorState::eNormal));
	}

	void Scene::OnExit()
	{
		PostMaster::AssertState(*this);
		PostMaster::Post<ShowCursorMessage>(ShowCursorMessage(true));
		PostMaster::Post<ChangeCursorMessage>(ChangeCursorMessage(eCursorState::eNormal));
	}

	void Scene::PushCameraController(const std::shared_ptr<CameraController> & aCameraController)
	{
		myCameraControllers.Push(aCameraController);
	}

	void Scene::PopCameraController()
	{
		myCameraControllers.Pop();
	}

	bool Scene::IsCameraControllerActive(const std::shared_ptr<CameraController> & aCameraController) const
	{
		return myCameraControllers.Top() == aCameraController;
	}


	void Scene::SetSkyBox(const std::string & aSkyboxPath)
	{
		std::shared_ptr<Effect> skyboxShader = std::make_shared<SkyboxEffect>();
		mySkybox = std::make_unique<ModelInstance>(std::make_shared<Skybox>(std::make_shared<Texture>(aSkyboxPath)));
		mySkybox->SetEffect(skyboxShader);

		Engine::GetRenderer().GetModelRenderer().SetSkyBox(aSkyboxPath);
	}

	void Scene::SetCameraOrientation(const Vector3f & aCameraPosition, const Vector3f & aLookDirection /*= Vector3f(0.f, 0.f, 1.f)*/)
	{
		myCamera->SetPosition(aCameraPosition);
		myCamera->LookAt(aCameraPosition + aLookDirection);
	}

	void Scene::BindGUIFunctions()
	{
	}

	const Camera & Scene::GetCamera() const
	{
		return *myCamera;
	}

	const std::string & Scene::GetName() const
	{
		return myName;
	}

	void Scene::CreateGameObjectBuffer(const unsigned short aObjectCount)
	{
		myObjects.Reserve(aObjectCount);
	}

	ObjectPtr Scene::CreateGameObjectFromPrefab(const std::string aIdentifier)
	{
		PostMaster::AssertState(*this);

		return myGameObjectFactory->CreateObjectFromPrefab(*this, aIdentifier);
	}

	ObjectPtr Scene::CreateGameObject(const std::string & aIdentifier)
	{
		PostMaster::AssertState(*this);

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

	bool Scene::RayTraceAllObjectsInScene(const RayCollider & aCollider, CollisionData & aCollisionDataToBuild)
	{
		return myPhysicsManager->RayTrace(aCollider, aCollisionDataToBuild);
	}

	bool Scene::RayTraceAllObjectsInScene(const RayCollider & aCollider, GrowingArray<CollisionData> & aCollisionDataToBuild)
	{
		return myPhysicsManager->RayTrace(aCollider, aCollisionDataToBuild);
	}

	std::shared_ptr<ParticleSystem> Scene::GetParticleSystem()
	{
		return myParticleSystem;
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

	bool Scene::Prepare(bool aLoadAsynchronously)
	{
		bool isReady = true;

		for (size_t iFactory = 0; iFactory < myFactories.Size(); ++iFactory)
		{
			if (myFactories[iFactory] != nullptr)
			{
				if (myFactories[iFactory]->Prepare(aLoadAsynchronously) == false)
				{
					isReady = false;
				}
			}
		}

		return isReady;
	}

	Scene::operator PostMasterState&() const
	{
		return *myPostMasterState;
	}

	void Scene::ToJson() const
{
		JsonSerializer& serializer = Engine::GetJsonSerializer();

		serializer.WriteNode("name", myName);

		serializer.WriteArray("hierarchy");

		//Serialize all objects in scene
		for(unsigned short i = 0; i < myObjects.Size(); ++i)
		{
			if (myObjects[i]->IsRemoved() == false)
			{
				if (myObjects[i]->GetShouldBeSaved() == true)
				{
					serializer.WriteObject();
					myObjects[i]->ToJson();
					serializer.StepOut();
				}
			}
		}

		serializer.StepOut();
	}


	ReceiveResult Scene::Receive(const SaveLevelMessage & aMessage)
	{
		JsonSerializer& serializer = Engine::GetJsonSerializer();
		serializer.OpenSaveFile();
		ToJson();
		serializer.CloseSaveFile();
		return ReceiveResult::eContinue;
	}

	ObjectPtr Scene::CreateAndAddModel(const std::string & aIdentifier, const std::string & aPath, const Vector3f & aPosition, const Vector3f & aScale /*= Vector3f::One*/, const Quaternion & aOrientation /*= Quaternion()*/)
	{
		return CreateObjectWithModel(aIdentifier, Engine::GetResourceManager().Get<AssimpModel>(aPath), aPosition, aScale, aOrientation);
	}

	ObjectPtr Scene::CreateObjectWithModel(const std::string & aIdentifier, const std::shared_ptr<Model> & aModel, const Vector3f & aPosition, const Vector3f & aScale /*= Vector3f::One*/, const Quaternion & aOrientation /*= Quaternion()*/)
	{
		ObjectPtr object = CreateGameObject(aIdentifier);
		object->SetPosition(aPosition);
		object->SetRotation(aOrientation);

		object->CreateComponent<ModelComponent>()->SetModel(aModel);

		return object;
	}

	void Scene::UpdatePerspective(float aFoV, float aWidth, float aHeight, float aNearPlane, float aFarPlane) const
	{
		myCamera->CreatePerspective(aFoV, aWidth, aHeight, aNearPlane, aFarPlane);
	}

}
