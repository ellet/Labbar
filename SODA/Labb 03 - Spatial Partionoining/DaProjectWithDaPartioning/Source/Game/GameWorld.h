#pragma once
#include <vector>

class PartionGrid;

//namespace DX2D
//{
//	class CSprite;
//	class CSpriteBatch;
//	class CText;
//	class CCustomShape;
//} 

class StaticSprite;

class CGameWorld
{
public:
	CGameWorld(); 
	~CGameWorld();

	void Init();
	void Update(float aTimeDelta); 
	void Draw() const;
private:

	PartionGrid * myGrid;
	int testInt;
	
};