#include "StdAfx.h"
#include "ScoreHandler.h"
#include "Frog.h"
#include "TileGrid.h"
#include "MainSingleton.h"
#include "SpriteContainer.h"

FG::ScoreHandler::ScoreHandler()
{
}

FG::ScoreHandler::~ScoreHandler()
{
}

void FG::ScoreHandler::Init(Frog* aFrog)
{
    myFrog = aFrog;

    InitFont();       
    InitFrogHomes();
   
    myCurrentLevelToGetScore = 400;
	myHasFoundHome = false;
	myCurrentBugIndex = -1;

	myBugSpawnTimer = TIME_BETWEEN_BUG_SPAWNS;
	myTimeForBugToStay = TIME_FOR_BUG_TO_STAY;
}

void FG::ScoreHandler::ReInit()
{
    myCurrentLevelToGetScore = 400;
	myHasFoundHome = false;

    for(int index = 0; index < 5; index++)
    {
        myFrogHomes[index].myFirstTile->myIsWater = false;
        myFrogHomes[index].mySecondTile->myIsWater = false;
        myFrogHomes[index].myIsTaken = false;
		myFrogHomes[index].myHasBug = false;
    }

	myCurrentBugIndex = -1;
	myBugSpawnTimer = TIME_BETWEEN_BUG_SPAWNS;
	myTimeForBugToStay = TIME_FOR_BUG_TO_STAY;
}

void FG::ScoreHandler::InitFont()
{
    myFont = new hgeFont("Fonts/font1.fnt");
    DWORD color = ARGB(255,255,255,255);
    myFont->SetColor(color);
    myFont->SetScale(0.5f);    
}

void FG::ScoreHandler::InitFrogHomes()
{
    myFrogHomes[0].myFirstTile = &MainSingleton::GetInstance()->GetTileGrid()->GetTileSet()[0][0];
    myFrogHomes[0].mySecondTile = &MainSingleton::GetInstance()->GetTileGrid()->GetTileSet()[1][0];
    myFrogHomes[0].myPosition = CU::Vector2f(32.0f,21.0f);
    myFrogHomes[0].myIsTaken = false;
	myFrogHomes[0].myHasBug = false;

    myFrogHomes[1].myFirstTile = &MainSingleton::GetInstance()->GetTileGrid()->GetTileSet()[3][0];
    myFrogHomes[1].mySecondTile = &MainSingleton::GetInstance()->GetTileGrid()->GetTileSet()[4][0];
    myFrogHomes[1].myPosition = CU::Vector2f(129,21.0f);
    myFrogHomes[1].myIsTaken = false;
	myFrogHomes[1].myHasBug = false;

    myFrogHomes[2].myFirstTile = &MainSingleton::GetInstance()->GetTileGrid()->GetTileSet()[6][0];
    myFrogHomes[2].mySecondTile = &MainSingleton::GetInstance()->GetTileGrid()->GetTileSet()[7][0];
    myFrogHomes[2].myPosition = CU::Vector2f(226,21.0f);
    myFrogHomes[2].myIsTaken = false;
	myFrogHomes[2].myHasBug = false;

    myFrogHomes[3].myFirstTile = &MainSingleton::GetInstance()->GetTileGrid()->GetTileSet()[9][0];
    myFrogHomes[3].mySecondTile = &MainSingleton::GetInstance()->GetTileGrid()->GetTileSet()[10][0];
    myFrogHomes[3].myPosition = CU::Vector2f(322,21.0f);
    myFrogHomes[3].myIsTaken = false;
	myFrogHomes[3].myHasBug = false;

    myFrogHomes[4].myFirstTile = &MainSingleton::GetInstance()->GetTileGrid()->GetTileSet()[12][0];
    myFrogHomes[4].mySecondTile = &MainSingleton::GetInstance()->GetTileGrid()->GetTileSet()[13][0];
    myFrogHomes[4].myPosition = CU::Vector2f(417,21.0f);
    myFrogHomes[4].myIsTaken = false;
	myFrogHomes[4].myHasBug = false;

    for(int index = 0; index < 5; index++)
    {
        myFrogHomes[index].myFirstTile->myIsWater = false;
        myFrogHomes[index].mySecondTile->myIsWater = false;
    }
}

bool FG::ScoreHandler::LevelCompleted()
{
	for(int index = 0; index < 5; index++)
    {
		if(myFrogHomes[index].myIsTaken == false)
		{
			return false;
		}
	}

	return true;
}

void FG::ScoreHandler::Update()
{
    HandleMovementScore();
    HandleFrogHomes();  
	HandleBugSpawn();
}

void FG::ScoreHandler::HandleMovementScore()
{
    if(myFrog->IsDead() == false)
    {
        float currentTilePos = myFrog->GetCurrentTile()->myPosition.myY;
        if(currentTilePos < myCurrentLevelToGetScore)
        {
            myFrog->AddScore(SCORE_EACH_STEP);
            myCurrentLevelToGetScore = currentTilePos;
        }
    }
    else
    {
        myCurrentLevelToGetScore = 400;
    }
}

void FG::ScoreHandler::HandleFrogHomes()
{
    for(int index = 0; index < 5; index++)
    {
        if(myFrogHomes[index].myIsTaken == false)
        {
            if(myFrog->GetCurrentTile() == myFrogHomes[index].myFirstTile ||
               myFrog->GetCurrentTile() == myFrogHomes[index].mySecondTile)
            {
                myFrog->AddScore(SCORE_FROG_HOME);
                myFrogHomes[index].myIsTaken = true;
                myFrogHomes[index].myFirstTile->myIsWater = true;
                myFrogHomes[index].mySecondTile->myIsWater = true;
                myFrog->Respawn();
				myFrog->SetFoundHome(true);
				myCurrentLevelToGetScore = 400;

				if(myFrogHomes[index].myHasBug)
				{
					myFrog->AddScore(SCORE_PICKUP_BUG);
					myFrogHomes[myCurrentBugIndex].myHasBug = false;
					myTimeForBugToStay = TIME_FOR_BUG_TO_STAY;
					myCurrentBugIndex = -1;
				}
            }
        }
    }
}

void FG::ScoreHandler::HandleBugSpawn()
{
	if(myCurrentBugIndex == -1) //No Bug in world
	{
		float time = static_cast<float>(MainSingleton::GetInstance()->GetTimeManager()->GetElapsedTime(CU::GAME_CLOCK).GetTime());

		myBugSpawnTimer -= time;
		if(myBugSpawnTimer <= 0)
		{
			myBugSpawnTimer = TIME_BETWEEN_BUG_SPAWNS;
			AddBug();
		}
	}
	else
	{
		float time = static_cast<float>(MainSingleton::GetInstance()->GetTimeManager()->GetElapsedTime(CU::GAME_CLOCK).GetTime());
		myTimeForBugToStay -= time;
		if(myTimeForBugToStay <= 0)
		{
			myFrogHomes[myCurrentBugIndex].myHasBug = false;
			myTimeForBugToStay = TIME_FOR_BUG_TO_STAY;
			myCurrentBugIndex = -1;
		}
	}
}

void FG::ScoreHandler::AddBug()
{	
	myCurrentBugIndex = -1;

	CU::GrowingArray<int> possibleHomes;
	for(int index = 0; index < 5; index++)
	{
		if(myFrogHomes[index].myIsTaken == false)
		{
			possibleHomes.Add(index);
		}
	}
	
	int random = rand() % possibleHomes.Count();
	myCurrentBugIndex = possibleHomes[random];
	
	if(myCurrentBugIndex != -1)
	{
		myFrogHomes[myCurrentBugIndex].myHasBug = true;
	}
}
    
void FG::ScoreHandler::Render()
{    
    //Render Score
    char score[32] = "Score: ";
    char number[16];
    _itoa_s(myFrog->GetScore(), number, 16, 10);
    for(int index = 0; index < 16; index++)
    {
        score[7+index] = number[index];
    }
    myFont->Render(10, 448, HGETEXT_LEFT, score);
    
    //Render Lives
    int frogLives = myFrog->GetNumberOfLives();
    for(int index = 0; index < frogLives; index++)
    {
        hgeSprite* sprite = MainSingleton::GetInstance()->GetSpriteContainer()->GetSprite(IDLE_UP_SPRITE);
        sprite->RenderStretch(static_cast<float>(10 + 20 * index), 430.0f, static_cast<float>(30 + 20 * index), 450.0f);
    }

    //Render Frog Homes
    for(int index = 0; index < 5; index++)
    {
        if(myFrogHomes[index].myIsTaken)
        {
            hgeSprite* sprite = MainSingleton::GetInstance()->GetSpriteContainer()->GetSprite(IDLE_DOWN_SPRITE);
            sprite->Render(myFrogHomes[index].myPosition.myX, myFrogHomes[index].myPosition.myY);
        }

		if(myFrogHomes[index].myHasBug)
        {
			hgeSprite* sprite = MainSingleton::GetInstance()->GetSpriteContainer()->GetSprite(BUG_SPRITE);
            sprite->Render(myFrogHomes[index].myPosition.myX, myFrogHomes[index].myPosition.myY);
		}
    }
}
