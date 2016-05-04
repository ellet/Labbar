#include "stdafx.h"
#include "GameWorld.h"

#include <tga2d/sprite/sprite.h>
#include <tga2d/Engine.h>
#include <tga2d/light/light_manager.h>
#include <tga2d/sprite/sprite_batch.h>
#include <tga2d/drawers/debug_drawer.h>
#include <tga2d/text/text.h>
#include <tga2d/primitives/custom_shape.h>
#include <tga2d/math/color.h>
#include "TinyXML2\tinyxml2.h"
#include <iostream>

using namespace DX2D;
CGameWorld::CGameWorld()
{
}


CGameWorld::~CGameWorld()
{
}

void CGameWorld::Init()
{		
	tinyxml2::XMLDocument myTestDocument;
	myTestDocument.LoadFile("TGA2Dtest.xml");

	tinyxml2::XMLElement * root = myTestDocument.FirstChildElement();

	SetAGameObject((*root->FirstChildElement()));

	myCarSprite = new DX2D::CSprite("sprites/car_1.dds");
	myCarSprite2 = new DX2D::CSprite("sprites/car_1.dds");


	myCarSprite->SetPosition(DX2D::Vector2f(0.0f, 0.0f));
	myCarSprite2->SetPosition(DX2D::Vector2f(myCarSprite->GetSize().x, myCarSprite->GetSize().y));


	Vector2f size = myCarSprite->GetSize();

	text = new DX2D::CText("Text/calibril.ttf_sdf");
	text->myText = "Test";
	text->myPosition = DX2D::Vector2f(0.5f, 0.02f);
	text->myColor.Set(1, 1, 1, 1.0f);
	text->mySize = 0.4f;
}


void CGameWorld::Update(float /*aTimeDelta*/)
{ 

	text->Render();

	


	myCarSprite->Render();
	myCarSprite2->Render();

	CEngine::GetInstance()->GetLightManager().SetAmbience(1.0f);
}

void CGameWorld::ReadXMLFile(tinyxml2::XMLElement & aStartingElement)
{
	tinyxml2::XMLElement * CurrentElementPoint = &aStartingElement;
	while (CurrentElementPoint != nullptr)
	{
		std::string currentElementName = CurrentElementPoint->Name();

		if (currentElementName == "GAMEOBJECT")
		{
			SetAGameObject((*CurrentElementPoint));
		}
		else
		{
			std::cout << currentElementName << " is unkown data type" << std::endl;
		}

		CurrentElementPoint = CurrentElementPoint->NextSiblingElement();
	}
}

void CGameWorld::SetAGameObject(tinyxml2::XMLElement & aBaseElement)
{
	tinyxml2::XMLElement * BrowseElement = aBaseElement.FirstChildElement();

	while (BrowseElement != nullptr)
	{
		std::string testString = BrowseElement->GetText();

		BrowseElement = BrowseElement->NextSiblingElement();
	}
}