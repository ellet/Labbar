#include "BaseGameObject.h"

#include <tga2d\sprite\sprite.h>

#include "..\..\RendererManager\RenderManager.h"

BaseGameObject::BaseGameObject()
	:myRenderPriority(0.f)
{

	SetPosition(Vector2f(0.f, 0.f));
	SetSize(Vector2f(1.f, 1.f));

	//Might be annoying.
	SetPivot(Vector2f(.5f, 1.f));

	myRotation = 0.f;

	SetColor(Vector4f(1.f, 1.f, 1.f, 1.f));
	myIsActive = true;
}
BaseGameObject::~BaseGameObject()
{
}

void BaseGameObject::Update(const float aDeltaTime)
{

	(aDeltaTime);

	myRenderPriority = myPosition.y;

}
void BaseGameObject::Draw() const
{
	if (myIsActive == true)
	{
		RenderManager::AddRenderCommand(RenderCommand(GetSprite(), myPosition, mySize, myPivot, myRotation, myColors, Vector4f(0.f, 0.f, 1.f, 1.f)), myRenderPriority);
	}	
}

void BaseGameObject::SetSprite(std::shared_ptr<DX2D::CSprite> aSprite)
{
	mySprite = aSprite;
}
void BaseGameObject::LoadSprite(const std::string &aPathToSprite)
{
	mySprite = std::make_shared<DX2D::CSprite>(DX2D::CSprite(aPathToSprite.c_str()));
}