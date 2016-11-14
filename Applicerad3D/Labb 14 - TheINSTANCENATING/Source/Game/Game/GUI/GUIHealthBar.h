#pragma once
#include <Engine\GUI\GUIElement.h>
#include "..\Player\PlayerMessages.h"

namespace ENGINE_NAMESPACE
{
	class GUIHealthBar : public GUIElement, public Subscriber<PlayerHealthChangedMessage>
	{
	public:
		GUIHealthBar(const char * aTexturePath, const Vector2f& aPosition, const Vector2f& aScale, const Vector2f& aSize = Vector2f::Zero);
		~GUIHealthBar();

		virtual void Update() override;
		virtual void Render() override;

		ReceiveResult Receive(const PlayerHealthChangedMessage & aMessage) override;

	private:
		inline float GetCurrentFillAmount() const
		{
			return myPlayerCurrentHealth / myPlayerMaxHealth;
		}
		void SetFillAmount(const float aNewValue);

		Vector4f myTextureRect;
		float myPlayerMaxHealth;
		float myPlayerCurrentHealth;
	};
}

