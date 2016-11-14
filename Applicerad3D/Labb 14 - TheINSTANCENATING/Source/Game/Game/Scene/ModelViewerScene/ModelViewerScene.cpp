#include "stdafx.h"
#include "ModelViewerScene.h"
#include "Engine\Camera\Controllers\FreeSpaceCameraController.h"
#include "Engine\Window\WindowMessage.h"

namespace ENGINE_NAMESPACE
{

	ModelViewerScene::ModelViewerScene(SB::PostMasterState & aPostMasterState) : Scene(aPostMasterState, "ModelViewer")
	{
		PostMasterStateBinding bind = PostMaster::Push(*this);
		
		myFileDropListener = std::make_shared<Subscription<WindowMessage>>(
		[this](const WindowMessage& aMessage) -> ReceiveResult
		{
			return this->Receive(aMessage);
		});

		LoadModel("Assets/Models/PBL_Spheres/testSpheres.fbx", false);

		PushCameraController(std::make_shared<FreeSpaceCameraController>(15.f, 2.5f));
	}


	ModelViewerScene::~ModelViewerScene()
	{
		PostMasterStateBinding bind = PostMaster::Push(*this);

		myFileDropListener = nullptr;
	}

	void ModelViewerScene::Update(const Time & aDeltaTime)
	{
		PostMaster::Post<ShowCursorMessage>(ShowCursorMessage(true));
		PostMaster::Post(ConfineMouseMessage(false));
		Scene::Update(aDeltaTime);
	}

	void ModelViewerScene::Render()
	{
		Scene::Render();
	}

	void ModelViewerScene::DebugRender()
	{
		Scene::DebugRender();
	}

	void ModelViewerScene::OnEnter()
	{
		Scene::OnEnter();
		
	}

	ReceiveResult ModelViewerScene::Receive(const WindowMessage& aMessage)
	{
		if (aMessage.type == WindowMessageType::eFileDrop)
		{
			if (aMessage.data.FileDropEvent.myFileExtension == FileExtensionsEnum::eFBX)
			{
				LoadModel(*aMessage.data.FileDropEvent.myFilePath);
			}
			else if (aMessage.data.FileDropEvent.myFileExtension == FileExtensionsEnum::eDDS)
			{
				SetSkyBox(*aMessage.data.FileDropEvent.myFilePath);
			}
		}

		return ReceiveResult::eContinue;
	}


	void ModelViewerScene::LoadModel(const std::string & aPathToFileToLoad, const bool aFixScaleFlag)
	{
		if (myModelGameObject != nullptr)
		{
			myModelGameObject->Remove();
			myModelGameObject = ObjectPtr();
		}

		myModelGameObject = CreateAndAddModel("ModelObject", aPathToFileToLoad, Vector3f(0.f, 0.f, 25.f));

		if (aFixScaleFlag == true)
		{
			myModelGameObject->SetScale(Vector3f(0.01f, 0.01f, 0.01f));
		}

		myModelGameObject->Initialize();
	}

}
