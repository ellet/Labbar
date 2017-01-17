#include "stdafx.h"
#include "GUIElement.h"
#include "..\Text\Text.h"
#include "Engine/GenericEngineMessages.h"
#include "Engine/Texture/GuiRenderTarget.h"

namespace SB
{
	Vector2f GUIElement::ourMousePosition = Vector2f(0.f, 0.f);

	GUIElement::GUIElement() : GUIElement(Vector2f(0.0f, 0.0f), Vector2f(100.f, 100.f))
	{
	}

	GUIElement::GUIElement(const Vector2f & aPosition, const Vector2f & aSize, const bool aIsRoot)
	{
		myHasFocus = true;
		myGainedFocus = false;
		myContentChanged = false;
		myGainedHover = false;
		myMouseOver = false;
		myIsActive = false;	
		myParent = nullptr;
		myHoverFunction = nullptr;
		myPosition = aPosition;
		mySize = aSize;
		myName = "";
		myHorizontalAnchorPoint = HorizontalAnchorPoint::eLeft;
		myVerticalAnchorPoint = VerticalAnchorPoint::eTop;
		myRenderSize = Vector2f(1080.f * (Engine::GetRenderer().GetRenderTargetResolution().x / Engine::GetRenderer().GetRenderTargetResolution().y), 1080.f);
		myOrigin = Vector2f::Zero;
		myIsRoot = aIsRoot;
		myAnchorOffset = Vector2f::Zero;
		myNormalizedPosition.x = aPosition.x;
		myNormalizedPosition.y = aPosition.y;
		myClickSoundPath = "";
		myHoverSoundPath = "";
		myScale = Vector2f::One;
		if (mySize == Vector2f(-1, -1))
		{
			mySize = Vector2f(1080.f * (Engine::GetRenderer().GetRenderTargetResolution().x / Engine::GetRenderer().GetRenderTargetResolution().y), 1080.f);
		}
		myAllowedBoundery = Vector4f(myPosition.x, myPosition.y, myPosition.x + mySize.x, myPosition.y + mySize.y);
	}

	GUIElement::~GUIElement()
	{
	}

	void GUIElement::Update(const SB::Time &aDeltaTime)
	{
		if (myContentChanged == true)
		{
			myContentChanged = false;
		}
		for (unsigned short i = 0; i < myChildren.Size(); i++)
		{
			if (myChildren[i]->myIsActive == true)
			{
				myChildren[i]->Update(aDeltaTime);
			}
		}
		if (myParent == nullptr)
		{
			OnHover();
		}
		if (myGainedFocus == true)
		{
			GainedFocus();
		}
	}

	void GUIElement::Render(const GuiRenderTarget & aRenderTarget)
	{
		if (myIsActive == true)
		{
			for (unsigned short i = 0; i < myChildren.Size(); i++)
			{
				if (myChildren[i]->myIsActive == true)
				{
					myChildren[i]->Render(aRenderTarget);
				}
			}
		}
	}

	void GUIElement::AddChild(std::shared_ptr<GUIElement> aGUIElement)
	{
		aGUIElement->SetParent(this);
		aGUIElement->myHasFocus = false;
		AlignChild(*aGUIElement, static_cast<int>(Engine::GetRenderer().GetRenderTargetResolution().x), static_cast<int>(Engine::GetRenderer().GetRenderTargetResolution().y));
		myChildren.Add(aGUIElement);
	}

	void GUIElement::RemoveChild(std::shared_ptr<GUIElement> aGUIElement)
	{
		unsigned short resultIndex = myChildren.Find(aGUIElement);
		if (resultIndex != myChildren.FoundNone)
		{
			myChildren.RemoveAtIndex(resultIndex);
		}
	}

	void GUIElement::SetPosition(const Vector2f & aPosition)
	{
		myPosition.x = aPosition.x;
		myPosition.y = aPosition.y;
		myPosition += myAnchorOffset;

		if (myHorizontalAnchorPoint == HorizontalAnchorPoint::eRight)
		{
			myPosition.x -= mySize.x;
		}
		if (myVerticalAnchorPoint == VerticalAnchorPoint::eBottom)
		{
			myPosition.y -= mySize.y;
		}
		if (myHorizontalAnchorPoint == HorizontalAnchorPoint::eCenter)
		{
			myPosition.x -= mySize.x / 2.f;
		}
		if (myVerticalAnchorPoint == VerticalAnchorPoint::eCenter)
		{
			myPosition.y -= mySize.y / 2.f;
		}

		if (myPosition.x < myAllowedBoundery.x)
		{
			myPosition.x = myAllowedBoundery.x;
		}
		else if (myPosition.x + mySize.x > myAllowedBoundery.z)
		{
			myPosition.x = myAllowedBoundery.z - mySize.x;
		}

		if (myPosition.y < myAllowedBoundery.y)
		{
			myPosition.y = myAllowedBoundery.y;
		}
		else if (myPosition.y + mySize.y > myAllowedBoundery.w)
		{
			myPosition.y = myAllowedBoundery.w - mySize.y;
		}
	}

	void GUIElement::SetParent(GUIElement * aParent)
	{
		myParent = aParent;
	}

	void GUIElement::SetActive(bool aValue)
	{
		myIsActive = aValue;
		if (aValue == true)
		{
			if (myParent != nullptr)
			{
				myParent->SetActive(aValue);
			}
		}
	}

	void GUIElement::SetHoverSoundPath(const std::string & aPath)
	{
		myHoverSoundPath = aPath;
	}

	void GUIElement::SetClickSoundPath(const std::string & aPath)
	{
		myClickSoundPath = aPath;
	}

	void GUIElement::BindHoverFunction(std::function<void()> aFunction)
	{
		myHoverFunction = aFunction;
	}

	void GUIElement::BindKeyBindFunction(std::function<void()> aFunction, const KeyboardKey & aKeyToBind)
	{
		myKeybindFunction[aKeyToBind] = aFunction;
	}

	void GUIElement::SetPadding(const Vector4f & aPadding)
	{
		myPadding = aPadding;
	}

	void GUIElement::SetAnchorPoint(const HorizontalAnchorPoint & aHorizontalPoint, const VerticalAnchorPoint & aVerticalPoint)
	{
		myHorizontalAnchorPoint = aHorizontalPoint;
		myVerticalAnchorPoint = aVerticalPoint;
	}

	void GUIElement::SetName(const std::string & aName)
	{
		myName = aName;
	}

	//PROTECTED FUNCTIONS

	void GUIElement::ExitHoverFunction()
	{
		//myGainedHover = false;
	}

	void GUIElement::HoverFunction()
	{
		if (myHoverFunction != nullptr)
		{
			myHoverFunction();
		}
	}

	bool GUIElement::LeftClickFunction()
	{
		for (unsigned short i = 0; i < myChildren.Size(); i++)
		{
			if (myChildren[i]->myMouseOver == true)
			{
				myChildren[i]->LeftClickFunction();
				return false;
			}
		}
		if (myHasFocus == false)
		{
			if (myParent != nullptr)
			{
				myParent->ResetFocus();
			}
			else
			{
				ResetFocus();
			}
			myHasFocus = true;
			myGainedFocus = true;
		}
		else
		{
			if (myParent != nullptr)
			{
				myParent->ResetFocus();
			}
			else
			{
				ResetFocus();
			}
			myHasFocus = true;
		}
		return true;
	}

	void GUIElement::KeybindFunction(const KeyboardKey & aKey)
	{
		if (myIsActive != false)
		{
			for (unsigned short i = 0; i < myChildren.Size(); i++)
			{
				if (myChildren[i]->myKeybindFunction.find(aKey) != myChildren[i]->myKeybindFunction.end())
				{
					if (myChildren[i]->myKeybindFunction[aKey] != nullptr)
					{
						myChildren[i]->KeybindFunction(aKey);
						return;
					}
				}
			}
			if (myKeybindFunction.find(aKey) != myKeybindFunction.end())
			{
				if (myKeybindFunction[aKey] != nullptr)
				{
					myKeybindFunction[aKey]();
				}
			}
		}
	}

	void GUIElement::Resize(const int aWidth, const int aHeight)
	{
		myRenderSize = Vector2f(1080.f * (static_cast<float>(aWidth) / static_cast<float>(aHeight)), 1080.f);
		if (GetIsRoot() == true)
		{
			mySize = myRenderSize;
			myPosition = Vector2f::Zero;
		}
		for (unsigned short i = 0; i < myChildren.Size(); i++)
		{	
			AlignChild(*myChildren[i], aWidth, aHeight);
		}
		for (unsigned short i = 0; i < myChildren.Size(); i++)
		{
			myChildren[i]->Resize(aWidth, aHeight);
		}
	}

	void GUIElement::GainedFocus()
	{
		myGainedFocus = false;
#ifndef Publish
		std::cout << "Gained Focus" << std::endl;
#endif
	}

	void GUIElement::ResetFocus()
	{
		for (unsigned short i = 0; i < myChildren.Size(); i++)
		{
			myChildren[i]->ResetFocus();
		}
		myHasFocus = false;
	}

	void GUIElement::ResetHover()
	{
		for (unsigned short i = 0; i < myChildren.Size(); i++)
		{
			myChildren[i]->ResetHover();
		}
		myGainedHover = false;
	}

	void GUIElement::LostFocus()
	{

	}

	bool GUIElement::OnHover()
	{
		Vector2f normalizedMousePosition = ourMousePosition / Engine::GetRenderer().GetRenderTargetResolution();
		Vector4f normalizedPosition = Vector4f((myPosition.x) / myRenderSize.x, (myPosition.y) / myRenderSize.y, ((myPosition.x + mySize.x)  / myRenderSize.x), ((myPosition.y + mySize.y) / myRenderSize.y));
		if (!(normalizedMousePosition.x >= normalizedPosition.x && normalizedMousePosition.x <= normalizedPosition.z &&
			normalizedMousePosition.y >= normalizedPosition.y && normalizedMousePosition.y <= normalizedPosition.w))
		{
			myMouseOver = false;
			if (myGainedHover == true)
			{
				ExitHoverFunction();
			}
			ResetHover();
			return false;
		}
		myMouseOver = true;
		for (unsigned short i = 0; i < myChildren.Size(); i++)
		{
			if (myChildren[i]->myIsActive == true)
			{
				if (myChildren[i]->OnHover() == true)
				{
					if (myGainedHover == true)
					{
						ExitHoverFunction();
						myGainedHover = false;
					}
					return true;
				}
			}
		}
		if (myGainedHover == false)
		{
			if (myHoverSoundPath != "")
			{
				SB::Engine::GetSoundManager().PostEvent(myHoverSoundPath);
			}
			HoverFunction();
			myGainedHover = true;
		}
		return true;
	}

	//PRIVATE FUNCTIONS

	void GUIElement::SetAnchorOffset(GUIElement & aGUIElement)
	{
		if (aGUIElement.GetIsRoot() == false)
		{
			AnchorPoint anchorPoint = static_cast<AnchorPoint>(static_cast<int>(aGUIElement.myHorizontalAnchorPoint) | static_cast<int>(aGUIElement.myVerticalAnchorPoint));
			Vector2f offset;
			float halfSizeOffsetX;
			float halfSizeOffsetY;
			if (aGUIElement.myName.find("-button") == std::string::npos)
			{
				offset = aGUIElement.myParent->mySize;
				halfSizeOffsetX = (aGUIElement.myParent->mySize.x / 2.f);
				halfSizeOffsetY = (aGUIElement.myParent->mySize.y / 2.f);
			}
			else
			{
				offset = aGUIElement.myParent->myParent->mySize;
				halfSizeOffsetX = (aGUIElement.myParent->myParent->mySize.x / 2.f);
				halfSizeOffsetY = (aGUIElement.myParent->myParent->mySize.y / 2.f);
			}
			

			switch (anchorPoint)
			{
			case SB::AnchorPoint::eTopLeft:
				aGUIElement.myAnchorOffset = Vector2f(0.f, 0.f);
				aGUIElement.myOrigin = Vector2f(0.f, 0.f);
				break;
			case SB::AnchorPoint::eTopCenter:
				aGUIElement.myAnchorOffset = Vector2f(halfSizeOffsetX, 0.f);
				aGUIElement.myOrigin = Vector2f(aGUIElement.mySize.x / 2.f, 0.f);
				break;
			case SB::AnchorPoint::eTopRight:
				aGUIElement.myAnchorOffset = Vector2f(offset.x, 0.f);
				aGUIElement.myOrigin = Vector2f(aGUIElement.mySize.x, 0.f);
				break;
			case SB::AnchorPoint::eCenterRight:
				aGUIElement.myAnchorOffset = Vector2f(offset.x, halfSizeOffsetY);
				aGUIElement.myOrigin = Vector2f(aGUIElement.mySize.x, aGUIElement.mySize.y / 2.f);
				break;
			case SB::AnchorPoint::eBottomRight:
				aGUIElement.myAnchorOffset = Vector2f(offset.x, offset.y);
				aGUIElement.myOrigin = Vector2f(aGUIElement.mySize.x, aGUIElement.mySize.y);
				break;
			case SB::AnchorPoint::eBottomCenter:
				aGUIElement.myAnchorOffset = Vector2f(halfSizeOffsetX, offset.y);
				aGUIElement.myOrigin = Vector2f(aGUIElement.mySize.x / 2.f, aGUIElement.mySize.y);
				break;
			case SB::AnchorPoint::eBottomLeft:
				aGUIElement.myAnchorOffset = Vector2f(0.f, offset.y);
				aGUIElement.myOrigin = Vector2f(0, aGUIElement.mySize.y);
				break;
			case SB::AnchorPoint::eCenterLeft:
				aGUIElement.myAnchorOffset = Vector2f(0.f, halfSizeOffsetY);
				aGUIElement.myOrigin = Vector2f(0, aGUIElement.mySize.y / 2.f);
				break;
			case SB::AnchorPoint::eCenterCenter:
				aGUIElement.myAnchorOffset = Vector2f(halfSizeOffsetX, halfSizeOffsetY);
				aGUIElement.myOrigin = Vector2f(aGUIElement.mySize.x / 2.f, aGUIElement.mySize.y / 2.f);
				break;
			}
		}
	}

	void GUIElement::AlignChild(GUIElement & aGUIElement, const int aWidth, const int aHeight)
	{
		aGUIElement.SetAnchorOffset(aGUIElement);
		aGUIElement.SetAllowedSpace(Vector4f(myPosition.x, myPosition.y, myPosition.x + mySize.x, myPosition.y + mySize.y));
		AdjustBounderies(aGUIElement);
		AdjustPositions(aGUIElement, aWidth, aHeight);
	}

	void GUIElement::AdjustBounderies(GUIElement & aGUIElement)
	{
		if (aGUIElement.myName.find_first_of("-button") == std::string::npos)
		{
			if ((aGUIElement.myAllowedBoundery.z - myPadding.z) - (aGUIElement.myAllowedBoundery.x + myPadding.x) < aGUIElement.mySize.x)
			{
				if ((aGUIElement.myAllowedBoundery.x + myPadding.x + aGUIElement.mySize.x) > aGUIElement.myAllowedBoundery.z)
				{
					aGUIElement.myAllowedBoundery.x = aGUIElement.myAllowedBoundery.z - aGUIElement.mySize.x;
				}
				else if ((aGUIElement.myAllowedBoundery.z - myPadding.z - aGUIElement.mySize.x) < aGUIElement.myAllowedBoundery.x)
				{
					aGUIElement.myAllowedBoundery.z = aGUIElement.myAllowedBoundery.x + aGUIElement.mySize.x;
				}
				else
				{
					aGUIElement.myAllowedBoundery.x += myPadding.x;
					aGUIElement.myAllowedBoundery.z -= myPadding.z;
				}
			}
			else
			{
				aGUIElement.myAllowedBoundery.x += myPadding.x;
				aGUIElement.myAllowedBoundery.z -= myPadding.z;
			}


			if ((aGUIElement.myAllowedBoundery.w - myPadding.w) - (aGUIElement.myAllowedBoundery.y + myPadding.y) < aGUIElement.mySize.y)
			{
				if ((aGUIElement.myAllowedBoundery.y + myPadding.y + aGUIElement.mySize.y) > aGUIElement.myAllowedBoundery.w)
				{
					aGUIElement.myAllowedBoundery.y = aGUIElement.myAllowedBoundery.w - aGUIElement.mySize.y;
				}
				else if ((aGUIElement.myAllowedBoundery.w - myPadding.w - aGUIElement.mySize.y) < aGUIElement.myAllowedBoundery.y)
				{
					aGUIElement.myAllowedBoundery.w = aGUIElement.myAllowedBoundery.y + aGUIElement.mySize.y;
				}
				else
				{
					aGUIElement.myAllowedBoundery.y += myPadding.y;
					aGUIElement.myAllowedBoundery.w -= myPadding.w;
				}
			}
			else
			{
				aGUIElement.myAllowedBoundery.y += myPadding.y;
				aGUIElement.myAllowedBoundery.w -= myPadding.w;
			}
		}
	}

	void GUIElement::AdjustPositions(GUIElement & aGUIElement, const int aWidth, const int aHeight)
	{
		if (GetIsRoot() == false)
		{
			aGUIElement.SetPosition(Vector2f(
				aGUIElement.myNormalizedPosition.x * mySize.x + (myPosition.x),
				aGUIElement.myNormalizedPosition.y * mySize.y + (myPosition.y)));
		}
		else
		{
			aGUIElement.SetPosition(Vector2f(
				aGUIElement.myNormalizedPosition.x * (1080.f * (static_cast<float>(aWidth) / static_cast<float>(aHeight))),
				aGUIElement.myNormalizedPosition.y * 1080.f));
		}
	}

	void GUIElement::SetAllowedSpace(const Vector4f & aAllowedSize)
	{
		myAllowedBoundery = aAllowedSize;
	}
}
