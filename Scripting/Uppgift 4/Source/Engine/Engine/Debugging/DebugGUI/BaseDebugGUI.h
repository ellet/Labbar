#pragma once
#include "..\Utilities\Utilities\HelperFunctions\StringHandling.h"

namespace SB
{

	namespace DebugGUI
	{
		template<unsigned short TMaxChars = 128>
		void TextBox(std::string & aText, const std::string & aLabel = "Text");

		bool Combobox(GrowingArray<std::string> & aArrayOfStrings, int & aIndexToStartAt,const std::string & aLabel = "ComboBox");

		template<typename TIterator, typename TData>
		bool Combobox(std::unordered_map<std::string, TData> & aMapData, TIterator & aCurrentIndex, const std::string aLabel = "ComboBox");
		template<typename TData>
		bool Combobox(std::unordered_map<std::string, TData> & aMapData, TData & aCurrentIndex, const std::string aLabel = "ComboBox");
		template<typename TData>
		bool Combobox(std::unordered_map<std::string, TData> & aMapData, std::string & aCurrentIndex, const std::string aLabel = "ComboBox");

		void SetWindowPosition(const Vector2f & aPosition);
		void SetElementsWidth(float aWidth);

		void SetDebugGUISize(const Vector2f & aWidthHeight);

		void ImageAndRect(Vector4f & someUVs, std::shared_ptr<SB::Texture> aTexture, const float aScale = 1.f);

		void VectorSetter(Vector2f & aVectorToSet, const Vector2f aRange = Vector2f(0.f, 1.f), bool isMinMax = false);
		void VectorSetter(Vector4f & aVectorToSet, const Vector2f aRange = Vector2f(0.f, 1.f));

		void MinMaxSlider(Vector2f & aVectorToSet, const Vector2f aRange = Vector2f(0.f, 1.f));

		void VectorSlider(Vector2f & aVectorToSet, const Vector2f aRange = Vector2f(0.f, 1.f));
		void VectorSlider(Vector3f & aVectorToSet, const Vector2f aRange = Vector2f(0.f, 1.f));
		void VectorSlider(Vector4f & aVectorToSet, const Vector2f aRange = Vector2f(0.f, 1.f), bool aIsColor = false);

		void PrintVector(const Vector3f & aVectorToPrint, const std::string & aName = "Vector: ");
		void PrintVector(const Vector4f & aVectorToPrint, const std::string & aName = "Vector: ");

		void FloatSlider(float & aFloatToSet, const Vector2f aRange = Vector2f(0.f, 1.f), const std::string & aSliderName = "Float: ");

		void IntSlider(int & aNumberToSet, const Vector2i aRange = Vector2i(0, 1), const std::string & aSliderName = "#: ");
		void IntSetter(int & aNumberToSet, const std::string & anIntName = "#: ");
		void FloatSetter(float & aNumberToSet, const std::string & aName = "#: ");

		void PrintText(const std::string & aTextToPrint);
		void PrintText(const std::string & aTextToPrint, const Vector4f & aColor);

		void CheckBox(bool & aBoolToSet, const std::string & aName);

		bool Button(const std::string & aName, const Vector2f & aSize);

		template<unsigned short TMaxChars /*= 128*/>
		void TextBox(std::string & aText, const std::string & aLabel /*= "Text"*/)
		{
			const unsigned short TextLenght = TMaxChars;
			GrowingArray<char> tempInput(TextLenght);

			SB::HelperFunction::ConvertStringToCharPointer(aText, tempInput);

			ImGui::InputText(aLabel.c_str(), &tempInput[0], TextLenght);
			aText = std::string(&tempInput[0]);
		}

		//template<typename TIterator, typename TData>
		inline bool Combobox(GrowingArray<std::string, unsigned short> & aListOfOptions, unsigned short & aCurrentIndex, std::string & aChosenIndexByName, const std::string aLabel /*= "ComboBox"*/)
		{
			if (aListOfOptions.Size() == 0)
			{
				return false;
			}

			int tempSelectedIndex = static_cast<int>(aCurrentIndex);

			GrowingArray<const char *> tempArray;
			for (unsigned short i = 0; i < aListOfOptions.Size(); ++i)
			{
				tempArray.Add(aListOfOptions[i].c_str());
			}

			if (ImGui::Combo(aLabel.c_str(), &tempSelectedIndex, &tempArray[0], aListOfOptions.Size()) == true)
			{
				aChosenIndexByName = (aListOfOptions[static_cast<unsigned short>(tempSelectedIndex)]);
				aCurrentIndex = static_cast<unsigned short>(tempSelectedIndex);
				return true;
			}
			return false;
		}

		template<typename TIterator, typename TData>
		bool Combobox(std::unordered_map<std::string, TData> & aMapData, TIterator & aCurrentIndex, const std::string aLabel /*= "ComboBox"*/)
		{
			
			int tempSelectedIndex = 0;
			int currentIndex = 0;
			GrowingArray<const char*> tempArray;

			if (aCurrentIndex == aMapData.end())
			{
				/*
					Warn index did not exist
				*/
				aCurrentIndex = aMapData.begin();
			}

			for (TIterator iString = aMapData.begin(); iString != aMapData.end(); ++iString)
			{
				if (aCurrentIndex == iString)
				{
					tempSelectedIndex = currentIndex;
				}

				tempArray.Add(iString->first.c_str());

				++currentIndex;
			}

			if (ImGui::Combo(aLabel.c_str(), &tempSelectedIndex, &tempArray[0], tempArray.Size()) == true)
			{
				const std::string tempFindString(tempArray[static_cast<unsigned short>(tempSelectedIndex)]);

				aCurrentIndex = aMapData.find(tempFindString);
				return true;
			}
			return false;
		}

		template<typename TData>
		bool Combobox(std::unordered_map<std::string, TData> & aMapData, TData & aCurrentIndex, const std::string aLabel /*= "ComboBox"*/)
		{
			std::unordered_map<std::string, TData>::iterator iValue = aMapData.begin();
			for (; iValue != aMapData.end(); ++iValue)
			{
				if (iValue->second == aCurrentIndex)
				{
					break;
				}
			}

			if (Combobox(aMapData, iValue, aLabel) == true)
			{
				aCurrentIndex = iValue->second;

				return true;
			}
			return false;

		}

		template<typename TData>
		bool Combobox(std::unordered_map<std::string, TData> & aMapData, std::string & aCurrentIndex, const std::string aLabel /*= "ComboBox"*/)
		{
			std::unordered_map<std::string, TData>::iterator aCurrentIt = aMapData.find(aCurrentIndex);

			if (Combobox(aMapData, aCurrentIt, aLabel) == true)
			{
				aCurrentIndex = aCurrentIt->first;

				return true;
			}

			return false;
		}
	}

}
