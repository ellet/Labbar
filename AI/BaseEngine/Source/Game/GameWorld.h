#pragma once
#include <vector>
#include <memory>
#include "Input\InputListener.h"

class BDSprite;

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
private:

	//DX2D::CSprite* mySprite;
	std::unique_ptr<BDSprite> mySprite;
	InputListener myInputListener;
};