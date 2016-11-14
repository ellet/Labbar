#pragma once
#include "Engine\GUI\GUIElement.h"

namespace ENGINE_NAMESPACE
{
	class GUIMarker : public GUIElement
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

	private:
		Vector2f myTargetPosition;
		float mySignedDirection;
		bool myIsInside;

	};
}
