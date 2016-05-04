#pragma once
#include "GameObjects\GameObject.h"
#include <../CommonUtilities/InputWrapper.h>
#include <vector>

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
	void Draw();

private:
	void ResetBall();

	std::vector<GameObject> myGameObjects;
	
	size_t myLeftSideScore;
	size_t myRightSideScore;

	DX2D::CText* myScoreText;

	DX2D::CText* myTestPointer;

	InputWrapper myInput;

	bool myPlayerHasWonBool;
};