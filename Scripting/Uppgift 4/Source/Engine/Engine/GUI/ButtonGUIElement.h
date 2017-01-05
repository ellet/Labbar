#pragma once
#include "Engine\GUI\GUIElement.h"


namespace SB
{
	class SpriteGUIElement;

	class ButtonGUIElement : public GUIElement
	{
	public:
		ButtonGUIElement();	
		ButtonGUIElement(const char * aTexturePath, const Vector2f& aPosition = Vector2f::Zero, const bool aIsRoot = false, const Vector2f& aScale = Vector2f::One, const Vector2f& aSize = Vector2f::Zero);
		~ButtonGUIElement();

		virtual void Update(const SB::Time &aDeltaTime) override;
		virtual void Render(const GuiRenderTarget & aRenderTarget) override;
		void BindClickFunction(std::function<void()> aFunction);
		void SetIsHoverActivated(bool aValue);
		void AddButtonChild();

		virtual void SetName(const std::string & aName) override;


		virtual void SetAnchorPoint(const HorizontalAnchorPoint & aHorizontalPoint, const VerticalAnchorPoint & aVerticalPoint) override;

	protected:
		virtual bool LeftClickFunction() override;
	private:
		std::shared_ptr<SpriteGUIElement> mySpriteGUI;
		std::function<void()> myFunction;


	};
}
