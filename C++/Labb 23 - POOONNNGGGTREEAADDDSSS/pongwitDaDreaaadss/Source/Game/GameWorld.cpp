#include "stdafx.h"
#include "GameWorld.h"

#include <tga2d/math/vector2.h>
#include <tga2d/Engine.h>
#include <tga2d/text/text.h>
#include <Macros.h>
#include <sstream>
#include "TinyXML2/tinyxml2.h"
#include <iostream>


//using namespace DX2D;
CGameWorld::CGameWorld()
{
	myGameObjects.resize(static_cast<size_t>(enumGameObjects::enumLength));
	myLeftSideScore = 0;
	myRightSideScore = 0;
	myBallSpeed = 0;
	myPaddleSpeed = 0;
	myPlayerHasWonBool = false;
	myShowSplashScreen = false;
	myDraw = false;
	
	myScoreText = nullptr;
	myTestPointer = nullptr;
}


CGameWorld::~CGameWorld()
{
	SAFE_DELETE(myScoreText);
	SAFE_DELETE(myTestPointer);
}

void CGameWorld::Init()
{
	tinyxml2::XMLDocument myTestDocument;
	myTestDocument.LoadFile("XML Files/TGA2Dtest.xml");

	tinyxml2::XMLElement * root = myTestDocument.FirstChildElement();

	ReadXMLFile(root->FirstChildElement());


	ResetBall();
	
	

	myGameObjects[static_cast<size_t>(enumGameObjects::eBall)].SetUseFriciton(false);
	myGameObjects[static_cast<size_t>(enumGameObjects::eBall)].SetClampToScreen(true);

	myScoreText = new DX2D::CText("Text/calibril.ttf_sdf");
	myScoreText->myText = "0 - 0";
	myScoreText->myPosition = DX2D::Vector2f(0.5f, 0.02f);
	myScoreText->myColor.Set(1, 1, 1, 1.0f);
	myScoreText->mySize = 0.4f;

	myTestPointer = new DX2D::CText("Text/calibril.ttf_sdf");
	myTestPointer->myText = "test stuff";
	myTestPointer->myPosition = DX2D::Vector2f(0.5f, 0.4f);
	myTestPointer->myColor.Set(1, 1, 1, 1.0f);
	myTestPointer->mySize = 0.4f;

	myInput.Initialize(DX2D::CEngine::GetInstance()->GetHInstance(), (*DX2D::CEngine::GetInstance()->GetHWND()));

	myRenderDrawBufferIs1 = true;
	myCurrentDrawBuffer = &myRenderBuffer1;
	myCurrentRenderBuffer = nullptr;
}


void CGameWorld::Update(float aTimeDelta)
{ 
	myInput.Update();

	if (myShowSplashScreen == true)
	{
		if (myInput.GetKeyPressed(DIK_RETURN) == true)
		{
			myShowSplashScreen = false;
		}
	}
	else
	{
		//myInput.Update();

		std::ostringstream ScoreTextMaker;

		if (myPlayerHasWonBool == false)
		{
			if (myInput.GetKeyDown(DIK_DOWNARROW))
			{
				myGameObjects[static_cast<size_t>(enumGameObjects::eSecondPadde)].SetMovement(270, myPaddleSpeed);//, 0.003f);
			}

			if (myInput.GetKeyDown(DIK_UPARROW))
			{
				myGameObjects[static_cast<size_t>(enumGameObjects::eSecondPadde)].SetMovement(90, myPaddleSpeed);//, 0.003f);
			}

			if (myInput.GetKeyDown(DIK_S))
			{
				myGameObjects[static_cast<size_t>(enumGameObjects::eFirstPaddle)].SetMovement(270, myPaddleSpeed);//, 0.003f);
			}

			if (myInput.GetKeyDown(DIK_W))
			{
				myGameObjects[static_cast<size_t>(enumGameObjects::eFirstPaddle)].SetMovement(90, myPaddleSpeed);//, 0.003f);
			}

			for (size_t iGameObjects = 0; iGameObjects < static_cast<size_t>(enumGameObjects::enumLength); ++iGameObjects)
			{
				myGameObjects[iGameObjects].Update(aTimeDelta);
			}

			const size_t TempBallIndex = static_cast<size_t>(enumGameObjects::eBall);
			for (size_t iGameObjects = 0; iGameObjects < static_cast<size_t>(enumGameObjects::enumLength); ++iGameObjects)
			{
				if (iGameObjects != TempBallIndex)
				{
					myGameObjects[TempBallIndex].CheckCollision(myGameObjects[iGameObjects].GetCollisionRectangle());
				}
			}

			if (myGameObjects[static_cast<size_t>(enumGameObjects::eBall)].GetPostion().x > 1.f)
			{
				myLeftSideScore += 1;
				ResetBall();
			}
			else if (myGameObjects[static_cast<size_t>(enumGameObjects::eBall)].GetPostion().x < 0.f)
			{
				myRightSideScore += 1;
				ResetBall();
			}

			if (myLeftSideScore > 2 || myRightSideScore > 2)
			{
				myPlayerHasWonBool = true;
			}

			ScoreTextMaker << myLeftSideScore;
			ScoreTextMaker << " - ";
			ScoreTextMaker << myRightSideScore;
		}
		else
		{
			if (myLeftSideScore > 2)
			{
				ScoreTextMaker << "Left side player has won";
			}
			else
			{
				ScoreTextMaker << "Right side player has won";
			}

			if (myInput.GetKeyPressed(DIK_RETURN))
			{
				myLeftSideScore = 0;
				myRightSideScore = 0;
				myPlayerHasWonBool = false;
			}
		}

		if (myInput.GetKeyPressed(DIK_1))
		{
			myTestPointer->myText = "Test 1";
			myTestPointer->Render();
		}

		if (myInput.GetKeyPressed(DIK_2))
		{
			myTestPointer->myText = "Test 2";
			myTestPointer->Render();
		}

		if (myInput.GetKeyPressed(DIK_3))
		{
			myTestPointer->myText = "Test 3";
			myTestPointer->Render();
		}

		myScoreText->myText = ScoreTextMaker.str();
	}
}

void CGameWorld::SetDraw()
{
	if (myShowSplashScreen == true)
	{
		for (size_t iSprite = 0; iSprite < mySplashScreenSprites.size(); ++iSprite)
		{
			myCurrentDrawBuffer->push_back((*mySplashScreenSprites[iSprite]));
		}
	}
	else
	{
		for (size_t iGameObjects = 0; iGameObjects < static_cast<size_t>(enumGameObjects::enumLength); ++iGameObjects)
		{
			myCurrentDrawBuffer->push_back(myGameObjects[iGameObjects].Draw());
		}

		myScoreText->Render();
	}
}

void CGameWorld::DoDraw()
{
	if (myCurrentRenderBuffer != nullptr)
	{
		for (size_t iRenderCommand = 0; iRenderCommand < myCurrentRenderBuffer->size(); ++iRenderCommand)
		{
			(*myCurrentRenderBuffer)[iRenderCommand].RenderSprite();
		}
	}
}

void CGameWorld::ResetBall()
{
	const int leftOrRight = (rand() % 2);
	float randomAngle = static_cast<float>(rand() % 90);
	int randomPosition = (rand() % 75);

	if (randomPosition <= 50)
	{
		randomPosition += 25;
	}

	const float normalizedPosition = static_cast<float>(randomPosition) / 100.f;

	if (leftOrRight == 0)
	{
		randomAngle += 135.f;
	}
	else
	{
		randomAngle += 315.f;
	}

	myGameObjects[static_cast<size_t>(enumGameObjects::eBall)].SetPosition(0.5f, normalizedPosition);
	myGameObjects[static_cast<size_t>(enumGameObjects::eBall)].SetMovement(randomAngle, 0.35f, true);
}

void CGameWorld::ReadXMLFile(tinyxml2::XMLElement * aStartingElement)
{
	tinyxml2::XMLElement * CurrentElementPoint = aStartingElement;
	while (CurrentElementPoint != nullptr)
	{
		std::string currentElementName = CurrentElementPoint->Name();

		if (currentElementName == "GAMEOBJECT")
		{
			SetAGameObject((CurrentElementPoint));
		}
		else if (currentElementName == "GAMESETTINGS")
		{
			SetGameSettings((CurrentElementPoint));
		}
		else if (currentElementName == "SPLASHSCREEN")
		{
			AddSplashScreenSprite((CurrentElementPoint));
		}
		else
		{
			std::cout << currentElementName << " is unkown data type" << std::endl;
		}

		CurrentElementPoint = CurrentElementPoint->NextSiblingElement();
	}
}

void CGameWorld::AddSplashScreenSprite(tinyxml2::XMLElement * aBaseElement)
{
	tinyxml2::XMLElement * BrowseElement = aBaseElement->FirstChildElement();

	std::string aSpritePath;
	float objectX = 0.f;
	float objectY = 0.f;

	while (BrowseElement != nullptr)
	{
		std::string testString = BrowseElement->Name();

		if (testString == "SPRITEPATH")
		{
			aSpritePath = BrowseElement->GetText();
		}

		if (testString == "PositionX")
		{
			BrowseElement->QueryFloatText(&objectX);
		}

		if (testString == "PositionY")
		{
			BrowseElement->QueryFloatText(&objectY);
		}

		BrowseElement = BrowseElement->NextSiblingElement();
	}

	mySplashScreenSprites.push_back(new DX2D::CSprite(aSpritePath.c_str()));
	mySplashScreenSprites[mySplashScreenSprites.size() - 1]->SetPosition(DX2D::Vector2f(objectX, objectY));
}

void CGameWorld::SetAGameObject(tinyxml2::XMLElement * aBaseElement)
{
	tinyxml2::XMLElement * BrowseElement = aBaseElement->FirstChildElement();

	enumGameObjects objectID;
	std::string aSpritePath;
	float objectX = 0.f;
	float objectY = 0.f;

	while (BrowseElement != nullptr)
	{
		std::string testString = BrowseElement->Name();

		if (testString == "ID")
		{
			std::string iDstring = BrowseElement->GetText();
			objectID = getObjectIDFromString(iDstring);
		}

		if (testString == "SPRITEPATH")
		{
			aSpritePath = BrowseElement->GetText();
		}

		if (testString == "PositionX")
		{
			BrowseElement->QueryFloatText(&objectX);
		}

		if (testString == "PositionY")
		{
			BrowseElement->QueryFloatText(&objectY);
		}

		BrowseElement = BrowseElement->NextSiblingElement();
	}

	myGameObjects[static_cast<size_t>(objectID)].Init(aSpritePath.c_str());
	myGameObjects[static_cast<size_t>(objectID)].SetPosition(objectX, objectY);
}

void CGameWorld::SetGameSettings(tinyxml2::XMLElement * aBaseElement)
{
	tinyxml2::XMLElement * BrowseElement = aBaseElement->FirstChildElement();

	while (BrowseElement != nullptr)
	{
		std::string testString = BrowseElement->Name();

		if (testString == "BALLSPEED")
		{
			BrowseElement->QueryFloatText(&myBallSpeed);
		}
		else if (testString == "PADDLESPEED")
		{
			BrowseElement->QueryFloatText(&myPaddleSpeed);
		}
		else
		{
			std::cout << testString << " :: NO SUCH SETTING" << std::endl;
		}

		BrowseElement = BrowseElement->NextSiblingElement();
	}
}

enumGameObjects CGameWorld::getObjectIDFromString(std::string & aString)
{
	if (aString == "pad1")
	{
		return enumGameObjects::eFirstPaddle;
	}
	else if (aString == "pad2")
	{
		return enumGameObjects::eSecondPadde;
	}
	else if (aString == "ball")
	{
		return enumGameObjects::eBall;
	}
	else
	{
		std::cout << aString << ":: NO SUCH GAMEOBJECT"<< std::endl;
		return enumGameObjects::enumLength;
	}
}

void CGameWorld::SetDrawBuffer()
{
	if (myRenderDrawBufferIs1 == true)
	{
		

		myRenderDrawBufferIs1 = false;
		myCurrentDrawBuffer = &myRenderBuffer2;
		myCurrentRenderBuffer = &myRenderBuffer1;
	}
	else
	{
		myRenderDrawBufferIs1 = true;
		myCurrentDrawBuffer = &myRenderBuffer1;
		myCurrentRenderBuffer = &myRenderBuffer2;
	}

	myCurrentDrawBuffer->clear();
}