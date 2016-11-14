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
		void RemoveChild(std::shared_ptr<GUIElement> aGUIElement);
		virtual void Update();
		virtual void Render();
		void SetName(const std::string & aName);
		void SetText(std::shared_ptr<Text> aTextPtr);
		void SetFunctionName(const std::string & aName);
		void ExitHoverFunction();
		GUIElement* GetGUIElement(const std::string & aName);
		void SetIsHoverActivated(bool aValue);
		const Sprite & GetSprite() const;
		const bool GetActive() const;
		void SetActive(bool aValue);
		void SetRotation(const float aRotation);
		void SetPosition(const Vector2f & aPosition);
		const Vector2f GetPosition() const;
		float GetRotation() const;
		//void BindFunction(std::function<void()> aFunctionToCall);
		void AlignChildren();
		void SetSprite(const char * aTexturePath);
		const std::string & GetFunctionName() const;
		void BindFunction(std::unordered_map<std::string, std::function<void()>> & aFunctionMap, const std::string & aFunctionName, bool aBindHoverFunction = false);
		const Vector4f & GetBorderPosition() const;
		GUIElement * GetParent() const;
	protected:
		void HoverFunction();
		void GainedFocus();
		void LostFocus();
		void ResetFocus();
		void ResetHover();
		bool OnHover();
		void SetParent(GUIElement * aParent);
		void LeftClickFunction();
		std::string myName;
		std::string myFunctionName;
		std::string myHoverSprite;
		std::string mySpritePath;
		Vector4f myBorderPositions;
		GrowingArray<std::shared_ptr<GUIElement>> myChildren;
		std::function<void()> myFunction;
		std::function<void()> myHoverFunction;
		std::shared_ptr<Sprite> mySprite;
		std::shared_ptr<Text> myText;
		GUIElement * myParent;
		bool myHasFocus;
		bool myIsActive;
		bool myMouseOver;
		bool myGainedFocus;
		bool myGainedHover;
		bool myIsHoverSpriteActivated;

		static Vector2f ourMousePosition;
	private:
		GUIElement* InternGetGUIElement(const std::string & aName);

	};

	inline const std::string & GUIElement::GetFunctionName() const
	{
		return myFunctionName;
	}


}

