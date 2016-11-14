#pragma once
#include <Engine\GUI\GUIElement.h>
#include "..\Player\PlayerMessages.h"

namespace ENGINE_NAMESPACE
{
	class GUIOverheatBar : public GUIElement, public Subscriber<OverheatChangedMessage>
	{
	public:
		GUIOverheatBar(const char* aTexturePath, const Vector2f& aPosition, const Vector2f& aScale, const Vector2f& aSize, const bool aPrimary);
		~GUIOverheatBar();

		void Render() override;

		ReceiveResult Receive(const OverheatChangedMessage& aMessage) override;


	private:
		inline float GetCurrentFillAmount() const
		{
			return myCurrentOverheat / myMaxOverheat;
		}
		void SetFillAmount(const float aNewValue);

		Vector4f myTextureRect;
		float myCurrentOverheat;
		float myMaxOverheat;
		bool myIsPrimary;
	};
}

