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

	const float MagicNumberForScale = 0.5f;

	myGubbeWithHat.AddDot(Vector2<float>(0.f, 0.f));
	myGubbeWithHat.AddDot(Vector2<float>(0.1f, 0.1f));
	myGubbeWithHat.AddDot(Vector2<float>(0.2f, 0.2f));
	myGubbeWithHat.AddDot(Vector2<float>(0.3f, 0.1f));
	myGubbeWithHat.AddDot(Vector2<float>(0.2f, 0.f));
											  
	myGubbeWithHat.AddDot(Vector2<float>(0.2f, 0.3f));
	myGubbeWithHat.AddDot(Vector2<float>(0.2f, 0.5f));
	myGubbeWithHat.AddDot(Vector2<float>(0.2f, 0.6f));
	myGubbeWithHat.AddDot(Vector2<float>(0.2f, 0.7f));
	myGubbeWithHat.AddDot(Vector2<float>(0.1f, 0.7f));
										   	  
	myGubbeWithHat.AddDot(Vector2<float>(0.1f, 0.6f)); 
	myGubbeWithHat.AddDot(Vector2<float>(0.1f, 0.4f));


	for (unsigned int i = 0; i < myGubbeWithHat.GetMyDots().Size(); ++i)
	{
		myGubbeWithHat.GetMyDots()[i].SetPosition(myGubbeWithHat.GetMyDots()[i].GetPosition() * MagicNumberForScale);
	}

	
}

void CGameWorld::Update(float aTimeDelta)
{ 
	GameObjectsManager::Update(aTimeDelta);

	myGubbeWithHat.Rotate(1.f * aTimeDelta);
	
}

void CGameWorld::Draw()
{
	GameObjectsManager::Draw();
}