#include "stdafx.h"
#include "GUIElement.h"
#include "..\Text\Text.h"


namespace ENGINE_NAMESPACE
{
	Vector2f GUIElement::ourMousePosition = Vector2f(0.f, 0.f);
	GUIElement::GUIElement() : GUIElement(Vector4f(0.0f, 0.0f, 100.f, 100.f))
	{
	}

	GUIElement::GUIElement(const Vector4f & aBorderPositions)
	{
		myHasFocus = true;
		myIsActive = false;
		mySprite = nullptr;
		myText = nullptr;
		myParent = nullptr;
		myFunction = nullptr;
		myBorderPositions = aBorderPositions;
		myName = "";
	}

	GUIElement::GUIElement(const char * aTexturePath, const Vector2f& aPosition, const Vector2f& aScale, const Vector2f& aSize)
	{
		myHasFocus = true;
		if (aTexturePath != nullptr)
		{
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
			return false;
		}
		myMouseOver = true;

		for (unsigned short i = 0; i < myChildren.Size(); i++)
		{
			if (myChildren[i]->myIsActive == true)
			{
				if (myChildren[i]->OnHover() == true)
				{
					return true;
				}
			}
		}
		MyHoverFunction();
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
			mySprite->SetRotation(0.f);
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

	void GUIElement::BindFunction(std::function<void()> aFunctionToCall)
	{
		myFunction = aFunctionToCall;
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

	void GUIElement::MyHoverFunction()
	{

	}
}