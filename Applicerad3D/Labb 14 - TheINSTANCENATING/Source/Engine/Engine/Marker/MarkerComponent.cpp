#include "stdafx.h"
#include "MarkerComponent.h"
#include "..\Sprite\Sprite.h"
#include "Engine/GUI/GUIMarker.h"
#include "..\Scene\Scene.h"
#include "..\Camera\Camera.h"
#include "Engine/GUI/GUIElement.h"
#include "Engine/GUI/RootGUIElement.h"
namespace ENGINE_NAMESPACE
{
	MarkerComponent::MarkerComponent()
	{
	}


	MarkerComponent::~MarkerComponent()
	{
		myObject->GetScene().GetGUI()->GetGUIElement("MarkerRadar")->RemoveChild(myGUIMarker);
		myGUIMarker = nullptr;
	}

	void MarkerComponent::Update(const Time & aDeltaTime)
	{
		float signedDirection = myObject->GetScene().GetCamera().GetOrientation().GetForward().Dot(myObject->GetWorldPosition() - myObject->GetScene().GetCamera().GetTransformation().GetPosition());

		SB::Vector2f hej = GetScreenPosition(myObject->GetWorldPosition()) - Vector2f(640.f, 320.f);

		myGUIMarker->SetTargetPosition(GetScreenPosition(myObject->GetWorldPosition()));
		myGUIMarker->SetDirection(signedDirection);
		myGUIMarker->Align();
	}

	void MarkerComponent::ToJson() const
	{
		SB::JsonSerializer &serializer = SB::Engine::GetJsonSerializer();
		serializer.WriteObject("properties");
		serializer.StepOut();
		serializer.WriteNode("type", "MarkerComponent");
	}

	void MarkerComponent::Render() const
	{
	}

	void MarkerComponent::Initialize()
	{
		myGUIMarker = std::make_shared<GUIMarker>("Assets/Gui/Markers/enemy.dds", Vector2f::Zero);
		myGUIMarker->SetActive(true);
		myObject->GetScene().GetGUI()->GetGUIElement("MarkerRadar")->AddChild(myGUIMarker);
		myGUIMarker->SetOrigin(myGUIMarker->GetSprite().GetTextureRectSize() / 2.f);
		myGUIMarker->CenterMe();
	}

	void MarkerComponent::OnRemoved()
	{
		myGUIMarker->SetActive(false);
	}

	const Vector2f MarkerComponent::GetScreenPosition(const Vector3f & aPosition) const
	{



		Vector2f pos = myObject->GetScene().GetCamera().WorldToScreen(aPosition);
		pos += Vector2f::One;
		pos /= 2.f;
		pos.y = 1.f - pos.y;
		pos *= Vector2f(1280.f, 720.f);		
		return pos;	
	}


}