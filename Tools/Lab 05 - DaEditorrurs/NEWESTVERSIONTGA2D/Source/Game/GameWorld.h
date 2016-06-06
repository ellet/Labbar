#pragma once
#include <vector>
#include <Rend/StaticSprite.h>

class Camera2D;

class CGameWorld
{
public:
	CGameWorld(); 
	~CGameWorld();

	void Init();
	void Update(float aTimeDelta); 
	void Draw();

private:
	Camera2D * myCamera;
	StaticSprite mySprite;
};