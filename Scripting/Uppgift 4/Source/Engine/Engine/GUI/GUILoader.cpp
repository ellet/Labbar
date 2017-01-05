#include "stdafx.h"
#include "GUILoader.h"
#include "Engine\DataParser\DataParser.h"
#include "Engine\GUI\RootGUIElement.h"
#include "Engine\Scene\JsonScene.h"
#include "..\Text\Text.h"
#include "SpriteGUIElement.h"
#include "ButtonGUIElement.h"

//Positions are relative to parent element
//Sprite, if left empty will generate an invisible GUIElement
//Children set to active will show as long as the parent does
namespace SB
{
	GUILoader::GUILoader()
	{
	}

	GUILoader::~GUILoader()
	{
		
	}

	std::shared_ptr<RootGUIElement> GUILoader::LoadGUI(const std::string & aGUIPath)
	{
		if (myCreatedGUI.find(aGUIPath) != myCreatedGUI.end())
		{	
			SetCurrentGUI(aGUIPath);
			return myCreatedGUI[aGUIPath];
		}
		std::shared_ptr<RootGUIElement> newGUI = CreateGUI(aGUIPath);
		SetCurrentGUI(aGUIPath);
		return newGUI;
	}

	std::shared_ptr<RootGUIElement> GUILoader::CreateGUI(const std::string & aGUIPath)
	{
		DataDocument guiData;
		Data::Open(aGUIPath, guiData);
		std::shared_ptr<RootGUIElement> root;
		root = std::make_shared<RootGUIElement>(Vector2f::Zero, Vector2f((1080.f * (Engine::GetRenderer().GetRenderTargetResolution().x / Engine::GetRenderer().GetRenderTargetResolution().y)), 1080.f));
		root->SetName("root");
		Vector4f padding = Vector4f::Zero;
		if (guiData.HasMember("padding") == true)
		{
			padding.y = guiData["padding"][0].GetFloat();
			padding.x = guiData["padding"][1].GetFloat();
			padding.z = guiData["padding"][2].GetFloat();
			padding.w = guiData["padding"][3].GetFloat();
		}
		root->SetPadding(padding);
		CreateGUIChildren(root, guiData["children"]);
		myCreatedGUI[aGUIPath] = root;
		return myCreatedGUI[aGUIPath];
	}

	void GUILoader::DisableGUI()
	{
		for (std::unordered_map<std::string, std::shared_ptr<RootGUIElement>>::iterator i = myCreatedGUI.begin(); i != myCreatedGUI.end(); i++)
		{
			i->second->SetMyIsCurrentGUI(false);
		}
	}

	void GUILoader::SetCurrentGUI(const std::string & aGUIName)
	{
		for (std::unordered_map<std::string, std::shared_ptr<RootGUIElement>>::iterator i = myCreatedGUI.begin(); i != myCreatedGUI.end(); i++)
		{
			i->second->SetMyIsCurrentGUI(false);
		}
		myCreatedGUI[aGUIName]->SetMyIsCurrentGUI(true);
	}

	void GUILoader::CreateGUIChildren(std::shared_ptr<GUIElement> aGUIElement, const DataNode & aElementData)
	{
		for (unsigned short i = 0; i < aElementData.Capacity(); i++)
		{
			DataNode elementData = aElementData[i];
			Vector2f position;
			Vector2f size;
			position.x = elementData["position"][0].GetFloat();
			position.y = elementData["position"][1].GetFloat();
			size.x = elementData["size"][0].GetFloat();
			size.y = elementData["size"][1].GetFloat();
			Vector2f scale;
			scale.x = elementData["scale"][0].GetFloat();
			scale.y = elementData["scale"][1].GetFloat();
			std::string typeName = elementData["type"].GetString();
			if (typeName == "")
			{
				if (elementData.HasMember("sprite") == true)
				{
					std::shared_ptr<SpriteGUIElement> newGUIElement;
					std::string spritePath = elementData["sprite"].GetString();
					newGUIElement = std::make_shared<SpriteGUIElement>(spritePath.c_str(), position, false, scale, size);
					SetGUISettings(*newGUIElement, elementData);
					newGUIElement->SetIsHoverActivated(elementData["hover"].GetBool());
					aGUIElement->AddChild(newGUIElement);
					if (elementData["children"].Empty() == false)
					{
						CreateGUIChildren(newGUIElement, elementData["children"]);
					}			
				}
				else
				{
					std::shared_ptr<GUIElement> newGUIElement;
					newGUIElement = std::make_shared<GUIElement>(position, size);
					SetGUISettings(*newGUIElement, elementData);
					aGUIElement->AddChild(newGUIElement);
					if (elementData["children"].Empty() == false)
					{
						CreateGUIChildren(newGUIElement, elementData["children"]);
					}
				}			
			}
			else if (typeName == "button")
			{
				std::shared_ptr<ButtonGUIElement> newGUIElement;
				std::string spritePath = elementData["sprite"].GetString();
				newGUIElement = std::make_shared<ButtonGUIElement>(spritePath.c_str(), position, false, scale, size);
				SetGUISettings(*newGUIElement, elementData);
				newGUIElement->SetIsHoverActivated(elementData["hover"].GetBool());
				aGUIElement->AddChild(newGUIElement);
				newGUIElement->AddButtonChild();
				if (elementData["children"].Empty() == false)
				{
					CreateGUIChildren(newGUIElement, elementData["children"]);
				}
			}
			else
			{
				assert(false && "Type not found, please reconsider your life choices!");
			}
		}
	}

}