#pragma once

#include "Renderer.h"
#include "WrappedSprite.h"
#include "InteMartinHittaKakaCluster.h"

class CGameWorld
{
public:
	CGameWorld(); 
	~CGameWorld();

	void Init(const Vector2ui & aWindowSize);

	void Update();

	void Draw();


private:
	Vector2f myWindowSize;

	InteMartinHittaKakaCluster myGraphCluster;

	Renderer myRenderer;
};