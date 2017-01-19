/*
Use this class to create and show a text
*/

#pragma once
#include <tga2d/math/Color.h>
#include <tga2d/math/vector2.h>
#include <tga2d/render/render_common.h>
#include <string>

namespace Tga2D
{
	enum EFontSize
	{
		EFontSize_6 = 6,
		EFontSize_8 = 8,
		EFontSize_9 = 9,
		EFontSize_10 = 10,
		EFontSize_11 = 11,
		EFontSize_12 = 12,
		EFontSize_14 = 14,
		EFontSize_18 = 18,
		EFontSize_24 = 24,
		EFontSize_30 = 30,
		EFontSize_36 = 36,
		EFontSize_48 = 48,
		EFontSize_60 = 60,
		EFontSize_72 = 72,
		EFontSize_Count
	};
	class CTextService;
	class CText
	{
	public:
		// If this is the first time creating the text, the text will be loaded in memory, dont do this runtime
		CText(const char* aPathAndName, EFontSize aFontSize = EFontSize_14, unsigned char aBorderSize = 1);
		~CText();
		void Render();
		float GetWidth();
		std::string myText;
		Vector2f myPosition;
		float myScale;
		CColor myColor;
		ESamplerType mySampler;

		std::string myPathAndName;
		std::string myRenderName;
	private:

		CTextService* myTextService;
	};
}

