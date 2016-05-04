#pragma once
#include <vector>


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

	DX2D::CSprite* mySprite;
	
};