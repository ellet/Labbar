#pragma once
#include "Engine\GUI\SpriteGUIElement.h"

namespace SB
{
	class GUIMarker : public SpriteGUIElement
	{
	public:
		GUIMarker(const char * aTexturePath, const Vector2f& aPosition);
		~GUIMarker();

		void Align();
		void CenterMe();
		const Vector2f & GetTargetPosition() const;
		float GetDirection() const;
		bool GetIsInside() const;
		void SetTargetPosition(const Vector2f & aPosition);
		void SetOrigin(const Vector2f & aOrigin);
		void SetDirection(const float aDirection);
		void SetIsInside(const bool aValue);
		void SpecialUpdate();
		void SetColor(const Vector4f &aColor);
	private:
		Vector2f myTargetPosition;
		float mySignedDirection;
		bool myIsInside;
		bool myIsObjectiveMarker;

	};
}
