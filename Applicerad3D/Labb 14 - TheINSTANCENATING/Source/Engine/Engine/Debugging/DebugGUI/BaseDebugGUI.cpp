#include "stdafx.h"
#include "BaseDebugGUI.h"
#include "imgui.h"
#include "..\Utilities\Utilities\HelperFunctions\StringHandling.h"

namespace ENGINE_NAMESPACE
{
	namespace DebugGUI
	{
		bool Combobox(GrowingArray<std::string> & aArrayOfStrings, int & aIndexToStartAt, const std::string & aLabel /*= "ComboBox"*/)
		{
			GrowingArray<const char*> tempArrayOfOptions;
			tempArrayOfOptions.Resize(aArrayOfStrings.Size());

			for (unsigned short iString = 0; iString < aArrayOfStrings.Size(); ++iString)
			{
				tempArrayOfOptions[iString] = aArrayOfStrings[iString].c_str();
				
			}

			return ImGui::Combo(aLabel.c_str(), &aIndexToStartAt, &tempArrayOfOptions[0], tempArrayOfOptions.Size());
		}

		

		void SetWindowPosition(const Vector2f & aPosition)
		{
			ImVec2 position;
			position.x = aPosition.x;
			position.y = aPosition.y;
			ImGui::SetWindowPos(position);
		}

		void SetElementsWidth(float aWidth)
		{
			ImGui::PushItemWidth(aWidth);
		}

		void SetDebugGUISize(const Vector2f & aWidthHeight)
		{
			ImVec2 size;
			size.x = aWidthHeight.x;
			size.y = aWidthHeight.y;
			ImGui::SetWindowSize(size);
		}

		void ImageAndRect(Vector4f & someUVs, std::shared_ptr<SB::Texture> aTexture, const float aScale/* = 1.f*/)
		{
			ImVec2 size(someUVs.z * aScale, someUVs.w * aScale);
			Vector2f actualSize = aTexture->GetSize() * aScale;
			ImVec2 uvPos;
			uvPos.x = (someUVs.x / actualSize.x) * aScale;
			uvPos.y = (someUVs.y / actualSize.y) * aScale;
			ImVec2 uvWH;
			uvWH.x = ((someUVs.z / actualSize.x) + uvPos.x) * aScale;
			uvWH.y = ((someUVs.w / actualSize.y) + uvPos.y) * aScale;

			ImGui::Image((void*)aTexture->GetView(), size, uvPos, uvWH);
		}

		void Clamp(float & aValue, const Vector2f aRange)
		{
			if (aValue < aRange.x)
			{
				aValue = aRange.x;
			}
			if (aValue > aRange.y)
			{
				aValue = aRange.y;
			}
		}

		void VectorSetter(Vector2f & aVectorToSet, const Vector2f aRange/* = Vector2f(0.f, 1.f)*/, bool isMinMax/* = false*/)
		{
			ImGui::PushID(&aVectorToSet);

			Clamp(aVectorToSet.x, aRange);
			Clamp(aVectorToSet.y, aRange);

			if (isMinMax == true)
			{
				ImGui::InputFloat("Min", &aVectorToSet.x);
				ImGui::SameLine();
				ImGui::InputFloat("Max", &aVectorToSet.y);
			}
			else
			{
				ImGui::InputFloat("X", &aVectorToSet.x);
				ImGui::SameLine();
				ImGui::InputFloat("Y", &aVectorToSet.y);
			}

			ImGui::PopID();
		}

		void VectorSetter(Vector4f & aVectorToSet, const Vector2f aRange/* = Vector2f(0.f, 1.f)*/)
		{
			ImGui::PushID(&aVectorToSet);

			Clamp(aVectorToSet.x, aRange);
			Clamp(aVectorToSet.y, aRange);
			Clamp(aVectorToSet.z, aRange);
			Clamp(aVectorToSet.w, aRange);

			ImGui::InputFloat("X", &aVectorToSet.x);
			ImGui::SameLine();
			ImGui::InputFloat("Y", &aVectorToSet.y);
			ImGui::SameLine();
			ImGui::InputFloat("Z", &aVectorToSet.z);
			ImGui::SameLine();
			ImGui::InputFloat("W", &aVectorToSet.w);

			ImGui::PopID();
		}

		void MinMaxSlider(Vector2f & aVectorToSet, const Vector2f aRange /*= Vector2f(0.f, 1.f)*/)
		{
			ImGui::PushID(&aVectorToSet);

			ImGui::SliderFloat("Min", &aVectorToSet.x, aRange.x, aVectorToSet.y);
			ImGui::SameLine();
			ImGui::SliderFloat("Max", &aVectorToSet.y, aVectorToSet.x, aRange.y);

			ImGui::PopID();
		}

		void VectorSlider(Vector2f & aVectorToSet, const Vector2f aRange /*= Vector2f(0.f, 1.f)*/)
		{
			ImGui::PushID(&aVectorToSet);

			ImGui::SliderFloat("X", &aVectorToSet.x, aRange.x, aRange.y);
			ImGui::SameLine();
			ImGui::SliderFloat("Y", &aVectorToSet.y, aRange.x, aRange.y);

			ImGui::PopID();
		}

		void VectorSlider(Vector3f & aVectorToSet, const Vector2f aRange /*= Vector2f(0.f, 1.f)*/)
		{
			ImGui::PushID(&aVectorToSet);

			ImGui::SliderFloat("X", &aVectorToSet.x, aRange.x, aRange.y);
			ImGui::SameLine();
			ImGui::SliderFloat("Y", &aVectorToSet.y, aRange.x, aRange.y);
			ImGui::SameLine();
			ImGui::SliderFloat("Z", &aVectorToSet.z, aRange.x, aRange.y);

			ImGui::PopID();
		}

		void VectorSlider(Vector4f & aVectorToSet, const Vector2f aRange /*= Vector2f(0.f, 1.f)*/, bool aIsColor/* = false*/)
		{
			ImGui::PushID(&aVectorToSet);
			if (aIsColor == true)
			{
				ImGui::SliderFloat("R", &aVectorToSet.x, aRange.x, aRange.y);
				ImGui::SameLine();
				ImGui::SliderFloat("G", &aVectorToSet.y, aRange.x, aRange.y);
				ImGui::SameLine();
				ImGui::SliderFloat("B", &aVectorToSet.z, aRange.x, aRange.y);
				ImGui::SameLine();
				ImGui::SliderFloat("A", &aVectorToSet.w, aRange.x, aRange.y);
			}
			else
			{
				ImGui::SliderFloat("X", &aVectorToSet.x, aRange.x, aRange.y);
				ImGui::SameLine();
				ImGui::SliderFloat("Y", &aVectorToSet.y, aRange.x, aRange.y);
				ImGui::SameLine();
				ImGui::SliderFloat("Z", &aVectorToSet.z, aRange.x, aRange.y);
				ImGui::SameLine();
				ImGui::SliderFloat("W", &aVectorToSet.w, aRange.x, aRange.y);
			}
			ImGui::PopID();
		}

		void PrintVector(const Vector3f & aVectorToPrint, const std::string & aName /*= "Vector: "*/)
		{
			ImGui::Text((aName + FormatString( " X : {0}; Y : {1}; Z : {2}", aVectorToPrint.x, aVectorToPrint.y, aVectorToPrint.z)).c_str());
		}

		void PrintVector(const Vector4f & aVectorToPrint, const std::string & aName /*= "Vector: "*/)
		{
			ImGui::Text((aName + FormatString(" X : {0}; Y : {1}; Z : {2}, W : {3}", aVectorToPrint.x, aVectorToPrint.y, aVectorToPrint.z, aVectorToPrint.w)).c_str());
		}

		void FloatSlider(float & aFloatToSet, const Vector2f aRange /*= Vector2f(0.f, 1.f)*/, const std::string & aSliderName /*= "Float: "*/)
		{
			ImGui::SliderFloat(aSliderName.c_str(), &aFloatToSet, aRange.x, aRange.y);
		}

		void IntSlider(int & aNumberToSet, const Vector2i aRange /*= Vector2i(0, 1)*/, const std::string & aSliderName /*= "#: "*/)
		{
			ImGui::SliderInt(aSliderName.c_str(), &aNumberToSet, aRange.x, aRange.y);
		}

		void PrintText(const std::string & aTextToPrint)
		{
			ImGui::Text(aTextToPrint.c_str());
		}

		void PrintText(const std::string & aTextToPrint, const Vector4f & aColor)
		{
			ImVec4 color;
			color.x = aColor.x;
			color.y = aColor.y;
			color.z = aColor.z;
			color.w = aColor.w;

			ImGui::TextColored(color, aTextToPrint.c_str());
		}

		void CheckBox(bool & aBoolToSet, const std::string & aName)
		{
			ImGui::Checkbox(aName.c_str(), &aBoolToSet);

		}

		void SameLine()
		{
			ImGui::SameLine();
		}

		bool Button(const std::string & aName, const Vector2f & aSize)
		{
			ImVec2 size;
			size.x = aSize.x;
			size.y = aSize.y;
			return ImGui::Button(aName.c_str(), size);
		}

	}

}