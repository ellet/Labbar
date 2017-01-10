#include "stdafx.h"
#include "GUIMarker.h"
#include "Engine/Text/Text.h"

namespace SB
{
	GUIMarker::GUIMarker(const char * aTexturePath, const Vector2f& aPosition) : SpriteGUIElement(aTexturePath,aPosition)
	{
		myTargetPosition = Vector2f::Zero;
		mySignedDirection = 0.f;
		myIsInside = false;
		myIsObjectiveMarker = false;
	}

	GUIMarker::~GUIMarker()
	{

	}

	void GUIMarker::Align()
	{
		
		Vector4f radarBorder = GetParent()->GetAllowedSpace();
		Vector2f centerPosition = Vector2f(radarBorder.x + (radarBorder.z - radarBorder.x) / 2.f, radarBorder.y + (radarBorder.w - radarBorder.y) / 2.f);
		Vector2f screenTargetPosition = myTargetPosition - centerPosition;
		float radius = (radarBorder.z - radarBorder.x) / 2.f;
		if (mySignedDirection < 0.f)
		{
			SetPosition(Vector2f(screenTargetPosition.GetNormalized().x * -radius + centerPosition.x, screenTargetPosition.GetNormalized().y  * -radius + centerPosition.y));
		}
		else
		{
			if ((screenTargetPosition).Length() > radius)
			{
				SetPosition(Vector2f(screenTargetPosition.GetNormalized().x * radius + centerPosition.x, screenTargetPosition.GetNormalized().y  * radius + centerPosition.y));
			}
			else
			{
				SetPosition(Vector2f(screenTargetPosition.x + centerPosition.x, screenTargetPosition.y + centerPosition.y));
			}
		}

		
	}

	void GUIMarker::CenterMe()
	{
		Vector4f radarBorder = GetParent()->GetAllowedSpace();
		SetPosition(Vector2f(radarBorder.x + (radarBorder.z - radarBorder.x) / 2.f, radarBorder.y + (radarBorder.w - radarBorder.y) / 2.f));
	}

	const Vector2f & GUIMarker::GetTargetPosition() const
	{
		return myTargetPosition;
	}

	void GUIMarker::SetTargetPosition(const Vector2f & aPosition)
	{
		myTargetPosition = aPosition;
	}

	void GUIMarker::SetOrigin(const Vector2f & aOrigin)
	{
		mySprite->SetOrigin(aOrigin);
	}

	float GUIMarker::GetDirection() const
	{
		return mySignedDirection;
	}

	bool GUIMarker::GetIsInside() const
	{
		return myIsInside;
	}

	void GUIMarker::SetDirection(const float aDirection)
	{
		mySignedDirection = aDirection;
	}

	void GUIMarker::SetIsInside(const bool aValue)
	{
		myIsInside = aValue;
	}

	void GUIMarker::SpecialUpdate()
	{
		Vector4f radarBorder = GetParent()->GetAllowedSpace();
		Vector2f centerPosition = Vector2f(radarBorder.x + (radarBorder.z - radarBorder.x) / 2.f, radarBorder.y + (radarBorder.w - radarBorder.y) / 2.f);
		Vector2f screenTargetPosition = myTargetPosition - centerPosition;
		float radius = (radarBorder.w - radarBorder.x);
		if (mySignedDirection < 0.f)
		{
			myIsInside = false;
		}
		else
		{
			if ((screenTargetPosition).Length() > radius)
			{
				myIsInside = false;
				SetOrigin(Vector2f(0.f, 90.f));
				SetPosition(Vector2f::Zero);
				CenterMe();
			}
			else
			{
				myIsInside = true;
				SetOrigin(Vector2f::Zero);
				SetPosition(GetParent()->GetPosition());
			}
		}
	}

	void GUIMarker::SetColor(const Vector4f &aColor)
	{
		if (mySprite != nullptr)
		{
			mySprite->SetColor(aColor);
		}
	}

}