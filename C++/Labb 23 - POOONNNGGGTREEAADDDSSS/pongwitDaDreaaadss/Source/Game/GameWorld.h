#pragma once
#include "GameObjects\GameObject.h"
#include <../CommonUtilities/InputWrapper.h>
#include "TinyXML2/tinyxml2.h"
#include <vector>
#include "GameObjects\RenderCommand.h"

namespace DX2D
{
	class CText;
}

enum class enumGameObjects
{
	eBall,
	eFirstPaddle,
	eSecondPadde,
	enumLength
};

class CGameWorld
{
public:
	CGameWorld();
	~CGameWorld();
	void Init();
	void Update(float aTimeDelta);
	void SetDraw();

	void DoDraw();

	void SetDrawBuffer();

private:
	void ReadXMLFile(tinyxml2::XMLElement * aStartingElement);
	void SetAGameObject(tinyxml2::XMLElement * aBaseElement);
	void SetGameSettings(tinyxml2::XMLElement * aBaseElement);
	void AddSplashScreenSprite(tinyxml2::XMLElement * aBaseElement);
	enumGameObjects getObjectIDFromString(std::string & aString);

	void ResetBall();
	

	float myBallSpeed;
	float myPaddleSpeed;

	std::vector<GameObject> myGameObjects;
	
	size_t myLeftSideScore;
	size_t myRightSideScore;

	std::vector<DX2D::CSprite*>mySplashScreenSprites;

	DX2D::CText* myScoreText;

	DX2D::CText* myTestPointer;

	InputWrapper myInput;

	bool myDraw;
	bool myShowSplashScreen;
	bool myPlayerHasWonBool;
	bool myRenderDrawBufferIs1;


	std::vector<RenderCommand> * myCurrentDrawBuffer;
	std::vector<RenderCommand> * myCurrentRenderBuffer;
	std::vector<RenderCommand> myRenderBuffer1;
	std::vector<RenderCommand> myRenderBuffer2;
};