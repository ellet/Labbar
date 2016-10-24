#include "stdafx.h"
#include "GUILoader.h"
#include "Engine\DataParser\DataParser.h"
#include "Engine\GUI\RootGUIElement.h"
#include "Engine\Scene\JsonScene.h"
#include "..\Game\Game\GUIHealthBar.h"
#include "..\Text\Text.h"
//Positions are relative to parent element
//Sprite, if left empty will generate an invisible GUIElement
//Children set to active will show as long as the parent does
namespace ENGINE_NAMESPACE
{
	GUILoader::GUILoader(std::unordered_map<std::string, std::function<void()>> & aFunctionMap)
	{
		myBoundFunctions = &aFunctionMap;
	}

	GUILoader::~GUILoader()
	{
	}

	std::shared_ptr<RootGUIElement> GUILoader::LoadGUI(const char* aFilePath)
	{
		if (myCreatedGUI.find(aFilePath) != myCreatedGUI.end())
		{
			return myCreatedGUI[aFilePath];
		}
		return CreateGUI(aFilePath);
	}

	std::shared_ptr<RootGUIElement> GUILoader::CreateGUI(const char* aFilePath)
	{
		DataDocument guiData;

		Data::Open(aFilePath, guiData);
		std::shared_ptr<RootGUIElement> root;
		std::string spritePath = guiData["sprite"].GetString();
		if (spritePath == "")
		{
			root = std::make_shared<RootGUIElement>(Vector4f(0.f, 0.f, Engine::GetRenderer().GetRenderTargetResolution().x, Engine::GetRenderer().GetRenderTargetResolution().y));
		}
		else
		{
			root = std::make_shared<RootGUIElement>(spritePath.c_str());
		}
		root->SetName("root");
		CreateGUIChildren(root, guiData["children"]);
		root->AlignChildren();

		return root;
	}

	void GUILoader::CreateGUIChildren(std::shared_ptr<GUIElement> aGUIElement, const DataNode & aElementData)
	{
		for (unsigned short i = 0; i < aElementData.Capacity(); i++)
		{
			DataNode elementData = aElementData[i];

			std::shared_ptr<GUIElement> newGUIElement;

			std::string name = elementData["name"].GetString();

			

			Vector4f borderPositions;
			borderPositions.x = elementData["position"][0].GetFloat();
			borderPositions.y = elementData["position"][1].GetFloat();
			borderPositions.z = borderPositions.x + elementData["size"][0].GetFloat();
			borderPositions.w = borderPositions.y + elementData["size"][1].GetFloat();

			Vector2f scale;
			scale.x = elementData["scale"][0].GetFloat();
			scale.y = elementData["scale"][1].GetFloat();

			std::string spritePath = elementData["sprite"].GetString();

			bool active = elementData["active"].GetBool();

			if (elementData.FindMember("type") != elementData.MemberEnd())
			{
				std::string typeName = elementData["type"].GetString();

				if (typeName == "PlayerBar")
				{
					newGUIElement = std::make_shared<GUIHealthBar>(spritePath.c_str(), Vector2f(borderPositions.x, borderPositions.y), scale, Vector2f(borderPositions.z - borderPositions.x, borderPositions.w - borderPositions.y));
				}
				else if (typeName == "Text")
				{
					std::string text = elementData["text"].GetString();
					std::shared_ptr<Text> newText = std::make_shared<Text>(Vector2f(borderPositions.x, borderPositions.y), scale, text);
					if (spritePath == "")
					{
						newGUIElement = std::make_shared<GUIElement>(borderPositions);
						newGUIElement->SetText(newText);
					}
					else
					{
						newGUIElement = std::make_shared<GUIElement>(spritePath.c_str(), Vector2f(borderPositions.x, borderPositions.y), scale, Vector2f(borderPositions.z - borderPositions.x, borderPositions.w - borderPositions.y));
						newGUIElement->SetText(newText);
					}
				}
				else
				{
					assert(false && "Type not found, please reconsider your life choices!");
				}
			}
			else
			{
				if (spritePath == "")
				{
					newGUIElement = std::make_shared<GUIElement>(borderPositions);
				}
				else
				{
					newGUIElement = std::make_shared<GUIElement>(spritePath.c_str(), Vector2f(borderPositions.x, borderPositions.y), scale, Vector2f(borderPositions.z - borderPositions.x, borderPositions.w - borderPositions.y));
				}
			}
			std::string functionName = elementData["function"].GetString();


			newGUIElement->SetName(name);
			newGUIElement->SetActive(active);
			if (functionName != "" && (*myBoundFunctions).find(functionName) == (*myBoundFunctions).end())
			{
				assert(false && "Could not find function");
			}
			newGUIElement->BindFunction((*myBoundFunctions)[functionName]);
			if (elementData["children"].Empty() == false)
			{
				CreateGUIChildren(newGUIElement, elementData["children"]);
			}
			aGUIElement->AddChild(newGUIElement);
		}
	}

}