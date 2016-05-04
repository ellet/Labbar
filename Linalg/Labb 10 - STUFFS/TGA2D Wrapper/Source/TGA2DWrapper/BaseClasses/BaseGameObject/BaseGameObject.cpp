#include "BaseGameObject.h"

#include <tga2d\sprite\sprite.h>

#include "..\..\RendererManager\RenderManager.h"

#include <DLDebug/DL_Debug.h>



BaseGameObject::BaseGameObject()
{

	SetPosition(Vector2f(0.f, 0.f));
	SetSize(Vector2f(1.f, 1.f));

	//Might be annoying.
	SetPivot(Vector2f(.5f, 0.5f));

	myRotation = 0.f;

	SetColor(Vector4f(1.f, 1.f, 1.f, 1.f));

	myCollisionData = nullptr;
}
BaseGameObject::~BaseGameObject()
{
}

void BaseGameObject::Update(const float aDeltaTime)
{
	(aDeltaTime);
}
void BaseGameObject::Draw() const
{
	RenderManager::AddRenderCommand(RenderCommand(GetSprite(), myPosition, mySize, myPivot, myRotation, myColors, Vector4f(0.f, 0.f, 1.f, 1.f)));
}

void BaseGameObject::OnCollision(const CollisionData & aCollisionData)
{
	(aCollisionData);
	bool NEJYLVA = false;
	DL_ASSERT(NEJYLVA, "CANT HANDLE THAT COLLISION");
}

void BaseGameObject::SetSprite(DX2D::CSprite *aSprite)
{
	mySprite = std::shared_ptr<DX2D::CSprite>(aSprite);
}

void BaseGameObject::LoadSprite(const std::string &aPathToSprite)
{
	mySprite = std::shared_ptr<DX2D::CSprite>(new DX2D::CSprite(aPathToSprite.c_str()));	
}