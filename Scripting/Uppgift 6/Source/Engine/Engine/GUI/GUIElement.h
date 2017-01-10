#pragma once
#include <functional>
#include <bitset>
#include "Engine/Input/KeyboardKey.h"


namespace SB
{
	enum class VerticalAnchorPoint
	{
		eTop = 1 << 0,
		eCenter = 1 << 1,
		eBottom = 1 << 2
	};

	enum class HorizontalAnchorPoint
	{
		eLeft = 1 << 3,
		eCenter = 1 << 4,
		eRight = 1 << 5

	};
	
	enum class AnchorPoint
	{
		eTopLeft = 9,
		eCenterLeft = 10,
		eBottomLeft = 12,
		eTopCenter = 17,
		eCenterCenter = 18,
		eBottomCenter = 20,
		eTopRight = 33,
		eCenterRight = 34,
		eBottomRight = 36
	};

	class GUIElement 
	{
	friend class RootGUIElement;
	public:
		GUIElement();
		GUIElement(const Vector2f & aPosition, const Vector2f & aSize, bool aIsRoot = false);
		virtual ~GUIElement();
		virtual void Update(const SB::Time &aDeltaTime);
		virtual void Render(const GuiRenderTarget & aRenderTarget);	
		void AddChild(std::shared_ptr<GUIElement> aGUIElement);
		void RemoveChild(std::shared_ptr<GUIElement> aGUIElement);
		void SetPosition(const Vector2f & aPosition);
		void SetParent(GUIElement * aParent);
		void SetActive(bool aValue);
		void SetHoverSoundPath(const std::string & aPath);
		void SetClickSoundPath(const std::string & aPath);
		void BindHoverFunction(std::function<void()> aFunction);
		void BindKeyBindFunction(std::function<void()> aFunction, const KeyboardKey & aKeyToBind);
		inline GUIElement * GetParent() const;
		inline const Vector4f & GetAllowedSpace() const;
		inline const Vector2f & GetRenderSize() const;
		inline const Vector2f & GetOrigin() const;
		inline const Vector2f & GetSize() const;
		inline const Vector2f & GetPosition() const;
		virtual void SetAnchorPoint(const HorizontalAnchorPoint & aHorizontalPoint, const VerticalAnchorPoint & aVerticalPoint);
		virtual void SetName(const std::string & aName);
		inline void SetSize(const Vector2f & aSize);	
		virtual void SetPadding(const Vector4f & aPadding);
		inline const bool GetActive() const;	
		inline const bool GetIsRoot() const;
		inline const Vector4f & GetPadding() const;
		template<typename TGuiType>
		inline TGuiType* GetGUIElement(const std::string & aName);
	protected:
		virtual void ExitHoverFunction();
		virtual void HoverFunction();
		virtual bool LeftClickFunction();
		virtual void KeybindFunction(const KeyboardKey & aKey);
		void Resize(const int aWidth, const int aHeight);
		void GainedFocus();
		void ResetFocus();
		void ResetHover();
		void LostFocus();
		bool OnHover();
		GrowingArray<std::shared_ptr<GUIElement>> myChildren;
		std::function<void()> myHoverFunction;	
		std::unordered_map<KeyboardKey,std::function<void()>> myKeybindFunction;
		GUIElement * myParent;
		std::string myClickSoundPath;
		std::string myHoverSoundPath;
		std::string myName;
		Vector4f myAllowedBoundery;
		Vector4f myPadding;
		Vector2f myNormalizedPosition;
		Vector2f myAnchorOffset;
		Vector2f myRenderSize;
		Vector2f myPosition;
		Vector2f myScale;
		Vector2f mySize;
		Vector2f myOrigin;
		VerticalAnchorPoint myVerticalAnchorPoint;
		HorizontalAnchorPoint myHorizontalAnchorPoint;
		bool myHasFocus;
		bool myIsActive;
		bool myMouseOver;
		bool myGainedFocus;
		bool myGainedHover;
		bool myContentChanged;
		bool myIsRoot;	
		static Vector2f ourMousePosition;
	private:
		void AdjustBounderies(GUIElement & aGUIElement);
		void AdjustPositions(GUIElement & aGUIElement, const int aWidth, const int aHeight);
		void SetAllowedSpace(const Vector4f & aAllowedSize);
		void SetAnchorOffset(GUIElement & aGUIElement);
		void AlignChild(GUIElement & aGUIElement, const int aWidth, const int aHeight);
		template<typename TGuiType>
		TGuiType* InternGetGUIElement(const std::string & aName);	
	};

	const Vector2f & GUIElement::GetPosition() const
	{
		return myPosition;
	}
	template<typename TGuiType>
	TGuiType* GUIElement::GetGUIElement(const std::string & aName)
	{
		if (InternGetGUIElement<TGuiType>(aName) == nullptr)
		{
			Error("GUIElement: " + aName + " doesn't exist!")
		}
		else
		{
			return InternGetGUIElement<TGuiType>(aName);
		}
	}
	template<typename TGuiType>
	TGuiType* GUIElement::InternGetGUIElement(const std::string & aName)
	{
		if (myName == aName)
		{
			return static_cast<TGuiType*>(this);
		}
		else
		{
			TGuiType* tempGUI = nullptr;
			for (unsigned short i = 0; i < myChildren.Size(); i++)
			{
				tempGUI = myChildren[i]->InternGetGUIElement<TGuiType>(aName);
				if (tempGUI != nullptr)
				{
					break;
				}
			}
			return tempGUI;
		}
	}

	GUIElement * GUIElement::GetParent() const
	{
		return myParent;
	}

	const bool GUIElement::GetActive() const
	{
		return myIsActive;
	}

	const Vector4f & GUIElement::GetAllowedSpace() const
	{
		return myAllowedBoundery;
	}

	const Vector2f & GUIElement::GetRenderSize() const
	{
		return myRenderSize;
	}

	const Vector2f & GUIElement::GetOrigin() const
	{
		return myOrigin;
	}

	const bool GUIElement::GetIsRoot() const
	{
		return myIsRoot;
	}

	const Vector2f & GUIElement::GetSize() const
	{
		return mySize;
	}

	const Vector4f & GUIElement::GetPadding() const
	{
		return myPadding;
	}

	void GUIElement::SetSize(const Vector2f & aSize)
	{
		mySize = aSize;
	}
}

