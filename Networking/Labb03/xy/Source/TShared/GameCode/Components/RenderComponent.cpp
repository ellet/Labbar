#include "stdafx.h"
#include "RenderComponent.h"
#include "tga2d\sprite\sprite.h"
#include <GameCode\GameObject\GameObject.h>


unsigned int RenderComponent::myID = EComponentIds::EComponentIds_CIRenderComponent;

RenderComponent::RenderComponent()
{
}


RenderComponent::~RenderComponent()
{
}

void RenderComponent::LoadSprite(const std::string & aFilePath)
{
	mySprite = new DX2D::CSprite(aFilePath.c_str());
}

void RenderComponent::Render()
{
	mySprite->SetPosition(myOwner->myPosition);
	mySprite->Render();
}

const DX2D::Vector2f & RenderComponent::GetSize() const
{
	return mySprite->GetSize();
}


