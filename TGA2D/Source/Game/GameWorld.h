#pragma once

namespace Tga2D
{
	class CSprite;
}

class CGameWorld
{
public:
	CGameWorld(); 
	~CGameWorld();

	void Init();
	void Update(float aTimeDelta); 
private:
	Tga2D::CSprite* myTga2dLogoSprite;

};