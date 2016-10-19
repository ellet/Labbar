#pragma once
#include <functional>
#include "Engine/Sprite/Sprite.h"
#include <bitset>
class Sprite;

namespace ENGINE_NAMESPACE
{
	class Text;
	class GUIElement 
	{
	friend class RootGUIElement;
	public:
		GUIElement();
		GUIElement(const Vector4f & aBorderPositions);
		GUIElement(const char * aTexturePath, const Vector2f& aPosition = Vector2f::Zero, const Vector2f& aScale = Vector2f::One, const Vector2f& aSize = Vector2f::Zero);
		virtual ~GUIElement();
		void AddChild(std::shared_ptr<GUIElement> aGUIElement);
		virtual void Update();
		virtual void Render();
		void SetName(const std::string & aName);
		void SetText(std::shared_ptr<Text> aTextPtr);
		GUIElement* GetGUIElement(const std::string & aName);
		inline void SetActive(bool aValue);
		void BindFunction(std::function<void()> aFunctionToCall);
		void AlignChildren();
		void SetSprite(const char * aTexturePath);
	protected:
		void MyHoverFunction();
		void GainedFocus();
		void LostFocus();
		void ResetFocus();
		bool OnHover();
		void SetParent(GUIElement * aParent);
		void LeftClickFunction();
		std::string myName;
		Vector4f myBorderPositions;
		GrowingArray<std::shared_ptr<GUIElement>> myChildren;
		std::function<void()> myFunction;
		std::shared_ptr<Sprite> mySprite;
		std::shared_ptr<Text> myText;
		GUIElement * myParent;
		bool myHasFocus;
		bool myIsActive;
		bool myMouseOver;
		bool myGainedFocus;

		static Vector2f ourMousePosition;
	private:
		GUIElement* InternGetGUIElement(const std::string & aName);

	};

	void GUIElement::SetActive(bool aValue)
	{
		myIsActive = aValue;
		if (myParent != nullptr)
		{
			myParent->SetActive(aValue);
		}
	}
}

