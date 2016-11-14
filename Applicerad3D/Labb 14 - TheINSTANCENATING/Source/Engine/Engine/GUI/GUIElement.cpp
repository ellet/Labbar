#include "stdafx.h"
#include "GUIElement.h"
#include "..\Text\Text.h"
#include "Engine/GenericEngineMessages.h"

namespace ENGINE_NAMESPACE
{
	Vector2f GUIElement::ourMousePosition = Vector2f(0.f, 0.f);
	GUIElement::GUIElement() : GUIElement(Vector4f(0.0f, 0.0f, 100.f, 100.f))
	{
	}

	GUIElement::GUIElement(const Vector4f & aBorderPositions)
	{
		myHasFocus = true;
		myGainedHover = false;
		myIsActive = false;
		mySprite = nullptr;
		myText = nullptr;
		myParent = nullptr;
		myFunction = nullptr;
		myHoverFunction = nullptr;
		myBorderPositions = aBorderPositions;
		myName = "";
		myHoverSprite = "";
		mySpritePath = "";
	}

	GUIElement::GUIElement(const char * aTexturePath, const Vector2f& aPosition, const Vector2f& aScale, const Vector2f& aSize)
	{
		myHasFocus = true;
		myGainedHover = false;
		if (aTexturePath != nullptr)
		{
			mySpritePath = aTexturePath;
			myHoverSprite = aTexturePath;
			if (myHoverSprite.find_first_of(".") != std::string::npos)
			{
				myHoverSprite = myHoverSprite.substr(0, myHoverSprite.find_first_of("."));
				myHoverSprite += "Hover.dds";
			}
			mySprite = std::make_shared<Sprite>();
			mySprite->SetTexture(Engine::GetResourceManager().Get<Texture>(aTexturePath));
			mySprite->SetScale(aScale);
			myBorderPositions = mySprite->GetBorderPositions();
			if (aSize != Vector2f::Zero)
			{
				myBorderPositions.z = aSize.x * aScale.x;
				myBorderPositions.w = aSize.y * aScale.y;
			}
			myBorderPositions += Vector4f(aPosition.x, aPosition.y, aPosition.x, aPosition.y);
		}
		myParent = nullptr;
		myIsActive = false;
	}

	GUIElement::~GUIElement()
	{
	}

	void GUIElement::AddChild(std::shared_ptr<GUIElement> aGUIElement)
	{
		aGUIElement->SetParent(this);
		aGUIElement->myHasFocus = false;
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

	void GUIElement::AlignChildren()
	{
		float diff;
		for (unsigned short i = 0; i < myChildren.Size(); i++)
		{
			myChildren[i]->myBorderPositions += Vector4f(myBorderPositions.x, myBorderPositions.y, myBorderPositions.x, myBorderPositions.y);

			if (myChildren[i]->myBorderPositions.z > myBorderPositions.z)
			{
				diff = myChildren[i]->myBorderPositions.z - myBorderPositions.z;
				myChildren[i]->myBorderPositions.x -= diff;
				myChildren[i]->myBorderPositions.z -= diff;
			}
			if (myChildren[i]->myBorderPositions.x < myBorderPositions.x)
			{
				diff = myChildren[i]->myBorderPositions.x - myBorderPositions.x;
				myChildren[i]->myBorderPositions.x -= diff;
				myChildren[i]->myBorderPositions.z -= diff;
			}
			if (myChildren[i]->myBorderPositions.y < myBorderPositions.y)
			{
				diff = myChildren[i]->myBorderPositions.y - myBorderPositions.y;
				myChildren[i]->myBorderPositions.y -= diff;
				myChildren[i]->myBorderPositions.w -= diff;
			}
			if (myChildren[i]->myBorderPositions.w > myBorderPositions.w)
			{
				diff = myChildren[i]->myBorderPositions.w - myBorderPositions.w;
				myChildren[i]->myBorderPositions.y -= diff;
				myChildren[i]->myBorderPositions.w -= diff;
			}
			myChildren[i]->AlignChildren();

		}
	}

	void GUIElement::SetSprite(const char * aTexturePath)
	{
		if (mySprite != nullptr)
		{
			mySprite->SetTexture(Engine::GetResourceManager().Get<Texture>(aTexturePath, nullptr, true));
		}
	}

	bool GUIElement::OnHover()
	{
		if (!(ourMousePosition.x >= myBorderPositions.x && ourMousePosition.x <= myBorderPositions.z &&
			ourMousePosition.y >= myBorderPositions.y && ourMousePosition.y <= myBorderPositions.w))
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
			HoverFunction();
			myGainedHover = true;
		}
		return true;
	}

	void GUIElement::Update()
	{
		for (unsigned short i = 0; i < myChildren.Size(); i++)
		{
			if (myChildren[i]->myIsActive == true)
			{
				myChildren[i]->Update();
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

	void GUIElement::Render()
	{
		if (mySprite != nullptr)
		{
			mySprite->SetPosition(Vector2f(myBorderPositions.x, myBorderPositions.y));
			mySprite->Render();
		}

		for (unsigned short i = 0; i < myChildren.Size(); i++)
		{
			if (myChildren[i]->myIsActive == true)
			{
				myChildren[i]->Render();
			}
		}
		if (myText != nullptr)
		{
			myText->SetPositionTopLeft(Vector2f(myBorderPositions.x, myBorderPositions.y));
			myText->Render();
		}
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

	void GUIElement::SetParent(GUIElement * aParent)
	{
		myParent = aParent;
	}

	void GUIElement::SetName(const std::string & aName)
	{
		myName = aName;
	}

	void GUIElement::LeftClickFunction()
	{
		for (unsigned short i = 0; i < myChildren.Size(); i++)
		{
			if (myChildren[i]->myMouseOver == true)
			{
				myChildren[i]->LeftClickFunction();
				return;
			}
		}
		if (myFunction != nullptr)
		{
			myFunction();
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
	}

	void GUIElement::GainedFocus()
	{
		myGainedFocus = false;
		std::cout << "Gained Focus" << std::endl;
	}

	void GUIElement::LostFocus()
	{

	}

	GUIElement* GUIElement::GetGUIElement(const std::string & aName)
	{
		if (InternGetGUIElement(aName) == nullptr)
		{
			Error("GUIElement: " + aName + " doesn't exist!")
		}
		else
		{
			return InternGetGUIElement(aName);
		}
	}

	void GUIElement::SetIsHoverActivated(bool aValue)
	{
		myIsHoverSpriteActivated = aValue;
	}

	const Sprite & GUIElement::GetSprite() const
	{
		return *mySprite;
	}

	const bool GUIElement::GetActive() const
	{
		return myIsActive;
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

	void GUIElement::SetRotation(const float aRotation)
	{
		mySprite->SetRotation(aRotation);
	}

	void GUIElement::SetPosition(const Vector2f & aPosition)
	{
		myBorderPositions.x = aPosition.x;
		myBorderPositions.y = aPosition.y;
		myBorderPositions.z = aPosition.x + myBorderPositions.z;
		myBorderPositions.w = aPosition.y + myBorderPositions.w;
	}

	const Vector2f GUIElement::GetPosition() const
	{
		return Vector2f(myBorderPositions.x, myBorderPositions.y);
	}

	float GUIElement::GetRotation() const
	{
		return mySprite->GetRotation();
	}

	GUIElement* GUIElement::InternGetGUIElement(const std::string & aName)
	{
		if (myName == aName)
		{
			return this;
		}
		else
		{
			GUIElement* tempGUI = nullptr;
			for (unsigned short i = 0; i < myChildren.Size(); i++)
			{
				tempGUI = myChildren[i]->InternGetGUIElement(aName);
				if (tempGUI != nullptr)
				{
					break;
				}
			}
			return tempGUI;
		}
	}

	void GUIElement::BindFunction(std::unordered_map<std::string, std::function<void()>> & aFunctionMap, const std::string & aFunctionName, bool aBindHoverFunction)
	{
		if (aBindHoverFunction == false)
		{
			myFunction = [&, aFunctionName]()
			{
				if (aFunctionMap.find(aFunctionName) == aFunctionMap.end())
				{
					std::cout << aFunctionName << std::endl;
					assert(false && "Could not find function");
					Error("could not find function");
				}
				std::function<void()> function;
				function = aFunctionMap[aFunctionName];
				myFunction = aFunctionMap[aFunctionName];
				function(); 
			};
		}
		else
		{
			myHoverFunction = [&, aFunctionName]()
			{
				if (aFunctionMap.find(aFunctionName) == aFunctionMap.end())
				{
					std::cout << aFunctionName << std::endl;
					assert(false && "Could not find function");
					Error("could not find function");
				}
				std::function<void()> function;
				function = aFunctionMap[aFunctionName];
				myHoverFunction = aFunctionMap[aFunctionName];
				function(); 
			};
		}
	}

	const Vector4f & GUIElement::GetBorderPosition() const
	{
		return myBorderPositions;
	}

	GUIElement * GUIElement::GetParent() const
	{
		return myParent;
	}

	void GUIElement::SetText(std::shared_ptr<Text> aTextPtr)
	{
		myText = aTextPtr;

		myBorderPositions = myText->GetBoundaries();

		if (myParent != nullptr)
		{
			myParent->AlignChildren();
		}
	}

	void GUIElement::SetFunctionName(const std::string & aName)
	{
		myFunctionName = aName;
	}

	void GUIElement::ExitHoverFunction()
	{
		if (mySprite != nullptr && myIsHoverSpriteActivated == true)
		{
		PostMaster::Post<ChangeCursorMessage>(ChangeCursorMessage(eCursorState::eNormal));
			mySprite->SetTexture(Engine::GetResourceManager().Get<Texture>(mySpritePath));
		}
	}

	void GUIElement::HoverFunction()
	{

		if (mySprite != nullptr && myIsHoverSpriteActivated == true)
		{
			PostMaster::Post<ChangeCursorMessage>(ChangeCursorMessage(eCursorState::eHover));
			mySprite->SetTexture(Engine::GetResourceManager().Get<Texture>(myHoverSprite));
		}
		if (myHoverFunction != nullptr)
		{
			myHoverFunction();
		}
	}
}