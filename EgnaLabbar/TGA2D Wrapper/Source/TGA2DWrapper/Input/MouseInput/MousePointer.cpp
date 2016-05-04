#include "MousePointer.h"
#include <tga2d/sprite/sprite.h>
#include "MouseInput.h"
#include "../../../Game/Inventory/Inventory.h"
#include "../../../Game/Object/Object.h"
#include "../../RendererManager/RenderManager.h"

namespace
{
	class CSprite;
}

MousePointer::MousePointer()
{
	myRenderPriority = 2000.f;
	myNormalSprite = std::shared_ptr<DX2D::CSprite>(new DX2D::CSprite("Sprites/MousePointers/NormalMouse.dds"));
	myMouseOverSprite = std::shared_ptr<DX2D::CSprite>(new DX2D::CSprite("Sprites/MousePointers/MouseOver.dds"));
	myMouseClickOnSprite = std::shared_ptr<DX2D::CSprite>(new DX2D::CSprite("Sprites/MousePointers/ClickOn.dds"));
	myMouseItemHeld = std::shared_ptr<DX2D::CSprite>(new DX2D::CSprite("Sprites/MousePointers/ItemHeld.dds"));
	//LoadSprite("Sprites/MousePointers/TestMouse.dds");

	myActiveState = enumMouseStates::eMovePlayerMode;

	SetSprite(myNormalSprite);

	SetPivot(Vector2f::Zero);

	myStateIsLocked = false;
}


MousePointer::~MousePointer()
{
	myMouseActions.DeleteAll();
}


void MousePointer::TriggerClick()
{
	myStateIsLocked = true;

	if (myActiveState != enumMouseStates::eNeutralMode)
	{
		myMouseActions[static_cast<unsigned short>(myActiveState)]->DoOnClick();
	}
}

void MousePointer::TriggerHeld()
{
	if (myActiveState != enumMouseStates::eNeutralMode)
	{
		myMouseActions[static_cast<unsigned short>(myActiveState)]->DoOnHeld();
	}
}

void MousePointer::TriggerRelease()
{
	myStateIsLocked = false;

	if (myActiveState != enumMouseStates::eNeutralMode)
	{
		myMouseActions[static_cast<unsigned short>(myActiveState)]->DoOnRelease();
	}
}

#include "MouseAction/ClickOnObject.h"
#include "MouseAction/SetPlayerGotoOnClick.h"
#include "MouseAction/ActivateActionWheel.h"
#include "MouseAction/ClickForNextText.h"
#include "MouseAction/UseHeldObjectOnObject.h"

void MousePointer::VariableSetup()
{
	myMouseActions.Init(static_cast<unsigned short>(enumMouseStates::enumlength));
	myMouseActions.Resize(static_cast<unsigned short>(enumMouseStates::enumlength));

	myMouseActions[static_cast<unsigned short>(enumMouseStates::eClickOnStuffMode)] = new ClickOnObject();
	myMouseActions[static_cast<unsigned short>(enumMouseStates::eMovePlayerMode)] = new SetPlayerGotoOnClick();
	myMouseActions[static_cast<unsigned short>(enumMouseStates::eActivateWheel)] = new ActivateActionWheel();
	myMouseActions[static_cast<unsigned short>(enumMouseStates::eTalkMode)] = new ClickForNextText();
	myMouseActions[static_cast<unsigned short>(enumMouseStates::eHoldingItem)] = new UseHeldObjectOnObject();

	myActiveState = enumMouseStates::eMovePlayerMode;
}

void MousePointer::ChangeSprite()
{
	switch (myActiveState)
	{
	case enumMouseStates::eHoldingItem:
		SetSprite(myMouseItemHeld);
		break;
	case enumMouseStates::eMovePlayerMode:
	case enumMouseStates::eNeutralMode:
		SetSprite(myNormalSprite);
		break;
	case enumMouseStates::eClickOnStuffMode:
	case enumMouseStates::eTalkMode:
		SetSprite(myMouseClickOnSprite);
		break;
	case enumMouseStates::eActivateWheel:
		SetSprite(myMouseOverSprite);
		break;
	}
}

void MousePointer::Draw() const
{
	if (myActiveState == enumMouseStates::eHoldingItem)
	{
		DX2D::CSprite * tempPointer = MouseInput::GetInventoryPointer().GetSelectedObject()->GetSprite();
		RenderManager::AddRenderCommand(RenderCommand(tempPointer, GetPosition(), GetSize(), Vector2f(0.5f, 0.5f), GetRotation(), GetColor(), Vector4f(0.f, 0.f, 1.f, 1.f)), GetRenderPriority());
	}
	BaseGameObject::Draw();
}