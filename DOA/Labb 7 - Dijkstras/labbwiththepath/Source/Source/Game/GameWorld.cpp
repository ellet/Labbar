#include "stdafx.h"
#include "GameWorld.h"

#include <tga2d/Engine.h>
#include <tga2d/sprite/sprite.h>

#include "Renderer.h"
#include <InputWrapper/SingletonInputWrapper.h>

#include <Timer/Alarm.h>

const size_t nodeAmount = 25;

CGameWorld::CGameWorld()
{
	
}


CGameWorld::~CGameWorld()
{
}

void CGameWorld::Init(const Vector2ui & aWindowSize)
{
	myRenderer.Init();
	myRenderer.SetWindowSize(aWindowSize);
	myGraphCluster.Init();

	myUpdateClusterAlarm = new CU::Alarm(0.5f, true);

	Vector2f windowFloat(aWindowSize.x, aWindowSize.y);
	//windowFloat /= ;

	myWindowSize = windowFloat;

	myGraphCluster.GenerateMap(nodeAmount, windowFloat);
	myGraphCluster.AddNodesToRenderer(myRenderer);

	myState = eGameState::eSetStartNode;
}

void CGameWorld::Update()
{
	if (myState == eGameState::eCalculating && myGraphCluster.CheckIfDone() == true)
	{
		myState = eGameState::eSetStartNode;
	}

	if (myState == eGameState::eSetStartNode && CU::SingletonInputWrapper::GetKeyReleased(DIK_H) == true)
	{
		myState = eGameState::eInfo;
	}
	else if (myState == eGameState::eInfo && (CU::SingletonInputWrapper::GetKeyReleased(DIK_H) == true || CU::SingletonInputWrapper::GetKeyReleased(DIK_ESCAPE) == true))
	{
		myState = eGameState::eSetStartNode;
	}

	if (CU::SingletonInputWrapper::GetKeyReleased(DIK_SPACE) == true && myState == eGameState::eSetStartNode)
	{
		myRenderer.ResetRender();
		myGraphCluster.GenerateMap(nodeAmount, myWindowSize);
		myGraphCluster.AddNodesToRenderer(myRenderer);
	}

	if (myState != eGameState::eInfo)
	{

		if (CU::SingletonInputWrapper::GetKeyReleased(DIK_Q) == true && myState != eGameState::eCalculating)
		{
			myState = eGameState::eCalculating;
			myGraphCluster.FindPath();
		}

		if (CU::SingletonInputWrapper::GetMouseButtonPressed(CU::enumMouseButtons::eLeft) == true)
		{
			if (myState == eGameState::eSetStartNode)
			{
				if (myGraphCluster.SetStartNodeWithMouse(CU::SingletonInputWrapper::GetMouseWindowPosition()) == true)
				{
					myState = eGameState::eSetGoalNode;
				}
			}
			else if (myState == eGameState::eSetGoalNode)
			{
				if (myGraphCluster.SetGoalNodeWithMouse(CU::SingletonInputWrapper::GetMouseWindowPosition()) == true)
				{
					myState = eGameState::eCalculating;
					myGraphCluster.FindPath();

				}
			}


		}

		if (myUpdateClusterAlarm->GetProgress() >= 1.f)
		{
			myGraphCluster.Update();
		}
	}
}

void CGameWorld::Draw()
{
	if (myState == eGameState::eInfo)
	{
		PrintHalp();
	}
	else
	{
		myGraphCluster.DrawLinks(myRenderer);

		myRenderer.Draw();

		myGraphCluster.PrintNodeValues(myRenderer);
		myRenderer.PrintText("Press H for Halp.", Vector2f(25.f,25.f));
	}
}

void CGameWorld::PrintHalp()
{
	myRenderer.PrintText("HALP:", Vector2f(100.f, 200.f));
	myRenderer.PrintText("Press H or escape to return to Dijkstras and the bushes.", Vector2f(100.f, 260.f));
	myRenderer.PrintText("Click on bushes to assign them as start and goal bushes.", Vector2f(200.f, 350.f));
	myRenderer.PrintText("Press Space to randomize a new forest. (Only available when not calculating)", Vector2f(200.f, 380.f));
	myRenderer.PrintText("Press Q to randomize start and goal bushes.", Vector2f(200.f, 410.f));
}
