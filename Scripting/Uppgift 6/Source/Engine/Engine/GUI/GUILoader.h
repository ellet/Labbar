#pragma once

namespace SB
{
	class GUIElement;
	class SpriteGUIElement;
	class ButtonGUIElement;
	class RootGUIElement;
	class JsonScene;
	class GUILoader
	{
	public:
		GUILoader();
		~GUILoader();
		std::shared_ptr<RootGUIElement> CreateGUI(const std::string & aGUIPath);
		void DisableGUI();
		void SetCurrentGUI(const std::string & aGUIName);
		std::shared_ptr<RootGUIElement> LoadGUI(const std::string & aGUIPath);
	private:
		template<typename TGuiType>
		void SetAnchorPoints(TGuiType & aNewGUIElement, const std::string & aHorizontal, const std::string & aVertical);
		void CreateGUIChildren(std::shared_ptr<GUIElement> aGUIElement, const DataNode & aElementData);
		template<typename TGuiType>
		void SetGUISettings(TGuiType & aNewGUIElement, const DataNode & aElementData);
		std::unordered_map<std::string, std::shared_ptr<RootGUIElement >> myCreatedGUI;
		JsonScene * myScenePtr;
		Vector2f myRenderSize;
	};

	template<typename TGuiType>
	void GUILoader::SetAnchorPoints(TGuiType & aNewGUIElement, const std::string & aHorizontal, const std::string & aVertical)
	{
		if (aHorizontal == "left")
		{
			if (aVertical == "top")
				aNewGUIElement.SetAnchorPoint(HorizontalAnchorPoint::eLeft, VerticalAnchorPoint::eTop);
			else if (aVertical == "bottom")
				aNewGUIElement.SetAnchorPoint(HorizontalAnchorPoint::eLeft, VerticalAnchorPoint::eBottom);
			else
				aNewGUIElement.SetAnchorPoint(HorizontalAnchorPoint::eLeft, VerticalAnchorPoint::eCenter);

		}
		else if (aHorizontal == "right")
		{
			if (aVertical == "top")
				aNewGUIElement.SetAnchorPoint(HorizontalAnchorPoint::eRight, VerticalAnchorPoint::eTop);
			else if (aVertical == "bottom")
				aNewGUIElement.SetAnchorPoint(HorizontalAnchorPoint::eRight, VerticalAnchorPoint::eBottom);
			else
				aNewGUIElement.SetAnchorPoint(HorizontalAnchorPoint::eRight, VerticalAnchorPoint::eCenter);
		}
		else
		{
			if (aVertical == "top")
				aNewGUIElement.SetAnchorPoint(HorizontalAnchorPoint::eCenter, VerticalAnchorPoint::eTop);
			else if (aVertical == "bottom")
				aNewGUIElement.SetAnchorPoint(HorizontalAnchorPoint::eCenter, VerticalAnchorPoint::eBottom);
			else
				aNewGUIElement.SetAnchorPoint(HorizontalAnchorPoint::eCenter, VerticalAnchorPoint::eCenter);
		}
	}
	
	template<typename TGuiType>
	void GUILoader::SetGUISettings(TGuiType & aNewGUIElement, const DataNode & aElementData)
	{
		if (aElementData.HasMember("hoverSound") == true)
		{
			std::string hoverSound = aElementData["hoverSound"].GetString();
			aNewGUIElement.SetHoverSoundPath(hoverSound);
		}
		if (aElementData.HasMember("clickSound") == true)
		{
			std::string clickSound = aElementData["clickSound"].GetString();
			aNewGUIElement.SetClickSoundPath(clickSound);
		}
		std::string name = aElementData["name"].GetString();
		aNewGUIElement.SetName(name);


		if (aElementData.HasMember("horizontalAnchorPoint") && aElementData.HasMember("verticalAnchorPoint"))
		{
			std::string horizontalAnchorPoint = aElementData["horizontalAnchorPoint"].GetString();
			std::string verticalAnchorPoint = aElementData["verticalAnchorPoint"].GetString();
			SetAnchorPoints<TGuiType>(aNewGUIElement, horizontalAnchorPoint, verticalAnchorPoint);
		}
		bool active = aElementData["active"].GetBool();
		aNewGUIElement.SetActive(active);
		Vector4f padding = Vector4f::Zero;

		if (aElementData.HasMember("padding") == true)
		{
			padding.y = aElementData["padding"][0].GetFloat();
			padding.x = aElementData["padding"][1].GetFloat();
			padding.z = aElementData["padding"][2].GetFloat();
			padding.w = aElementData["padding"][3].GetFloat();
		}
		aNewGUIElement.SetPadding(padding);
	}

}

