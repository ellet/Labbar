#include "RenderCommand.h"

#include <tga2d\engine.h>
#include <tga2d\sprite\sprite.h>
#include <tga2d\sprite\sprite_batch.h>

#include "..\..\..\Utility\TGA2DConversions.h"

RenderCommand::RenderCommand()
{
	mySprite = nullptr;
	myRotation = 0;
}
RenderCommand::RenderCommand(DX2D::CSprite *aSprite, const Vector2f &aPosition, const Vector2f &aSize, const Vector2f &aPivot, const float aRotation, const Vector4f aColors, const Vector4f aRectangle)
{
	
	mySprite = aSprite;
	myPosition = aPosition;
	myPivot = aPivot;

	myRotation = aRotation;
	mySize = aSize;

	myColors = aColors;
	myRectangle = aRectangle;

}
RenderCommand::~RenderCommand()
{
}

DX2D::CSprite * RenderCommand::Render(const Vector2f &aParentPosition, const Vector2f &aParentSize)
{

	const DX2D::Vector2ui virtualScreenSize = DX2D::CEngine::GetInstance()->GetWindowSize();


	mySprite->SetPosition(DX2D::Vector2f((myPosition.x / virtualScreenSize.x), (myPosition.y / virtualScreenSize.y)));

	mySprite->SetSize(DX2D::Vector2f(mySize.x, mySize.y)); //* aParentSize.x, mySize.y * aParentSize.y));
	DX2D::Vector2f pivot;
	mySprite->SetPivot(pivot << myPivot);

	mySprite->SetRotation(myRotation);

	mySprite->SetColor(DX2D::CColor(myColors.x, myColors.y, myColors.z, myColors.w));
	mySprite->SetTextureRect(myRectangle.x, myRectangle.y, myRectangle.z, myRectangle.w);

	//mySprite->Render();
	return mySprite;

}
