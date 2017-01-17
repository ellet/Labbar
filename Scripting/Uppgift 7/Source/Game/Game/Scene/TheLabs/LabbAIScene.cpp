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

extern "C" inline int TestPop(lua_State * aLuaState)
{
	int args = lua_gettop(aLuaState);
	

	int intValue = 0;
	//std::string stringValue = "";
	float testfloat = 0.f;
	float testNumber = 0.f;

	int ararar = lua_gettop(aLuaState);


	std::tie(intValue, testfloat, testNumber) = ScriptSystem::PopValues<int, float, float>(aLuaState);

//	size_t testInt = lua_tointeger(aLuaState, 1);

	std::cout << std::endl;

	return 0;
}

void RegisterFunctions(const size_t aNodeIndex)
{
	ScriptSystem::RegisterFunction(aNodeIndex, "Print", PrintFromLua, "Will do a cout on each in arguemnt, ends with a newline. (there is no space or newline between arguments)");
	ScriptSystem::RegisterFunction(aNodeIndex, "TestPop", TestPop, "test tuple and pop");
}

LabbAIScene * LabbAIScene::ourScene = nullptr;



LabbAIScene::LabbAIScene(SB::PostMasterState & aPostMasterState) : SB::Scene(aPostMasterState, "PhysxTestScene"/*, "Assets/Skyboxes/skybox4_16f.dds"*/)
{
	ourScene = this;

	ScriptSystem::Create();
	ScriptSystem::RegisterEvent("VolumeEnter");
	ScriptSystem::RegisterEvent("VolumeExit");
	ScriptSystem::RegisterEvent("KeyPress");

	ScriptSystem::SetLuaFunctionRegistrationInit(std::bind(RegisterFunctions, std::placeholders::_1));
	ScriptSystem::LoadLuaFile("Scripts/TestPop.lua");
	
	ScriptSystem::CallFunction("Init");

	//25
	//myUnits.Resize(2);

	/*for (unsigned short iUnit = 0; iUnit < myUnits.Size(); ++iUnit)
	{
		float xPosition = myRandomizer.GetRandomValue(100, 1920.f);
		float yPosition = myRandomizer.GetRandomValue(0, 1080.f);
		myUnits[iUnit].SetPosition(SB::Vector2f(xPosition, yPosition));

		myUnits[iUnit].SetIndex(iUnit);
	}*/

	CreateAndAddModel("derp", "Assets/Models/PBL_Spheres/testSpheres.fbx", SB::Vector3f(0.f, 0.f, 25.f))->Initialize();

	myMouseListener = std::make_shared<SB::Subscription<SB::MouseMovedMessage>>([this](const SB::MouseMovedMessage & aMessage)
	{
		myMousePosition = SB::Vector2f(static_cast<float>( aMessage.x), static_cast<float>(aMessage.y));
	});

	

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
	
	if (myInputListener.GetAnyKeyPressedThisFrame() == true)
	{
		ScriptSystem::CallEvent("KeyPress");
	}

	if (myInputListener.GetMouseButtonDownThisFrame() == true)
	{
		AIEventHandler::SetNewTargetForSeek(SetSeekTargetEvent(myMousePosition));
	}

	for (unsigned short iUnit = 0; iUnit < myUnits.Size(); ++iUnit)
	{
		myUnits[iUnit].Update(aDeltaTime);
	}

	//AIEventHandler::CheckEvadeOnBlendControllers();
	//AIEventHandler::CheckEvadeOnFormationControllers();

	//CollisionCheckAgainstVolume();
	CollisionCheckUnits();

	Scene::Update(aDeltaTime);
}

void LabbAIScene::Render()
{
	Scene::Render();


	for (unsigned short iUnit = 0; iUnit < myUnits.Size(); ++iUnit)
	{
		myUnits[iUnit].DebugRender(*myGuiRenderTarget);
		myGuiRenderTarget->RenderBuffer();
		myUnits[iUnit].Render(*myGuiRenderTarget);
	}

}


LabbAIScene & LabbAIScene::GetScene()
{
	return *ourScene;
}


void LabbAIScene::CollisionCheckUnits()
{
	/*for (unsigned short iUnit = 0; iUnit < myUnits.Size(); ++iUnit)
	{
		bool hasCollided = false;

		SB::CircleShape unitCircle(myUnits[iUnit].GetPosition(), myUnits[iUnit].GetRadius());

		for (unsigned short iVolume = 0; iVolume < myVolumeSprites.Size(); ++iVolume)
		{
			SB::CircleShape volumeCollider(myVolumeSprites[iVolume].GetPosition(), 128.f);



			if (CollisionCheck(volumeCollider, unitCircle) == true)
			{
				hasCollided = true;
				if (myCollidedStates[iUnit] == false)
				{
					myCollidedStates[iUnit] = true;
					OnCollisionEnter(iUnit, iVolume);
				}
				break;
			}
		}

		if (hasCollided == false)
		{
			myCollidedStates[iUnit] = false;
		}
	}*/
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

void LabbAIScene::OnCollisionEnter(const unsigned short aObjectID, const unsigned short aVolumeID)
{
	ScriptSystem::CallEvent("VolumeEnter", aObjectID, aVolumeID);
}

void LabbAIScene::OnCollisionExit(const unsigned short aObjectID, const unsigned short aVolumeID)
{
	ScriptSystem::CallEvent("VolumeExit", aObjectID, aVolumeID);
}

