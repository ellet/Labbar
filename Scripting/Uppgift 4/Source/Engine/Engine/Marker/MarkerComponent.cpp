#include "stdafx.h"
#include "MarkerComponent.h"
#include "..\Sprite\Sprite.h"
#include "Engine/GUI/GUIMarker.h"
#include "..\Scene\Scene.h"
#include "..\Camera\Camera.h"
#include "Engine/GUI/GUIElement.h"
#include "Engine/GUI/RootGUIElement.h"
#include "Engine/Text/Text.h"


namespace SB
{
	MarkerComponent::MarkerComponent()
	{
		myGUIMarker = std::make_shared<GUIMarker>("Assets/Gui/Markers/enemy.dds", Vector2f::Zero);
		myGUIMarker->SetActive(true);
		myGUIMarker->SetIsHoverActivated(false);
		SetColor(Vector4f(1.f, 0.f, 0.f, 1.f));
		myIsObjectiveMarker = false;

	}


	MarkerComponent::~MarkerComponent()
	{
		myObject->GetScene().GetGUI()->GetGUIElement<SB::GUIElement>("MarkerRadar")->RemoveChild(myGUIMarker);
		myGUIMarker = nullptr;
	}

	void MarkerComponent::EndUpdate(const Time & aDeltaTime)
	{
		float signedDirection = myObject->GetScene().GetCamera().GetOrientation().GetForward().Dot(myObject->GetWorldPosition() - myObject->GetScene().GetCamera().GetTransformation().GetPosition());
		
		myGUIMarker->SetTargetPosition(GetScreenPosition(myObject->GetWorldPosition()));
		myGUIMarker->SetDirection(signedDirection);
		myGUIMarker->Align();
	}

	void MarkerComponent::ToJson(JsonSerializer &aSerializer) const
	{
		SB::JsonSerializer &serializer = aSerializer;
		serializer.WriteObject("properties");
		serializer.StepOut();
		serializer.WriteNode("type", "MarkerComponent");
	}

	void MarkerComponent::Initialize()
	{
		myObject->GetScene().GetGUI()->GetGUIElement<SB::GUIElement>("MarkerRadar")->AddChild(myGUIMarker);
		myGUIMarker->SetOrigin(myGUIMarker->GetSprite().GetTextureRectSize() / 2.f);
		myGUIMarker->CenterMe();
	}


	void MarkerComponent::SetColor(const Vector4f &aColor)
	{
		myGUIMarker->SetColor(aColor);
	}

	void MarkerComponent::OnRemoved()
	{
		myGUIMarker->SetActive(false);
	}

	void MarkerComponent::SetActive(bool aValue)
	{
		myGUIMarker->SetActive(aValue);
	}

	bool MarkerComponent::GetActive() const
	{
		return myGUIMarker->GetActive();
	}

	void MarkerComponent::SetIsObjective(bool aValue)
	{
		myIsObjectiveMarker = aValue;
	}

	void MarkerComponent::SetSprite(const ObjectiveType & aObjectiveType)
	{
		switch (aObjectiveType)
		{
		case ObjectiveType::AttackObjective:
			myGUIMarker->SetSprite("Assets/Gui/Markers/objectiveEnemyMarker.dds");
			myGUIMarker->SetColor(Vector4f(1.f, 0.3f, 0.f, 1.f));
			break;
		case ObjectiveType::BossObjective:
			myGUIMarker->SetSprite("Assets/Gui/Markers/bossMarker.dds");
			myGUIMarker->SetColor(Vector4f(1.f, 0.f, 0.f, 1.f));
			break;
		case ObjectiveType::DefendObjective:
			myGUIMarker->SetSprite("Assets/Gui/Markers/defendMarker.dds");
			break;
		}
	}

	const Vector2f MarkerComponent::GetScreenPosition(const Vector3f & aPosition) const
	{
		Vector2f pos = myObject->GetScene().GetCamera().WorldToScreen(aPosition);
		pos += Vector2f::One;
		pos /= 2.f;
		pos.y = 1.f - pos.y;
		pos *= Vector2f(myGUIMarker->GetRenderSize().x, myGUIMarker->GetRenderSize().y);		
		return pos;	
	}

}