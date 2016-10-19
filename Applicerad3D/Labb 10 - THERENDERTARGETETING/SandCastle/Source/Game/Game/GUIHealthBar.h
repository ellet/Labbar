#pragma once
#include <Engine\GUI\GUIElement.h>
#include "Player\PlayerMessages.h"

namespace ENGINE_NAMESPACE
{
	class GUIHealthBar : public GUIElement, public Subscriber<PlayerHealthChangedMessage>
	{
	public:
		GUIHealthBar(const char * aTexturePath, const Vector2f& aPosition, const Vector2f& aScale, const Vector2f& aSize = Vector2f::Zero);
		~GUIHealthBar();

		ReceiveResult Receive(const PlayerHealthChangedMessage & aMessage) override;


		virtual void Update() override;


		virtual void Render() override;
	private:
		Vector4f myTextureRect;
		float myPlayerMaxHealth;
		float myPlayerCurrentHealth;
	};
}

