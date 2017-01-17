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
	float ararfloat = 0.f;
	float testNumber = 0.f;
	//std::string daDerp = "";
	const char * comboBreaker = "";

	int ararar = lua_gettop(aLuaState);



	std::tie(intValue, testfloat, ararfloat, comboBreaker, testNumber) = ScriptSystem::PopValues<int, float, float, const char *, float>(aLuaState);

//	size_t testInt = lua_tointeger(aLuaState, 1);

	std::cout << std::endl;

	return 0;
}

extern "C" inline int SpawnUnit(lua_State * aLuaState)
{
	int args = lua_gettop(aLuaState);

	unsigned short caller = 0;
	const char * filePath = "";
	float xPos = 0.f;
	float yPos = 0.f;

	std::tie(caller, filePath, xPos, yPos) = ScriptSystem::PopValues<unsigned short, const char *, float, float>(aLuaState);

	std::string stringPath = filePath;
	SB::Vector2f spawnPos(xPos, yPos);

	const unsigned short newUnitIndex = LabbAIScene::GetScene().SpawnUnit(stringPath, spawnPos);

	ScriptSystem::AddArgumentsToStack(caller, newUnitIndex);

	return 1;
}

extern "C" inline int ClearUnits(lua_State * aLuaState)
{
	int args = lua_gettop(aLuaState);

	LabbAIScene::GetScene().ClearUnits();

	return 0;
}

extern "C" inline int SetObjectPosition(lua_State * aLuaState)
{
	int args = lua_gettop(aLuaState);

	unsigned short objectID = 0;
	SB::Vector2f newPosition;


	std::tie(objectID, newPosition.x, newPosition.y) = ScriptSystem::PopValues<unsigned short, float, float>(aLuaState);

	LabbAIScene::GetScene().SetPositionOnObject(objectID, newPosition);

	return 0;
}

extern "C" inline int AddToObjectPosition(lua_State * aLuaState)
{
	int args = lua_gettop(aLuaState);

	unsigned short activeObjectID = 0;
	SB::Vector2f deltaMovement;

	std::tie(activeObjectID, deltaMovement.x, deltaMovement.y) = ScriptSystem::PopValues<unsigned short, float ,float>(aLuaState);

	LabbAIScene::GetScene().AddToObjectPosition(activeObjectID, deltaMovement);

	return 0;
}

extern "C" inline int GetObjectPosition(lua_State * aLuaState)
{
	int args = lua_gettop(aLuaState);

	unsigned short caller = 0;
	unsigned short aObjectID = 0;
	

	std::tie(caller, aObjectID) = ScriptSystem::PopValues<unsigned short, unsigned short>(aLuaState);

	SB::Vector2f currentPosition = LabbAIScene::GetScene().GetObjectsPosition(aObjectID);

	ScriptSystem::AddArgumentsToStack(caller, currentPosition.x ,currentPosition.y);

	return 2;
}

extern "C" inline int CheckCollision(lua_State * aLuaState)
{
	int args = lua_gettop(aLuaState);

	unsigned short caller = 0;
	unsigned short objectID = 0;
	unsigned short otherObjectID = 0;


	std::tie(caller, objectID, otherObjectID) = ScriptSystem::PopValues<unsigned short, unsigned short, unsigned short>(aLuaState);

	bool collisionState = LabbAIScene::GetScene().CheckIfUnitsCollide(objectID, otherObjectID);

	ScriptSystem::AddArgumentsToStack(caller, collisionState);

	return 1;
}

void RegisterFunctions(const size_t aNodeIndex)
{
	ScriptSystem::RegisterFunction(aNodeIndex, "Print", PrintFromLua, "Will do a cout on each in arguemnt, ends with a newline. (there is no space or newline between arguments)");
	ScriptSystem::RegisterFunction(aNodeIndex, "TestPop", TestPop, "test tuple and pop");
	ScriptSystem::RegisterFunction(aNodeIndex, "SpawnUnit", SpawnUnit, "spawns a unit with given sprite at given position");
	ScriptSystem::RegisterFunction(aNodeIndex, "ClearUnits", ClearUnits, "removes all the units in the scene");
	ScriptSystem::RegisterFunction(aNodeIndex, "GetObjectPosition", GetObjectPosition, "Gets Given objects position");
	ScriptSystem::RegisterFunction(aNodeIndex, "AddToObjectPosition", AddToObjectPosition, "On the given object will add to its position");
	ScriptSystem::RegisterFunction(aNodeIndex, "CheckCollision", CheckCollision, "Checks collision between two objects");
	ScriptSystem::RegisterFunction(aNodeIndex, "SetObjectPosition", SetObjectPosition, "On given Object set given Position");
}

LabbAIScene * LabbAIScene::ourScene = nullptr;



LabbAIScene::LabbAIScene(SB::PostMasterState & aPostMasterState) : SB::Scene(aPostMasterState, "PhysxTestScene"/*, "Assets/Skyboxes/skybox4_16f.dds"*/)
{
	ourScene = this;

	ScriptSystem::Create();
	ScriptSystem::RegisterEvent("KeyPress");

	ScriptSystem::SetLuaFunctionRegistrationInit(std::bind(RegisterFunctions, std::placeholders::_1));
	ScriptSystem::LoadLuaFile("Scripts/TestPop.lua");

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
	

	if (myInputListener.GetHeldKeyDown(SB::KeyboardKey::eRight) == true)
	{
		ScriptSystem::CallEvent("KeyPress", 1);
	}

	if (myInputListener.GetHeldKeyDown(SB::KeyboardKey::eDown) == true)
	{
		ScriptSystem::CallEvent("KeyPress", 2);
	}

	if (myInputListener.GetHeldKeyDown(SB::KeyboardKey::eLeft) == true)
	{
		ScriptSystem::CallEvent("KeyPress", 3);
	}

	if (myInputListener.GetHeldKeyDown(SB::KeyboardKey::eUp) == true)
	{
		ScriptSystem::CallEvent("KeyPress", 4);
	}

	if ((myInputListener.GetPressedThisFrame(SB::KeyboardKey::eSpace) == true) || (myInputListener.GetPressedThisFrame(SB::KeyboardKey::eControl) == true))
	{
		ScriptSystem::CallEvent("KeyPress", 5);
	}
	

	for (unsigned short iUnit = 0; iUnit < myUnits.Size(); ++iUnit)
	{
		myUnits[iUnit].Update(aDeltaTime);
	}

	ScriptSystem::CallFunction("Update", 0, aDeltaTime.InSeconds());
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


unsigned short LabbAIScene::SpawnUnit(const std::string & aFilePath, const SB::Vector2f & aPosition)
{
	myUnits.Add(Unit());
	Unit & newUnit = myUnits.GetLast();

	newUnit.SetPosition(aPosition);
	newUnit.SetSprite(aFilePath);

	newUnit.SetIndex(myUnits.Size() - 1);
	return myUnits.Size() - 1;
}

void LabbAIScene::AddToObjectPosition(const unsigned short aObjectID, const SB::Vector2f & aDeltaMovement)
{
	myUnits[aObjectID].AddToPosition(aDeltaMovement);
}

bool LabbAIScene::CheckIfUnitsCollide(const unsigned short aObjectID, const unsigned short aOtherObject)
{
	return CollisionCheck(myUnits[aObjectID].GetCircle(), myUnits[aOtherObject].GetCircle());
}

const SB::Vector2f LabbAIScene::GetObjectsPosition(const unsigned short aObjectID)
{
	return myUnits[aObjectID].GetPosition();
}

void LabbAIScene::SetPositionOnObject(const unsigned short aObjectID, const SB::Vector2f & aPosition)
{
	myUnits[aObjectID].SetPosition(aPosition);
}

void LabbAIScene::ClearUnits()
{
	std::system("cls");
	myUnits.RemoveAll();
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


