#include "stdafx.h"
#include "LabbAIScene.h"
#include "Engine\Texture\GuiRenderTarget.h"
#include "AIEventHandler.h"
#include "CircleShape.h"
#include "AIArriveController.h"
#include "AIFleeController.h"
#include "BlendBehaviourController.h"
#include "FormationController.h"
#include "..\Engine\Engine\Debugging\DebugGUI\BaseDebugGUI.h"
#include "Script\ScriptSystem.h"
//#include "..\Engine\Engine\Input\KeyboardKey.h"
//#include "..\Engine\Engine\Input\InputListener.h"

extern "C" inline int PrintFromLua(lua_State * aLuaState)
{
	int args = lua_gettop(aLuaState);

	for (int n = 1; n <= args; ++n)
	{
		if (lua_isnoneornil(aLuaState, n) == true)
		{
			std::cout << "a argument was none or nil " << std::endl;
			std::system("pause");
		}
		else
		{
			std::cout << lua_tostring(aLuaState, n);
		}
	}

	std::cout << std::endl;

	return 0;
}




void RegisterFunctions()
{
	ScriptSystem::RegisterFunction("Print", PrintFromLua, "Will do a cout on each in arguemnt, ends with a newline. (there is no space or newline between arguments)");
}

LabbAIScene::LabbAIScene(SB::PostMasterState & aPostMasterState) : SB::Scene(aPostMasterState, "PhysxTestScene"/*, "Assets/Skyboxes/skybox4_16f.dds"*/)
{
	ScriptSystem::Create();
	ScriptSystem::RegisterEvent("VolumeEnter");
	ScriptSystem::RegisterEvent("VolumeExit");

	ScriptSystem::LoadLuaFile(std::bind(RegisterFunctions), "Scripts/testfile.lua");
	ScriptSystem::CallFunction("Init");

	//25
	myUnits.Resize(9);
	myCollidedStates.Resize(myUnits.Size(), false);

	for (unsigned short iUnit = 0; iUnit < myUnits.Size(); ++iUnit)
	{
		float xPosition = myRandomizer.GetRandomValue(100, 1920.f);
		float yPosition = myRandomizer.GetRandomValue(0, 1080.f);
		myUnits[iUnit].SetPosition(SB::Vector2f(xPosition, yPosition));
		myUnits[iUnit].SetControllerType(myUnitGroup);
	}

	CreateAndAddModel("derp", "Assets/Models/PBL_Spheres/testSpheres.fbx", SB::Vector3f(0.f, 0.f, 25.f))->Initialize();

	myMouseListener = std::make_shared<SB::Subscription<SB::MouseMovedMessage>>([this](const SB::MouseMovedMessage & aMessage)
	{
		myMousePosition = SB::Vector2f(static_cast<float>( aMessage.x), static_cast<float>(aMessage.y));
	});

	myVolumeSprite.SetTexture(SB::Engine::GetResourceManager().Get<SB::Texture>("Sprites/CollisionVolume.dds"));
	myVolumeSprite.SetPosition(SB::Vector2f(300.f, 300.f));
	myVolumeSprite.SetOrigin(SB::Vector2f(256.f, 256.f));

	SeekBehaviour::ourWeight = 1.f;
	WanderBehaviour::ourWeight = 7.f;
	EvadeBehaviour::ourMaxWeight = 3.f;
	EvadeBehaviour::ourEvadeWeight = 1.7f;
}


LabbAIScene::~LabbAIScene()
{
	
}

void LabbAIScene::Update(const SB::Time & aDeltaTime)
{
	//SB::Vector2f WeightRange(0.01f, 2.f);

	//ImGui::Begin("Weights");

	////SB::DebugGUI::FloatSlider(EvadeBehaviour::ourMaxWeight, WeightRange, "Evade Max");
	//SB::DebugGUI::FloatSlider(EvadeBehaviour::ourEvadeWeight, WeightRange, "Evade weight");

	//if (SB::DebugGUI::Button("RepositionPillers", SB::Vector2f(200.f, 50.f)) == true)
	//{
	//	PositionPillers();
	//}

	//ImGui::End();

	ScriptSystem::Update();
	//ScriptSystem::CallFunction("Update", 3.3456f, 2);

	if (myInputListener.GetMouseButtonDownThisFrame() == true)
	{
		AIEventHandler::SetNewTargetForSeek(SetSeekTargetEvent(myMousePosition));
	}

	for (unsigned short iUnit = 0; iUnit < myUnits.Size(); ++iUnit)
	{
		myUnits[iUnit].Update(aDeltaTime);
	}

	AIEventHandler::CheckEvadeOnBlendControllers();
	AIEventHandler::CheckEvadeOnFormationControllers();

	CollisionCheckAgainstVolume();
	//std::cout << "ararararaar" << std::endl << std::endl << std::endl;

	Scene::Update(aDeltaTime);
}

void LabbAIScene::Render()
{
	Scene::Render();

	myGuiRenderTarget->Render(myVolumeSprite);

	for (unsigned short iUnit = 0; iUnit < myUnits.Size(); ++iUnit)
	{
		myUnits[iUnit].DebugRender(*myGuiRenderTarget);
		myGuiRenderTarget->RenderBuffer();
		myUnits[iUnit].Render(*myGuiRenderTarget);
	}

}

void LabbAIScene::CollisionCheckAgainstVolume()
{
	SB::CircleShape volumeCollider(myVolumeSprite.GetPosition(), 256.f);

	for (unsigned short iUnit = 0; iUnit < myUnits.Size(); ++iUnit)
	{
		SB::CircleShape unitCircle(myUnits[iUnit].GetPosition(), myUnits[iUnit].GetRadius());
		
		if (CollisionCheck(volumeCollider, unitCircle) == true)
		{
			if (myCollidedStates[iUnit] == false)
			{
				myCollidedStates[iUnit] = true;
				OnCollisionEnter(iUnit);
			}
		}
		else
		{
			if (myCollidedStates[iUnit] == true)
			{
				myCollidedStates[iUnit] = false;
				OnCollisionExit(iUnit);
			}
		}
	}
}

bool LabbAIScene::CollisionCheck(const SB::CircleShape & aFirstCircle, const SB::CircleShape & aSecondCircle)
{
	const float combinedRadius = aFirstCircle.myRadius + aSecondCircle.myRadius;
	const float distance = (aFirstCircle.myPosition - aSecondCircle.myPosition).Length();

	if (combinedRadius >= distance)
	{
		return true;
	}

	return false;
}

void LabbAIScene::OnCollisionEnter(unsigned short aObjectID)
{
	ScriptSystem::CallEvent("VolumeEnter", aObjectID, 0);
}

void LabbAIScene::OnCollisionExit(unsigned short aObjectID)
{
	ScriptSystem::CallEvent("VolumeExit", aObjectID, 0);
}
