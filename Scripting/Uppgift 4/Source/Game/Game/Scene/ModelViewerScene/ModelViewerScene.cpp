#include "stdafx.h"
#include "ModelViewerScene.h"
#include "Engine\Camera\Controllers\FreeSpaceCameraController.h"
#include "Engine\Window\WindowMessage.h"
#include "Engine/Debugging/DebugGUI/BaseDebugGUI.h"
#include "Engine/Component/ModelComponent.h"
#include "Engine/Camera/Camera.h"

namespace SB
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

		ImGui::Begin("ModelViewer", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove);
		SB::DebugGUI::SetElementsWidth(200.f);

		SB::DebugGUI::SetWindowPosition(SB::Vector2f(5.f, 5.f));
		SB::DebugGUI::SetDebugGUISize(SB::Vector2f(250.f, 700.f));

		SB::DebugGUI::PrintText("Currently Loaded Mesh: ");
		SB::DebugGUI::PrintText(myModelGameObject->GetComponent<ModelComponent>()->GetNameOfLastRenderedMesh());

		SB::DebugGUI::PrintText("Meshes in model: ");
		for (unsigned short iMesh = 0; iMesh < myMeshNames.Size(); ++iMesh)
		{
			SB::DebugGUI::PrintText(myMeshNames[iMesh]);
		}

		ImGui::End();

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
				myCamera->SetSkybox(aMessage.data.FileDropEvent.myFilePath->c_str());
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

		myModelGameObject->GetComponent<ModelComponent>()->GetNamesOfAllMeshes(myMeshNames);

		if (aFixScaleFlag == true)
		{
			// myModelGameObject->SetScale(Vector3f(0.01f, 0.01f, 0.01f));
		}

		myModelGameObject->Initialize();
	}

}
