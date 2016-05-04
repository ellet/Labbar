#pragma once

#include "Renderer.h"
#include "WrappedSprite.h"
#include "InteMartinHittaKakaCluster.h"

namespace CommonUtilities
{
	class Alarm;
}

enum class eGameState
{
	eSetStartNode,
	eSetGoalNode,
	eCalculating,
	eInfo
};

class CGameWorld
{
public:
	CGameWorld(); 
	~CGameWorld();

	void Init(const Vector2ui & aWindowSize);

	void Update();

	void Draw();

	void PrintHalp();

private:
	CU::Alarm * myUpdateClusterAlarm;

	Vector2f myWindowSize;

	InteMartinHittaKakaCluster myGraphCluster;

	Renderer myRenderer;

	eGameState myState;
};