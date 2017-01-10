#include "stdafx.h"
#include "ParticleEditorScene.h"
#include <Engine/ParticleSystem/ParticleSystem.h>
#include <Engine/ParticleSystem/ParticleEmitter.h>
#include <Engine/ParticleSystem/ParticleSystemStructs.h>
#include <Engine/Debugging/DebugGUI/BaseDebugGUI.h>
#include <Engine/GenericEngineMessages.h>
#include <Engine/Camera/Controllers/FreeSpaceCameraController.h>
#include <Engine\GUI\GUILoader.h>
#include <Engine/Texture/WorldRenderTexture.h>
#include "../Utilities/Utilities/StringFormatter.h"

ParticleEditorScene::ParticleEditorScene(SB::PostMasterState & aPostMasterState) : Scene(aPostMasterState, "Particle Editor")
{
	SB::PostMasterStateBinding bind = SB::PostMaster::Push(*this);
	myEmitterName = "EmitterName";
	myCamera->GetRenderTexture()->GetModelRenderer().SetDirectionalLight(0, SB::Vector3f::UnitZ, SB::Vector4f(1.f, 1.f, 1.f, 1.f));

	myAppliedTimer = 5.f;
	myDidntRenameTimer = 5.f;
	myDeletedTimer = 5.f;

	myAtlasTexture = myParticleSystem->GetAtlas();

	PushCameraController(std::make_shared<SB::FreeSpaceCameraController>(5.f, 1.5f));
	myCamera->SetPosition(SB::Vector3f(-2.f, 3.f, -10.f));
	SB::Quaternion looking;
	looking.RotateAroundLocalY(DEGREES_TO_RADIANSF(10));
	looking.RotateAroundLocalX(DEGREES_TO_RADIANSF(5));
	myCamera->SetOrientation(looking);
	SetupEmitterNames();
	BackupSave();

	myChosenEmitterIndex = 0;
	myEmitter = myParticleSystem->CreateEmitter(myEmitterTypeNames[myChosenEmitterIndex]);
	myEmitterSettings = myEmitter->GetSettingsForEditor();
	myEmitter->SetPositionOffset(SB::Vector3f(2.f, 0.f, 100.f));
	myShouldShowGrid = true;
	myShouldShowForceFields = false;
	myNumberOfGridLines = 8;
	myDistanceBetweenGridLines = 1.f;

	for (unsigned short i = 0; i < myEmitterSettings->myForceFieldsSettings.Size(); ++i)
	{
		myLocalForceFields.Add(SB::FormatString("# {0}", i));
	}

	myEditingForceField = nullptr;
	if (myEmitterSettings->myForceFieldsSettings.Size() > 0)
	{
		myEditingForceField = &myEmitterSettings->myForceFieldsSettings[0];
		myChosenForceField = myLocalForceFields[0];
	}
}

ParticleEditorScene::~ParticleEditorScene()
{
	myEmitter->ReturnEmitter();
	myEmitterSettings = nullptr;
	myEmitter = nullptr;
}

void ParticleEditorScene::Update(const SB::Time & aDeltaTime)
{	
	ImGui::Begin("ParticleEditor", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove);

	SB::DebugGUI::PrintText("Move using WASD, RF and arrow keys.\nCtrl-click a value to set it manually.", SB::Vector4f(0.f, 1.f, 1.f, 1.f));
	SetEmitterToEditor();


	if (HasErrors() == false)
	{
		myEmitter->Update(aDeltaTime, SB::Matrix44f::Zero);
		ImGui::End();

		ImGui::Begin("External", nullptr, ImGuiWindowFlags_NoCollapse);
		ChooseEmitterToEdit();
		HandleExternal();
		HandleActionTextAndAutosave(aDeltaTime);
	}
	else
	{
		ImGui::End();
		ImGui::Begin("External", nullptr, ImGuiWindowFlags_NoCollapse);
		ChooseEmitterToEdit();
		SB::DebugGUI::PrintText("EMITTER HAS INVALID VALUES!", SB::Vector4f(1.f, 0.f, 0.f, 1.f));
	}

	ImGui::End();
	HelpingWindow();
	ForceFieldWindow();

	Scene::Update(aDeltaTime);
}

void ParticleEditorScene::Render()
{
	Scene::Render();
	if (myShouldShowGrid == true)
	{
		MakeWorldGrid();
	}
	if (myShouldShowForceFields == true)
	{
		RenderForceFields();
	}
}

void ParticleEditorScene::OnEnter()
{
	SB::Engine::GetGUILoader().DisableGUI();
	SB::PostMaster::Post<SB::ShowCursorMessage>(SB::ShowCursorMessage(true));
	SB::PostMaster::Post<SB::ChangeCursorMessage>(SB::ChangeCursorMessage(SB::eCursorState::eNormal));
}

void ParticleEditorScene::ForceFieldWindow()
{
	ImGui::Begin("Local ForceFields", nullptr, 0);
	SB::DebugGUI::CheckBox(myShouldShowForceFields, "Show Local ForceFields");
	SB::DebugGUI::SetElementsWidth(100.f);

	if (myLocalForceFields.Size() > 0)
	{
		if (SB::DebugGUI::Combobox(myLocalForceFields, myChosenForceFieldIndex, myChosenForceField, "Local Forcefields") == true)
		{
			myEditingForceField = &myEmitterSettings->myForceFieldsSettings[myChosenForceFieldIndex];
		}

		SB::DebugGUI::PrintText("Forcefield Position");
		SB::DebugGUI::VectorSlider(myEditingForceField->myForceField.myPosition, SB::Vector2f(-1000.f, 1000.f));
		SB::DebugGUI::FloatSlider(myEditingForceField->myForceField.myRadius, SB::Vector2f(0.f, 1000.f), " : Radius");
		SB::DebugGUI::FloatSlider(myEditingForceField->myGravity, SB::Vector2f(-5000.f, 5000.f), " : Force");
	}

	if (SB::DebugGUI::Button("Create New ForceField", SB::Vector2f(100.f, 20.f)) == true)
	{
		AddLocalForceField();
	}

	ImGui::End();
}

void ParticleEditorScene::AddLocalForceField()
{
	myEmitterSettings->myForceFieldsSettings.Add(SB::ParticleForceField());
	myChosenForceFieldIndex = myEmitterSettings->myForceFieldsSettings.Size() - 1;
	myEditingForceField = &myEmitterSettings->myForceFieldsSettings.GetLast();
	myLocalForceFields.Add(SB::FormatString("# {0}", myChosenForceFieldIndex));
}

void ParticleEditorScene::HelpingWindow()
{
	ImGui::Begin("Grid", nullptr, 0);
	SB::DebugGUI::CheckBox(myShouldShowGrid, "Show Grid");
	SB::DebugGUI::SetElementsWidth(100.f);
	SB::DebugGUI::IntSetter(myNumberOfGridLines, "# Grid Lines");
	SB::DebugGUI::FloatSetter(myDistanceBetweenGridLines, "Segment Distance");
	ImGui::End();
}

void ParticleEditorScene::HandleActionTextAndAutosave(const SB::Time & aDeltaTime)
{
	myDidntRenameTimer += aDeltaTime;
	myAutoSaveTimer += aDeltaTime;
	mySaveTimer += aDeltaTime;
	myAppliedTimer += aDeltaTime;
	myDeletedTimer += aDeltaTime;

	if (myAppliedTimer.InSeconds() < 3.f)
	{
		SB::DebugGUI::PrintText("Applied Changes but Didn't Save to File", SB::Vector4f(0.f, 1.f, 0.f, 1.f));
	}	

	if (myAutoSaveTimer.InSeconds() > 40.f)
	{
		myAutoSaveTimer = 0.f;
		AutoSave();
	}
	else if (myAutoSaveTimer.InSeconds() < 3.f)
	{
		SB::DebugGUI::PrintText("Autosaved", SB::Vector4f(0.f, 1.f, 0.f, 1.f));
	}

	if (mySaveTimer.InSeconds() < 3.f)
	{
		SB::DebugGUI::PrintText("Saved", SB::Vector4f(0.f, 1.f, 0.f, 1.f));
	}

	if (myDeletedTimer.InSeconds() < 3.f)
	{
		SB::DebugGUI::PrintText("Deleted Emitter", SB::Vector4f(1.f, 0.5f, 0.f, 1.f));
	}

	if (myDidntRenameTimer < 4.f)
	{
		SB::DebugGUI::PrintText("Rename Emitter to add it!", SB::Vector4f(1.f, 0.f, 0.f, 1.f));
	}
}

bool ParticleEditorScene::ErrorCheckMinMax(const SB::Vector2f & aVector, const SB::Vector2f & aMinMax /*= SB::Vector2f(0.f, 1.f)*/)
{
	if (aVector.x < aMinMax.x || aVector.x > aVector.y || aVector.y > aMinMax.y)
	{
		return true;
	}
	return false;
}

bool ParticleEditorScene::HasErrors()
{
	SB::Vector2f derpy(-1000.f, 1000.f);

	if (ErrorCheckMinMax(myEmitterSettings->myMinMaxVelocityX, derpy) ||
		ErrorCheckMinMax(myEmitterSettings->myMinMaxVelocityY, derpy) ||
		ErrorCheckMinMax(myEmitterSettings->myMinMaxVelocityZ, derpy) ||
		ErrorCheckMinMax(myEmitterSettings->myMinMaxRotationPerSecond, derpy) ||
		ErrorCheckMinMax(myEmitterSettings->myMinMaxStartRotation, derpy) ||
		ErrorCheckMinMax(myEmitterSettings->myMinMaxLifeTime, SB::Vector2f(0.f, 1000.f)) ||
		ErrorCheckMinMax(myEmitterSettings->myMinMaxSize, SB::Vector2f(0.f, 10000.f)))
	{
		return true;
	}

	if (myEmitterSettings->myEndSizeInPercent < 0.f || myEmitterSettings->myEmitCoolDown.InSeconds() <= 0.f || myEmitterSettings->myAmountOfParticles <= 0 || myEmitterSettings->myAmountOfParticles > 200 )
	{
		return true;
	}

	return false;
}

void ParticleEditorScene::SetEmitterToEditor()
{

	SB::DebugGUI::SetElementsWidth(200.f);

	SB::DebugGUI::SetWindowPosition(SB::Vector2f(5.f, 5.f));

	SB::DebugGUI::SetElementsWidth(100.f);

	SB::DebugGUI::PrintText("Start Color:");
	SB::DebugGUI::VectorSlider(myEmitterSettings->myStartColor, SB::Vector2f(0.f, 1.f), true);
	SB::DebugGUI::PrintText("End Color:");
	SB::DebugGUI::VectorSlider(myEmitterSettings->myEndColor, SB::Vector2f(0.f, 1.f), true);

	SB::DebugGUI::PrintText("Gravity:");
	SB::DebugGUI::VectorSlider(myEmitterSettings->myGravity, SB::Vector2f(-10.f, 10.f));

	SB::DebugGUI::PrintText("Min Max Values:");

	SB::DebugGUI::PrintText("Velocity X:");
	SB::DebugGUI::MinMaxSlider(myEmitterSettings->myMinMaxVelocityX, SB::Vector2f(-500.f, 500.f));

	SB::DebugGUI::PrintText("Velocity Y:");
	SB::DebugGUI::MinMaxSlider(myEmitterSettings->myMinMaxVelocityY, SB::Vector2f(-500.f, 500.f));
	SB::DebugGUI::PrintText("Velocity Z:");
	SB::DebugGUI::MinMaxSlider(myEmitterSettings->myMinMaxVelocityZ, SB::Vector2f(-500.f, 500.f));

	SB::DebugGUI::PrintText("Rotation Per Second:");
	SB::DebugGUI::MinMaxSlider(myEmitterSettings->myMinMaxRotationPerSecond, SB::Vector2f(-800.f, 800.f));

	SB::DebugGUI::PrintText("Start Rotation:");
	SB::DebugGUI::MinMaxSlider(myEmitterSettings->myMinMaxStartRotation, SB::Vector2f(-800.f, 800.f));

	SB::DebugGUI::PrintText("LifeTime:");
	SB::DebugGUI::MinMaxSlider(myEmitterSettings->myMinMaxLifeTime, SB::Vector2f(-800.f, 800.f));

	SB::DebugGUI::PrintText("Size:");
	SB::DebugGUI::MinMaxSlider(myEmitterSettings->myMinMaxSize, SB::Vector2f(0.f, 20.f));

	SB::DebugGUI::FloatSlider(myEmitterSettings->myEndSizeInPercent, SB::Vector2f(0.f, 20.f), " : End Size In Percent");

	myEmitCD = myEmitterSettings->myEmitCoolDown.InSeconds();
	SB::DebugGUI::FloatSlider(myEmitCD, SB::Vector2f(0.f, 5.f), " : Emit Cooldown");
	myEmitterSettings->myEmitCoolDown = myEmitCD;
	

	SB::DebugGUI::CheckBox(myEmitterSettings->myShouldRotateInDirection, "Should Rotate in Direction ");
	SB::DebugGUI::CheckBox(myEmitterSettings->myIsExplosion, "Is Explosion ");

	myParticleAmount = myEmitterSettings->myAmountOfParticles;
	SB::DebugGUI::IntSlider(myParticleAmount, SB::Vector2i(1, 200), "Max Amount of Particles ");
	myEmitterSettings->myAmountOfParticles = static_cast<unsigned short>(myParticleAmount);

	SB::DebugGUI::ImageAndRect(myEmitterSettings->myTextureUV, myAtlasTexture);

	SB::DebugGUI::SetElementsWidth(70.f);

	SB::DebugGUI::PrintText("UV Coordinates:");
	SB::DebugGUI::VectorSetter(myEmitterSettings->myTextureUV, SB::Vector2f(0.f, 512.f));

	SB::Vector4f wholeImage(0.f, 0.f, 512.f, 512.f);
	SB::DebugGUI::ImageAndRect(wholeImage, myAtlasTexture, 0.5f);
}

void ParticleEditorScene::SetupEmitterNames()
{
	myEmitterTypeNames = myParticleSystem->GetEmitterNames();
}

void ParticleEditorScene::HandleExternal()
{
	SB::DebugGUI::TextBox(myEmitterName, "Emitter Name");

	if (SB::DebugGUI::Button("Apply Changes", SB::Vector2f(100.f, 20.f)) == true)
	{
		ApplyChangesToEmitter();
	}

	if (SB::DebugGUI::Button("Delete Emitter", SB::Vector2f(100.f, 20.f)) == true)
	{
		RemoveSelectedEmitter();
	}

	if (SB::DebugGUI::Button("Add Type", SB::Vector2f(100.f, 20.f)) == true)
	{
		AddCurrentEmitter();
	}
	
	if (SB::DebugGUI::Button("Save to File", SB::Vector2f(100.f, 20.f)) == true)
	{
		SaveEmitters();
	}
}

void ParticleEditorScene::ChangeForceFields()
{
	myLocalForceFields.RemoveAll();
	for (unsigned short i = 0; i < myEmitterSettings->myForceFieldsSettings.Size(); ++i)
	{
		myLocalForceFields.Add(SB::FormatString("# {0}", i));
	}
	myChosenForceFieldIndex = 0;
	myEditingForceField = nullptr;
	if (myEmitterSettings->myForceFieldsSettings.Size() > 0)
	{
		myEditingForceField = &myEmitterSettings->myForceFieldsSettings[0];
		myChosenForceField = myLocalForceFields[0];
	}
}

void ParticleEditorScene::ChooseEmitterToEdit()
{
	if (SB::DebugGUI::Combobox(myEmitterTypeNames, myChosenEmitterIndex, myChosenEmitter, "Emitter Types") == true)
	{
		myEmitterName = myChosenEmitter;
		myEmitter = myParticleSystem->CreateEmitter(myChosenEmitter);
		myEmitterSettings = myEmitter->GetSettingsForEditor();
		myEmitter->SetPositionOffset(SB::Vector3f(2.f, 0.f, 100.f));
		ChangeForceFields();
	}
}

void ParticleEditorScene::ApplyChangesToEmitter()
{
	myAppliedTimer = 0.f;

	myEmitterSettings->myEmitCoolDown = myEmitCD;
	myEmitterSettings->myAmountOfParticles = static_cast<unsigned short>(myParticleAmount);
	myParticleSystem->ModifyEmitterType(*myEmitterSettings, myEmitterName, myChosenEmitter);
	myEmitterTypeNames[myChosenEmitterIndex] = myEmitterName;
}

void ParticleEditorScene::AddCurrentEmitter()
{
	if (myChosenEmitter == myEmitterName)
	{
		myDidntRenameTimer = 0.f;
		return;
	}

	myEmitterSettings->myEmitCoolDown = myEmitCD;
	myEmitterSettings->myAmountOfParticles = static_cast<unsigned short>(myParticleAmount);
	myParticleSystem->AddEmitterType(*myEmitterSettings, myEmitterName);
	myEmitterTypeNames.Add(myEmitterName);
	myChosenEmitterIndex = myEmitterTypeNames.Size() -1;
}

void ParticleEditorScene::RemoveSelectedEmitter()
{
	if (myEmitterTypeNames.Size() == 1)
	{
		Error("Don't Remove the last Emitter! D:< Go see Ylf and get scolded! We need to have a template left.");
	}

	myParticleSystem->RemoveEmitterType(myChosenEmitter);
	myEmitterTypeNames.RemoveAtIndex(myChosenEmitterIndex);
	myChosenEmitterIndex -= 1;
	myDeletedTimer = 0.f;
	if (myChosenEmitterIndex == USHRT_MAX)
	{
		myChosenEmitterIndex = 0;
	}
	myChosenEmitter = myEmitterTypeNames[myChosenEmitterIndex];

	myEmitterName = myChosenEmitter;
	myEmitter = myParticleSystem->CreateEmitter(myChosenEmitter);
	myEmitterSettings = myEmitter->GetSettingsForEditor();
	myEmitter->SetPositionOffset(SB::Vector3f(2.f, 0.f, 100.f));
}

void ParticleEditorScene::SaveEmitters()
{
	myParticleSystem->SaveEmitterTypes("Assets/Data/ParticleEmitters/particleEmitters.json");
	mySaveTimer = 0.f;
}

void ParticleEditorScene::BackupSave()
{
	myParticleSystem->SaveEmitterTypes("Assets/Data/ParticleEmitters/Backup/particleEmitters.json");
}

void ParticleEditorScene::AutoSave()
{
	myParticleSystem->SaveEmitterTypes("Assets/Data/ParticleEmitters/Autosave/particleEmitters.json");
}


void ParticleEditorScene::MakeWorldGrid()
{
	unsigned short numberOfLines = static_cast<unsigned short>(myNumberOfGridLines);
	unsigned short halfNumberOfLines = (numberOfLines / 2);
	unsigned short over = numberOfLines + halfNumberOfLines;
	float distanceBetweenSegments = myDistanceBetweenGridLines;
	float extents = distanceBetweenSegments * static_cast<float>(halfNumberOfLines);
	float extraExtentAxises = 1.5f;

	SB::LineSegmentShape line1;

	//X AXIS
	line1.myFirstPosition = SB::Vector3f(-extents * extraExtentAxises, 0.f, 0.f);
	line1.mySecondPosition = SB::Vector3f(extents * extraExtentAxises, 0.f, 0.f);
	SB::Engine::GetDebugDrawer().DrawLine(GetCamera(), line1, SB::Color(1.f, 0.f, 0.f, 1.f));

	//Y AXIS
	line1.myFirstPosition = SB::Vector3f(0, extents *extraExtentAxises, 0.f);
	line1.mySecondPosition = SB::Vector3f(0, -extents * extraExtentAxises, 0.f);
	SB::Engine::GetDebugDrawer().DrawLine(GetCamera(), line1, SB::Color(0.f, 1.f, 0.f, 1.f));

	//Z AXIS
	line1.myFirstPosition = SB::Vector3f(0.f, 0.f, -extents * extraExtentAxises);
	line1.mySecondPosition = SB::Vector3f(0.f, 0.f, extents * extraExtentAxises);
	SB::Engine::GetDebugDrawer().DrawLine(GetCamera(), line1, SB::Color(0.f, 0.f, 1.f, 1.f));

	for (unsigned short iLineX = 1; iLineX < halfNumberOfLines; ++iLineX)
	{
		line1.myFirstPosition = SB::Vector3f(distanceBetweenSegments * static_cast<float>(iLineX) , 0.f, -extents);
		line1.mySecondPosition = SB::Vector3f(distanceBetweenSegments * static_cast<float>(iLineX), 0.f, extents);
		SB::Engine::GetDebugDrawer().DrawLine(GetCamera(), line1, SB::Color(1.f, 0.f, 0.f, 1.f));
	}
	for (unsigned short iLineX = 1; iLineX < halfNumberOfLines; ++iLineX)
	{
		line1.myFirstPosition = SB::Vector3f(distanceBetweenSegments * -static_cast<float>(iLineX), 0.f, -extents);
		line1.mySecondPosition = SB::Vector3f(distanceBetweenSegments * -static_cast<float>(iLineX), 0.f, extents);
		SB::Engine::GetDebugDrawer().DrawLine(GetCamera(), line1, SB::Color(1.f, 0.f, 0.f, 1.f));
	}

	for (unsigned short iLineY = 1; iLineY < halfNumberOfLines; ++iLineY)
	{
		line1.myFirstPosition = SB::Vector3f(-extents, distanceBetweenSegments * static_cast<float>(iLineY), 0.f);
		line1.mySecondPosition = SB::Vector3f(extents, distanceBetweenSegments * static_cast<float>(iLineY), 0.f);
		SB::Engine::GetDebugDrawer().DrawLine(GetCamera(), line1, SB::Color(0.f, 1.f, 0.f, 1.f));
	}
	for (unsigned short iLineY = 1; iLineY < halfNumberOfLines; ++iLineY)
	{
		line1.myFirstPosition = SB::Vector3f(-extents, distanceBetweenSegments * -static_cast<float>(iLineY), 0.f);
		line1.mySecondPosition = SB::Vector3f(extents, distanceBetweenSegments * -static_cast<float>(iLineY), 0.f);
		SB::Engine::GetDebugDrawer().DrawLine(GetCamera(), line1, SB::Color(0.f, 1.f, 0.f, 1.f));
	}

	for (unsigned short iLineZ = 1; iLineZ < halfNumberOfLines; ++iLineZ)
	{
		line1.myFirstPosition = SB::Vector3f(-extents, 0.f, distanceBetweenSegments * static_cast<float>(iLineZ));
		line1.mySecondPosition = SB::Vector3f(extents, 0.f, distanceBetweenSegments * static_cast<float>(iLineZ));
		SB::Engine::GetDebugDrawer().DrawLine(GetCamera(), line1, SB::Color(0.f, 0.f, 1.f, 1.f));
	}
	for (unsigned short iLineZ = 1; iLineZ < halfNumberOfLines; ++iLineZ)
	{
		line1.myFirstPosition = SB::Vector3f(-extents, 0.f, distanceBetweenSegments * -static_cast<float>(iLineZ));
		line1.mySecondPosition = SB::Vector3f(extents, 0.f, distanceBetweenSegments * -static_cast<float>(iLineZ));
		SB::Engine::GetDebugDrawer().DrawLine(GetCamera(), line1, SB::Color(0.f, 0.f, 1.f, 1.f));
	}
}

void ParticleEditorScene::RenderForceFields()
{
	for (unsigned short iFF = 0; iFF < myEmitterSettings->myForceFieldsSettings.Size(); ++iFF)
	{
		SB::Color prettyColor(1.f, 1.f, 0.f);
		if (myChosenForceFieldIndex == iFF)
		{
			prettyColor.g = 0.2f;
		}
		SB::Engine::GetDebugDrawer().RenderSphere(GetCamera(), myEmitterSettings->myForceFieldsSettings[iFF].myForceField.myPosition, myEmitterSettings->myForceFieldsSettings[iFF].myForceField.myRadius, prettyColor);
	}
}
