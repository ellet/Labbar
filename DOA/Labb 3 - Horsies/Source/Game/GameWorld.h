#pragma once
#include <vector>
#include "Board.h"
#include <thread>
#include <mutex>

namespace DX2D
{
	class CSprite;
	class CSpriteBatch;
	class CText;
	class CCustomShape;
} 

class CGameWorld
{
public:
	CGameWorld(); 
	~CGameWorld();

	void Init();
	void Update(float aTimeDelta); 
	void LogicThread(std::mutex & aMutex);


private:
	std::mutex * myRenderLock;
	std::thread * myLogicThread;

	Board myBoard;
	
	DX2D::CSprite* mySpriteHorse;
	DX2D::CSprite* mySpriteTile;

	
	DX2D::CSprite* myExplainForMartinWhatButtonHeShouldPressToShutdownTheProgramAndNotFailUsBecauseThatWouldBeVeryUnecessaryForUsToFailBecauseOfThatStupidReasonWhenWeSpendSoMuchTimeOnTheLabb;
	
};