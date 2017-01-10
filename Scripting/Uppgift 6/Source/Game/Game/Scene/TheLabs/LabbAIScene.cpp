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

extern "C" inline int MoveToFreeVolume(lua_State * aLuaState)
{
	int args = lua_gettop(aLuaState);

	unsigned short objectID;
	objectID = static_cast<unsigned short>(lua_tonumber(aLuaState, 1));

	LabbAIScene::GetScene().AssignNewTargetVolume(objectID);

	return 0;
}

extern "C" inline int GetCurrentObjectID(lua_State * aLuaState)
{
	int args = lua_gettop(aLuaState);

	size_t currentNode;
	currentNode = static_cast<size_t> (lua_tonumber(aLuaState, 1));

	ScriptSystem::AddArgumentsToStack(currentNode, LabbAIScene::GetScene().GetActiveObject());

	return 1;
}


void RegisterFunctions(const size_t aNodeIndex)
{
	ScriptSystem::RegisterFunction(aNodeIndex, "Print", PrintFromLua, "Will do a cout on each in arguemnt, ends with a newline. (there is no space or newline between arguments)");
	ScriptSystem::RegisterFunction(aNodeIndex, "MoveToFreeVolume", MoveToFreeVolume, "Gets a free volume index and moves towards it");
	ScriptSystem::RegisterFunction(aNodeIndex, "GetCurrentObjectID", GetCurrentObjectID, "Gets ID of current active object");
}

LabbAIScene * LabbAIScene::ourScene = nullptr;

LabbAIScene::LabbAIScene(SB::PostMasterState & aPostMasterState) : SB::Scene(aPostMasterState, "PhysxTestScene"/*, "Assets/Skyboxes/skybox4_16f.dds"*/)
{
	ourScene = this;

	ScriptSystem::Create();
	//ScriptSystem::RegisterEvent("VolumeEnter");
	ScriptSystem::RegisterEvent("TargetReached");
	ScriptSystem::RegisterEvent("KeyPress");

	ScriptSystem::SetLuaFunctionRegistrationInit(std::bind(RegisterFunctions, std::placeholders::_1));

	ScriptSystem::LoadScriptGraph("Graphs/GraphFile.json");
	//ScriptSystem::CallFunction("Init");

	myMouseCurrentIndex = 10;

	myVolumeSprites.Resize(8);

	for (unsigned short iVolume = 0; iVolume < myVolumeSprites.Size(); ++iVolume)
	{
		const float xOffset = 250 + myRandomizer.GetRandomValue(-100.f, 100.f);
		const float yOffset = 300 + myRandomizer.GetRandomValue(-100.f, 100.f);

		myVolumeSprites[iVolume].SetTexture(SB::Engine::GetResourceManager().Get<SB::Texture>("Sprites/CollisionVolume.dds"));
		myVolumeSprites[iVolume].SetPosition(SB::Vector2f(xOffset + (450.f * (iVolume % 4)), yOffset + (450 * (iVolume / 4))));
		myVolumeSprites[iVolume].SetOrigin(SB::Vector2f(128.f, 128.f));
	}

	//25
	myUnits.Resize(2);
	myCollidedStates.Resize(myUnits.Size(), false);

	for (unsigned short iUnit = 0; iUnit < myUnits.Size(); ++iUnit)
	{
		float xPosition = myRandomizer.GetRandomValue(100, 1920.f);
		float yPosition = myRandomizer.GetRandomValue(0, 1080.f);
		myUnits[iUnit].SetPosition(SB::Vector2f(xPosition, yPosition));
		myUnits[iUnit].SetTargetPosition(iUnit);
		myOccupiedIndexes.Add(iUnit);

		myUnits[iUnit].SetIndex(iUnit);
	}

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

	AIEventHandler::CheckEvadeOnBlendControllers();
	AIEventHandler::CheckEvadeOnFormationControllers();

	CollisionCheckAgainstVolume();
	CollisionCheckMouse();

	Scene::Update(aDeltaTime);
}

void LabbAIScene::Render()
{
	Scene::Render();

	for (unsigned short iVolume = 0; iVolume < myVolumeSprites.Size(); ++iVolume)
	{
		myGuiRenderTarget->Render(myVolumeSprites[iVolume]);
	}

	for (unsigned short iUnit = 0; iUnit < myUnits.Size(); ++iUnit)
	{
		myUnits[iUnit].DebugRender(*myGuiRenderTarget);
		myGuiRenderTarget->RenderBuffer();
		myUnits[iUnit].Render(*myGuiRenderTarget);
	}

}

const SB::Vector2f & LabbAIScene::GetVolumePosition(const unsigned short aVolumeIndex)
{
	return myVolumeSprites[aVolumeIndex].GetPosition();
}

LabbAIScene & LabbAIScene::GetScene()
{
	return *ourScene;
}

void LabbAIScene::SetActiveObject(const unsigned short aObjectID)
{
	myCurrentActiveObject = aObjectID;
}

unsigned short LabbAIScene::GetActiveObject() const
{
	return myCurrentActiveObject;
}

void LabbAIScene::AssignNewTargetVolume(const unsigned short aObjectID)
{
	unsigned short newVolumeIndex;
	do
	{
		newVolumeIndex = static_cast<unsigned short>(myRandomizer.GetRandomValue(0.f, 7.999f));

	} while (myOccupiedIndexes.Find(newVolumeIndex) != myOccupiedIndexes.FoundNone);

	unsigned short oldIndex = myUnits[aObjectID].GetTargetIndex();
	if (myOccupiedIndexes.Find(oldIndex) != myOccupiedIndexes.FoundNone)
	{
		myOccupiedIndexes.RemoveCyclic(oldIndex);
	}

	myOccupiedIndexes.Add(newVolumeIndex);
	myUnits[aObjectID].SetTargetPosition(newVolumeIndex);
}

void LabbAIScene::CollisionCheckAgainstVolume()
{
	for (unsigned short iUnit = 0; iUnit < myUnits.Size(); ++iUnit)
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

void LabbAIScene::CollisionCheckMouse()
{
	unsigned short currentIndex = 10;
	
	const SB::CircleShape mouseCollider(myMousePosition, 3.f);

	for (unsigned short iVolume = 0; iVolume < myVolumeSprites.Size(); ++iVolume)
	{
		SB::CircleShape volumeCollider(myVolumeSprites[iVolume].GetPosition(), 128.f);

		if (CollisionCheck(mouseCollider, volumeCollider) == true)
		{
			currentIndex = iVolume;
			break;
		}
	}

	
	if (currentIndex != myMouseCurrentIndex)
	{
		if (myOccupiedIndexes.Find(myMouseCurrentIndex) != myOccupiedIndexes.FoundNone)
		{
			myOccupiedIndexes.RemoveCyclic(myMouseCurrentIndex);
		}
	}
	

	if (currentIndex < 8)
	{
		if (myOccupiedIndexes.Find(currentIndex) == myOccupiedIndexes.FoundNone)
		{
			myOccupiedIndexes.Add(currentIndex);
		}
	}

	myMouseCurrentIndex = currentIndex;
}

void LabbAIScene::OnCollisionEnter(const unsigned short aObjectID, const unsigned short aVolumeID)
{
	//ScriptSystem::CallEvent("VolumeEnter");
}

