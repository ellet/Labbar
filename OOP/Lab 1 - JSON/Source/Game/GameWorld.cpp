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
#include "../tinyxml2/tinyxml2.h"
#include <string>
#include <iostream>
#include "../Picojson/picojson.h"

using namespace DX2D;
CGameWorld::CGameWorld()
{
}


CGameWorld::~CGameWorld()
{
	for (int i = 0; i < myMainMenuSprites.size(); ++i)
	{
		delete myMainMenuSprites[i];
		myMainMenuSprites[i] = nullptr;
	}

	myMainMenuSprites.clear();
}

void CGameWorld::ResetGame()
{
	myPlayer1Score = 0;
	myPlayer2Score = 0;
	myPlayer1.SetPosition(0.05f, 0.5f);
	myPlayer2.SetPosition(0.9f, 0.5f);
	myBall.Reset();
	myGameState = eGameState::eMainMenu;
}

void CGameWorld::Init()
{	
	myInputWrapper.Init(DX2D::CEngine::GetInstance()->GetHInstance(), *DX2D::CEngine::GetInstance()->GetHWND(),
		DX2D::CEngine::GetInstance()->GetWindowSize().x, DX2D::CEngine::GetInstance()->GetWindowSize().y);
	myText = new DX2D::CText("Text/calibril.ttf_sdf");


	myFileReader.open("JSON/settings.json");


	picojson::value wholeFile;

	picojson::parse(wholeFile, myFileReader);


	picojson::object root = wholeFile.get<picojson::object>();

	
	picojson::object objectToSet = root["paddles"].get<picojson::object>();

	myPlayer1.Init(objectToSet, false);
	myPlayer2.Init(objectToSet, true);

	objectToSet = root.find("balls")->second.get<picojson::object>();

	myBall.Init(objectToSet);

	objectToSet = root.find("titlescreen")->second.get<picojson::object>();

	picojson::array titleScreenPics = objectToSet.find("titlescreen")->second.get<picojson::array>();

	for (picojson::array::iterator iter = titleScreenPics.begin(); iter != titleScreenPics.end(); ++iter)
	{
		
		DX2D::CSprite* newSprite = new DX2D::CSprite((*iter).get("sprite").get<std::string>().c_str());
		picojson::object tempPos = (*iter).get("position").get<picojson::object>();
		float x = static_cast<float>(tempPos.find("x")->second.get<double>());
		float y = static_cast<float>(tempPos["y"].get<double>());
		newSprite->SetPosition(DX2D::Vector2f(x, y));
		myMainMenuSprites.push_back(newSprite);
	}

	

	ResetGame();
}

void CGameWorld::Update(float aDeltaTime)
{ 
	myInputWrapper.Update();

	switch (myGameState)
	{
	case eGameState::eMainMenu:
		if (myInputWrapper.GetKeyPressed(DIK_SPACE) == true)
		{
			ResetGame();
			myGameState = eGameState::ePlaying;
		}
		break;
	case eGameState::ePlaying:
		UpdateBall(aDeltaTime);
		myPlayer1.Update(aDeltaTime, myInputWrapper, myBall);
		myPlayer2.Update(aDeltaTime, myInputWrapper, myBall);
		CheckGameOverState();
		break;
	case eGameState::eGameOver:
		if (myInputWrapper.GetKeyPressed(DIK_SPACE) == true)
		{			
			myGameState = eGameState::eMainMenu;
		}
		break;
	}
	Render();
}

void CGameWorld::PrintScores()
{
	PrintText(0.05f, 0.1f, "Player 1");
	PrintText(0.05f, 0.15f, std::to_string(myPlayer1Score).c_str());

	PrintText(0.8f, 0.1f, "Player 2");
	PrintText(0.8f, 0.15f, std::to_string(myPlayer2Score).c_str());
}

void CGameWorld::CheckGameOverState()
{
	if (myPlayer1Score >= 3 || myPlayer2Score >= 3)
	{
		myGameState = eGameState::eGameOver;
	}
}

void CGameWorld::UpdateBall(const float aDeltaTime)
{
	myBall.Update(aDeltaTime);
	if (myBall.GetPosition().x <= 0)
	{
		myBall.Reset();
		myPlayer2Score++;
	}
	else if (myBall.GetPosition().x >= 1)
	{
		myBall.Reset();
		myPlayer1Score++;
	}

	if (myPlayer1.Collides(myBall) == true ||
		myPlayer2.Collides(myBall) == true)
	{
		myBall.ReverseDirection();
	}
}

void CGameWorld::Render()
{
	switch (myGameState)
	{
	case eGameState::eMainMenu:
		for (int i = 0; i < myMainMenuSprites.size(); ++i)
		{
			myMainMenuSprites[i]->Render();
		}
		break;

	case eGameState::eGameOver:
		PrintText(0.4f, 0.5f, "GAME OVER");
		PrintText(0.3f, 0.55f, "Press SPACE to restart");
		if (myPlayer1Score >= 3)
		{
			PrintText(0.4f, 0.6f, "Player 1 won");
		}
		else
		{
			PrintText(0.4f, 0.6f, "Player 2 won");
		}
		// Observe, no break, so next state will also be drawn
	case eGameState::ePlaying:
		PrintScores();
		myBall.Draw();
		myPlayer1.Draw();
		myPlayer2.Draw();
		break;
	default:
		assert(false && "Unknown gamestate found!");
	}
}

void CGameWorld::PrintText(const float aX, const float aY, const char* aText)
{
	myText->myPosition.Set(aX, aY);
	myText->myText = aText;
	myText->Render();
}




//double derp;
//double test;
////std::string derp;
////std::string line;
//
////std::getline(myFileReader, line);
//
//picojson::value getValue;
//picojson::value otherValue;
//
//picojson::parse(getValue, myFileReader);
//picojson::parse(otherValue, myFileReader);
//
//
//derp = getValue.get("firstName").get<double>();
//test = otherValue.get("firstName").get<double>();
////derp = static_cast<int> (getValue.get("test").get<double>());
//
//std::string error;
//
//bool doTrue = true;
//while (doTrue)
//{
//	error = picojson::parse(getValue, myFileReader);
//}