#include "stdafx.h"
#include "ParticleEditorScene.h"
#include <Engine/ParticleSystem/ParticleSystem.h>
#include <Engine/ParticleSystem/ParticleEmitter.h>
#include <Engine/ParticleSystem/ParticleSystemStructs.h>
#include <Engine/Debugging/DebugGUI/BaseDebugGUI.h>
#include <Engine/GenericEngineMessages.h>
#include <Engine/Camera/Controllers/FreeSpaceCameraController.h>
#include <Engine\GUI\GUILoader.h>

ParticleEditorScene::ParticleEditorScene(SB::PostMasterState & aPostMasterState) : Scene(aPostMasterState, "Particle Editor", "grass.dds")
{
	SB::PostMasterStateBinding bind = SB::PostMaster::Push(*this);
	myEmitterName = "EmitterName";
	myEmitter = myParticleSystem->CreateEmptyEmitter();
	myEmitterSettings = myEmitter->GetSettingsForEditor();
	myEmitter->SetPositionOffset(SB::Vector3f(2.f, 0.f, 5.f));
	SB::Engine::GetRenderer().GetModelRenderer().SetDirectionalLight(0, SB::Vector3f::UnitZ, SB::Vector4f(1.f, 1.f, 1.f, 1.f));

	myAtlasTexture = myParticleSystem->GetAtlas();

	PushCameraController(std::make_shared<SB::FreeSpaceCameraController>(5.f, 1.5f));
	SB::DebugGUI::SetWindowPosition(SB::Vector2f(5.f, 5.f));
	SB::DebugGUI::SetDebugGUISize(SB::Vector2f(500.f, 700.f));

}

ParticleEditorScene::~ParticleEditorScene()
{
	myEmitter->ReturnEmitter();
	myEmitterSettings = nullptr;
	myEmitter = nullptr;
}

void ParticleEditorScene::Update(const SB::Time & aDeltaTime)
{
	SB::DebugGUI::PrintText("Move using WASD, RF and arrow keys.\nCtrl-click a value to set it manually.", SB::Vector4f(0.f, 1.f, 1.f, 1.f));
	SetEmitterToEditor();

	if (HasErrors() == false)
	{
		myEmitter->Update(aDeltaTime, SB::Vector3f::Zero);

		HandleExternal();
	}
	else
	{
		SB::DebugGUI::PrintText("EMITTER HAS INVALID VALUES!", SB::Vector4f(1.f, 0.f, 0.f, 1.f));
	}
	Scene::Update(aDeltaTime);
}

void ParticleEditorScene::Render()
{
	Scene::Render();
}

void ParticleEditorScene::OnEnter()
{
	SB::Engine::GetGUILoader().DisableGUI();
	SB::PostMaster::Post<SB::ShowCursorMessage>(SB::ShowCursorMessage(true));
	SB::PostMaster::Post<SB::ChangeCursorMessage>(SB::ChangeCursorMessage(SB::eCursorState::eNormal));
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
		ErrorCheckMinMax(myEmitterSettings->myMinMaxSize, SB::Vector2f(0.f, 1000.f)))
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
	//SB::DebugGUI::TextBox(myEmitterName, "Emitter Name");


	SB::DebugGUI::SetElementsWidth(100.f);

	SB::DebugGUI::PrintText("Start Color:");
	SB::DebugGUI::VectorSlider(myEmitterSettings->myStartColor, SB::Vector2f(0.f, 1.f), true);
	SB::DebugGUI::PrintText("End Color:");
	SB::DebugGUI::VectorSlider(myEmitterSettings->myEndColor, SB::Vector2f(0.f, 1.f), true);

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

void ParticleEditorScene::HandleExternal()
{
	if (SB::DebugGUI::Button("Add Type", SB::Vector2f(100.f, 20.f)) == true)
	{
		AddCurrentEmitter();
	}
	
	if (SB::DebugGUI::Button("Save Emitters", SB::Vector2f(100.f, 20.f)) == true)
	{
		SaveEmitters();
	}
}

void ParticleEditorScene::AddCurrentEmitter()
{
	myEmitterSettings->myEmitCoolDown = myEmitCD;
	myEmitterSettings->myAmountOfParticles = static_cast<unsigned short>(myParticleAmount);
	myParticleSystem->AddEmitterType(*myEmitterSettings, myEmitterName);
}

void ParticleEditorScene::SaveEmitters()
{
	myParticleSystem->SaveEmitterTypes();
}
