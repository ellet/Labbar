#include "stdafx.h"
#include "GameWorld.h"

#include <tga2d/Engine.h>
#include <tga2d/sprite/sprite.h>
#include <CU/Vectors/Vector2.h>
#include "Renderer.h"
#include "WrappedSprite.h"
#include <CU/InputWrapper/SingletonInputWrapper.h>
#include "TextState.h"
#include <ProxyStateStack.h>

const float Speed = 150.f;


CGameWorld::CGameWorld()
{
}


CGameWorld::~CGameWorld()
{
	if (myTestSprite != nullptr)
	{
		SAFE_DELETE(myTestSprite);
	}
}


void CGameWorld::Init()
{
	myRenderer = new Renderer();
	myRenderer->Init("Sprites/hestfan.png");
	myRenderer->SetWindowSize(CU::Vector2ui(1280, 720));

	myTestSprite = new WrappedSprite();
	

	myTestSprite->Init();
	myTestSprite->SetPosition(CU::Vector2f(250.f, 250.f));
	myRenderer->AddNodeToDraw(*myTestSprite);
}


eStackReturnValue CGameWorld::Update(const CU::Time & aTimeDelta, ProxyStateStack & aStateStack)
{

	float kLeft = 0.f;
	float kRight = 0.f;
	float kUp = 0.f;
	float kDown = 0.f;

	if (GetInput::GetKeyDown(DIK_H) == true)
	{
		kLeft = 1.f;
	}

	if (GetInput::GetKeyDown(DIK_K) == true)
	{
		kRight = 1.f;
	}

	if (GetInput::GetKeyDown(DIK_U) == true)
	{
		kUp = 1.f;
	}

	if (GetInput::GetKeyDown(DIK_J) == true)
	{
		kDown = 1.f;
	}

	if (GetInput::GetKeyReleased(DIK_Q) == true)
	{
		bool isFalse = false;
		DL_ASSERT(isFalse, "IT Works!");
	}

	CU::Vector2f InputVector(kRight - kLeft, kDown - kUp);

	CU::Vector2f CurrentPosition = myTestSprite->GetPosition();

	CurrentPosition += InputVector * Speed * aTimeDelta.GetSeconds();

	myTestSprite->SetPosition(CurrentPosition);

	if (GetInput::GetKeyPressed(DIK_A) == true)
	{
		TextState * tempState = new TextState();
		tempState->Init();
		aStateStack.AddSubState(tempState);
	}

	if (GetInput::GetKeyPressed(DIK_END) == true)
	{
		return eStackReturnValue::ePopSubState;
	}
	if (GetInput::GetKeyPressed(DIK_HOME) == true)
	{
		return eStackReturnValue::ePopCurrentSubStates;
	}
	if (GetInput::GetKeyPressed(DIK_DELETE) == true)
	{
		return eStackReturnValue::ePopMain;
	}

	return eStackReturnValue::eStay;
}

void CGameWorld::Draw()
{
	myRenderer->UpdateSprite(*myTestSprite);
	myRenderer->Draw();
}