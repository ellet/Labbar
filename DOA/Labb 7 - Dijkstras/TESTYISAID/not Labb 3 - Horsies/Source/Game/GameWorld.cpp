#include "stdafx.h"
#include "GameWorld.h"

#include <tga2d/Engine.h>
#include <tga2d/sprite/sprite.h>

#include "Renderer.h"
#include <InputWrapper/SingletonInputWrapper.h>

const size_t nodeAmount = 15;

CGameWorld::CGameWorld()
{
	
}


CGameWorld::~CGameWorld()
{
}

void CGameWorld::Init(const Vector2ui & aWindowSize)
{
	myRenderer.Init();
	myRenderer.SetWindowSize(aWindowSize);
	myGraphCluster.Init();

	

	Vector2f windowFloat(aWindowSize.x, aWindowSize.y);
	//windowFloat /= ;

	myWindowSize = windowFloat;

	myGraphCluster.GenerateMap(nodeAmount, windowFloat);
	myGraphCluster.AddNodesToRenderer(myRenderer);
}

void CGameWorld::Update()
{
	if (CU::SingletonInputWrapper::GetKeyReleased(DIK_SPACE) == true)
	{
		myRenderer.ResetRender();
		myGraphCluster.GenerateMap(nodeAmount, myWindowSize);
		myGraphCluster.AddNodesToRenderer(myRenderer);
	}

	if (CU::SingletonInputWrapper::GetKeyReleased(DIK_Q) == true)
	{
		myGraphCluster.FindPath();
	}
}

void CGameWorld::Draw()
{
	myGraphCluster.DrawLinks(myRenderer);

	myRenderer.Draw();
}


