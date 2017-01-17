#include "stdafx.h"
#include "Engine\Scene\Scene.h"
#include "Engine\Model\ModelInstance.h"
#include "Engine\Texture\TextureCube.h"
#include "Engine\Camera\Skybox.h"
#include "Engine\Camera\Camera.h"
#include "Engine\Rendering\DXRenderer.h"
#include "Engine\Component\Factory\BaseComponentFactory.h"
#include "Engine\Camera\CameraController.h"
#include "Engine/Component\ModelComponent.h"
#include "Engine/Model/AssimpModel.h"
#include "Engine/GameObject/GameObject.h"
#include <imgui.h>
#include <Engine/Effect/SkyboxEffect.h>
#include "..\Component\Collider\ColliderComponent.h"
#include "Engine/GameObject/GameObjectFactory.h"
#include "Engine\GUI\RootGUIElement.h"
#include "Engine/ParticleSystem/ParticleSystem.h"
#include "..\Texture\TextureDebugger.h"
#include <Utilities/Randomizer/Randomizer.h>
#include "Engine/Texture/WorldRenderTexture.h"
#include "Engine/Texture/GuiRenderTarget.h"
#include "Engine/Rendering/PostProcessor.h"
#include "SceneSystems\SceneSystems.h"

namespace SB
{
	Scene::Scene(PostMasterState & aPostMasterState, const char* aName, const char * aSkyboxPath)
	{
		myShouldLetThroughUpdate = false;
		myShouldLetThroughRender = false;

		myPostMasterState = &aPostMasterState;

		mySystems = std::make_unique<SceneSystems>();

		myCamera = std::make_unique<Camera>(aSkyboxPath);
		Vector2ui size = Engine::GetRenderer().GetRenderTargetResolution().As<unsigned int>();
		myGuiRenderTarget = std::make_shared<GuiRenderTarget>(size.x, size.y);

		myName = aName;

		myScheduledRemovals = 0;

		myDefaultComponentAmountSize = 1024;

		myGameObjectFactory = std::make_unique<GameObjectFactory>();
		myParticleSystem = std::make_shared<ParticleSystem>(*this);
		myFactories.Reserve(8);
		

		myTimerBuffer = std::make_shared<ConstantBuffer<TimeData>>();
		myTimerData.timer.x = 0.f;

		myCamera->CreatePerspective(60.f, Engine::GetRenderer().GetRenderTargetResolution().x, Engine::GetRenderer().GetRenderTargetResolution().y, 0.01f, FAR_PLANE_DISTANCE);
	}

	Scene::~Scene()
	{
		myCameraControllers.PopAll();

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
		myTimerData.timer.x += (aDeltaTime.InSeconds() * 2.5f);
		myTimerBuffer->UpdateData(myTimerData);
		myTimerBuffer->BindToPS(7);

		PostMasterStateBinding bind = PostMaster::Push(*this);

		GetSystems().Update(aDeltaTime);

		for (size_t iFactory = 0; iFactory < myFactories.Size(); ++iFactory)
		{
			if (myFactories[iFactory] != nullptr)
			{
				myFactories[iFactory]->BeginUpdate(aDeltaTime);
			}
		}

		if (myGUI != nullptr)
		{
			myGUI->Update(aDeltaTime);

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

		for (size_t iFactory = 0; iFactory < myFactories.Size(); ++iFactory)
		{
			if (myFactories[iFactory] != nullptr)
			{
				myFactories[iFactory]->EndUpdate(aDeltaTime);
			}
		}

		myTime += aDeltaTime;
	}

	void Scene::RenderGui()
	{
		myGuiRenderTarget->Bind(0);

		if (myGUI != nullptr)
		{
			RenderingEventGroup event(L"GUI");

			myGUI->Render(*myGuiRenderTarget);
		}

		//myParticleSystem->RenderAboveGUIParticles();
	}

	void Scene::Render()
	{
		PostMasterStateBinding bind = PostMaster::Push(*this);

		GetSystems().Render();

		myCamera->RenderScene(*this, &*myParticleSystem);
	}

	void Scene::DebugRender()
	{
		for (size_t iFactory = 0; iFactory < myFactories.Size(); ++iFactory)
		{
			if (myFactories[iFactory] != nullptr)
			{
				myFactories[iFactory]->DebugRender(*myCamera);
			}
		}
	}

	void Scene::OnEnter()
	{
		PostMaster::AssertState(*this);
		PostMaster::Post<ShowCursorMessage>(ShowCursorMessage(true));
		PostMaster::Post<>(EnterSceneMessage(GetName().c_str()));
		PostMaster::Post<ChangeCursorMessage>(ChangeCursorMessage(eCursorState::eNormal));
	}

	void Scene::OnExit()
	{
		PostMaster::AssertState(*this);
		PostMaster::Post<ShowCursorMessage>(ShowCursorMessage(true));
		PostMaster::Post<>(ExitSceneMessage(GetName().c_str()));
		PostMaster::Post<ChangeCursorMessage>(ChangeCursorMessage(eCursorState::eNormal));
	}

	void Scene::CopyToBackbuffer()
	{
		myCamera->RenderBuffer();
		Engine::GetRenderer().DoFullscreenEffects(myCamera->GetRenderTexture());
		Engine::GetRenderer().GetPostProcessor().CopyRenderTexture(Engine::GetRenderer().GetBackBuffer(), myCamera->GetRenderTexture()->GetTexture(WorldRenderTarget::eDiffuse));
		myCamera->GetRenderTexture()->Clear(Vector4f::Zero);

		myGuiRenderTarget->RenderBuffer();
		Engine::GetRenderer().GetPostProcessor().CopyRenderTexture(Engine::GetRenderer().GetBackBuffer(), myGuiRenderTarget->GetTexture(0));
		myGuiRenderTarget->Clear(Vector4f::Zero);
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

	void Scene::SetSkybox(const char * aSkyboxPath)
	{
		myCamera->SetSkybox(aSkyboxPath);
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

	ObjectPtr Scene::CreateGameObjectFromPrefab(const std::string aIdentifier, const Vector3f & aPosition)
	{
		PostMaster::AssertState(*this);

		return myGameObjectFactory->CreateObjectFromPrefab(*this, aIdentifier, aPosition);
	}

	ObjectPtr Scene::CreateGameObject(const std::string & aIdentifier)
	{
		PostMaster::AssertState(*this);

		auto && it = myObjectNameCounter.find(aIdentifier);
		if (it != myObjectNameCounter.end())
		{
			it->second++;
			std::string newName = FormatString("{0} ({1})", aIdentifier, it->second);
			if (myObjectDictionary.find(newName) != myObjectDictionary.end())
			{
				return CreateGameObject(aIdentifier);
			}
			ObjectPtr gameObject = myGameObjectFactory->CreateObject(*this, newName);
			myObjectDictionary.emplace(newName, gameObject);
			return gameObject;
		}
		else
		{
			myObjectNameCounter.emplace(aIdentifier, 1);
			if (myObjectDictionary.find(aIdentifier) != myObjectDictionary.end())
			{
				return CreateGameObject(aIdentifier);
			}
			ObjectPtr gameObject = myGameObjectFactory->CreateObject(*this, aIdentifier);
			myObjectDictionary.emplace(aIdentifier, gameObject);
			return gameObject;
		}
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

	void Scene::ToJson(JsonSerializer &aSerializer) const 
{

		JsonSerializer& serializer = aSerializer;

		serializer.WriteNode("name", myName);

		serializer.WriteArray("hierarchy");

		//Serialize all objects in scene
		for (unsigned short i = 0; i < myObjects.Size(); ++i)
		{
			if (myObjects[i]->GetParent() == nullptr && myObjects[i]->IsRemoved() == false)
			{
				if (myObjects[i]->GetShouldBeSaved() == true)
				{
					serializer.WriteObject();
					myObjects[i]->ToJson(aSerializer);
					serializer.StepOut();
				}
			}
		}

		serializer.StepOut();
	}


	ReceiveResult Scene::Receive(const SaveLevelMessage & aMessage)
	{
		JsonSerializer serializer(Engine::GetJsonSerializer().c_str());
		ToJson(serializer);
		return ReceiveResult::eContinue;
	}

	ReceiveResult Scene::Receive(const WindowSizeChangedMessage& aMessage)
	{
		myCamera->CreatePerspective(60.f, Engine::GetRenderer().GetRenderTargetResolution().x, Engine::GetRenderer().GetRenderTargetResolution().y, 0.01f, FAR_PLANE_DISTANCE);
		return ReceiveResult::eContinue;
	}

	bool Scene::ShouldLetThroughUpdate() const
	{
		return myShouldLetThroughUpdate;
	}

	bool Scene::ShouldLetThroughRender() const
	{
		return myShouldLetThroughRender;
	}

	void Scene::RegisterLightComponent(const PointLightComponent& aPointLightComponent)
	{
		myCamera->GetRenderTexture()->GetModelRenderer().RegisterLightComponent(aPointLightComponent);
	}

	void Scene::RemoveLightComponent(const PointLightComponent& aPointLightComponent)
	{
		myCamera->GetRenderTexture()->GetModelRenderer().RemoveLightComponent(aPointLightComponent);
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
		object->SetScale(aScale);

		object->CreateComponent<ModelComponent>()->SetModel(aModel);

		return object;
	}

}
