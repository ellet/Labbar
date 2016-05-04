#include "stdafx.h"
#include "GameWorld.h"

#include <tga2d/math/vector2.h>
#include <tga2d/Engine.h>
#include <tga2d/text/text.h>
#include <Macros.h>
#include <sstream>
#include "TinyXML2/tinyxml2.h"
#include <iostream>
#include "BaseGameStructure\GameObjectsManager.h"
#include "../CommonUtilities/Vectors/Vector.h"


//using namespace DX2D;
CGameWorld::CGameWorld()
{
	testRotation = 0.f;
}


CGameWorld::~CGameWorld()
{
}

void CGameWorld::Init()
{
	myInput.Initialize(DX2D::CEngine::GetInstance()->GetHInstance(), (*DX2D::CEngine::GetInstance()->GetHWND()));

	const float MagicNumberForScale = 0.5f;

	//myTHING.Init(Vector2<float>(0.0f, 0.0f), nullptr);
	myGubbeWithHat.Init(Vector2<float>(0.0f, 0.0f), nullptr);
	myGubbeArm.Init((Vector2<float>(0.1f, 0.4f) * MagicNumberForScale), myGubbeWithHat.GetMySpace());
	myGubbeSword.Init(((Vector2<float>(-0.4f, 0.f)* MagicNumberForScale)* MagicNumberForScale), myGubbeArm.GetMySpace(), "sprites/redDot.png");

	CommonUtilities::GrowingArray<Vector2<float>> positions;
	CommonUtilities::GrowingArray<Vector2<float>> line;

	line.Init(50);
	positions.Init(12);

	positions.Add(Vector2<float>(0.f, 0.f));
	positions.Add(Vector2<float>(0.1f, 0.1f));
	positions.Add(Vector2<float>(0.2f, 0.2f));
	positions.Add(Vector2<float>(0.3f, 0.1f));
	positions.Add(Vector2<float>(0.2f, 0.f));

	positions.Add(Vector2<float>(0.2f, 0.3f));
	positions.Add(Vector2<float>(0.2f, 0.5f));
	positions.Add(Vector2<float>(0.2f, 0.6f));
	positions.Add(Vector2<float>(0.2f, 0.7f));
	positions.Add(Vector2<float>(0.1f, 0.7f));

	positions.Add(Vector2<float>(0.1f, 0.6f));
	//positions.Add(Vector2<float>(0.1f, 0.4f));

	for (float i = 0; i < 40; ++i)
	{

		line.Add(Vector2<float>(-i * 0.005f, 0.f));

		myGubbeSword.AddChild(line[i], myGubbeSword.GetMySpace(), "sprites/redDot.png");
		line[i] *= 0.5f;

		myGubbeArm.AddChild(line[i], myGubbeArm.GetMySpace());
	}
	myGubbeArm.AddChild(myGubbeSword);

	for (unsigned int i = 0; i < positions.Size(); ++i)
	{
		//myGubbeWithHat.GetMyChildren()[i]->SetPosition(myGubbeWithHat.GetMyChildren()[i]->GetPosition() * MagicNumberForScale);
		positions[i] *= MagicNumberForScale;
	}

	for (unsigned int i = 0; i < positions.Size(); ++i)
	{
		myGubbeWithHat.AddChild(positions[i], myGubbeWithHat.GetMySpace());
	}

	for (unsigned int i = 0; i < positions.Size(); ++i)
	{
		//myGubbeWithHat.GetMyChildren()[i]->SetPosition(myGubbeWithHat.GetMyChildren()[i]->GetPosition() * MagicNumberForScale);
		positions[i] *= MagicNumberForScale;
	}

	/*for (unsigned int i = 0; i < positions.Size(); ++i)
	{
		myGubbeArm.AddChild(positions[i], myGubbeArm.GetMySpace());
	}*/
	myGubbeWithHat.AddChild(myGubbeArm);

	myGubbeArm.Rotate(-1.f);
	myGubbeSword.Rotate(2.f);


	/*myGubbeWithHat.AddChild(Vector2<float>(0.f, 0.f), myGubbeWithHat.GetMySpace());
	myGubbeWithHat.AddChild(Vector2<float>(0.1f, 0.1f),myGubbeWithHat.GetMySpace());
	myGubbeWithHat.AddChild(Vector2<float>(0.2f, 0.2f),myGubbeWithHat.GetMySpace());
	myGubbeWithHat.AddChild(Vector2<float>(0.3f, 0.1f),myGubbeWithHat.GetMySpace());
	myGubbeWithHat.AddChild(Vector2<float>(0.2f, 0.f), myGubbeWithHat.GetMySpace());
											  		  
	myGubbeWithHat.AddChild(Vector2<float>(0.2f, 0.3f),myGubbeWithHat.GetMySpace());
	myGubbeWithHat.AddChild(Vector2<float>(0.2f, 0.5f),myGubbeWithHat.GetMySpace());
	myGubbeWithHat.AddChild(Vector2<float>(0.2f, 0.6f),myGubbeWithHat.GetMySpace());
	myGubbeWithHat.AddChild(Vector2<float>(0.2f, 0.7f),myGubbeWithHat.GetMySpace());
	myGubbeWithHat.AddChild(Vector2<float>(0.1f, 0.7f),myGubbeWithHat.GetMySpace());
										   	  		  
	myGubbeWithHat.AddChild(Vector2<float>(0.1f, 0.6f),myGubbeWithHat.GetMySpace()); 
	myGubbeWithHat.AddChild(Vector2<float>(0.1f, 0.4f),myGubbeWithHat.GetMySpace());*/
	/*for (unsigned int i = 0; i < myGubbeWithHat.GetMyChildren().Size(); ++i)
	{
		myGubbeWithHat.GetMyChildren()[i]->SetPosition(myGubbeWithHat.GetMyChildren()[i]->GetPosition() * MagicNumberForScale);
	}*/

	GameObjectsManager::SetCameraPosition(Vector2f( 0.0f, 0.0f));
}

void CGameWorld::Update(float aTimeDelta)
{
	GameObjectsManager::Update(aTimeDelta);

	myInput.Update();

	if (myInput.GetKeyDown(DIK_W))
	{
		GameObjectsManager::IncreaseCameraPosition((Vector2f(0.f, -0.10f) * aTimeDelta));
	}

	if (myInput.GetKeyDown(DIK_S))
	{
		GameObjectsManager::IncreaseCameraPosition((Vector2f(0.f, 0.10f) * aTimeDelta));
	}

	if (myInput.GetKeyDown(DIK_A))
	{
		GameObjectsManager::IncreaseCameraPosition((Vector2f(-0.10f, 0.f) * aTimeDelta));
	}

	if (myInput.GetKeyDown(DIK_D))
	{
		GameObjectsManager::IncreaseCameraPosition((Vector2f(0.10f, 0.f) * aTimeDelta));
	}

	if (myInput.GetKeyDown(DIK_E))
	{
		GameObjectsManager::IncreaseCameraRotation((0.5f * aTimeDelta));
	}

	if (myInput.GetKeyDown(DIK_Q))
	{
		GameObjectsManager::IncreaseCameraRotation((-0.5f * aTimeDelta));
	}

	//myGubbeWithHat.Rotate(1.f * aTimeDelta);
	//myGubbeArm.Rotate(1.f * aTimeDelta);
	//myGubbeSword.Rotate(0.5f * aTimeDelta);
	myGubbeArm.Rotate(1.f * aTimeDelta);
}

void CGameWorld::Draw()
{
	GameObjectsManager::Draw();
}