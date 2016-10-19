#include "stdafx.h"
#include "Font.h"
#include "Engine\Sprite\SpriteEffect.h"
#include "Engine\Text\Text.h"

#include <Engine\Texture\Texture.h>
#include <Engine\DataParser\DataParser.h>
namespace ENGINE_NAMESPACE
{

	Font::Font(const char *aFontPath)
	{
		myCharacterStart = 32;
		aFontPath;
		myCharacterAtlas.Resize(95);
		myLetterMetricsInfo.Resize(95);
		mySprite = std::make_unique<Sprite>();
		mySprite->SetTexture(std::make_shared< Texture>(std::string(aFontPath) + "\\textAtlas.dds"));
		mySprite->SetEffect(std::make_shared< SpriteEffect>("shaders/sprite/sprite.fx", "VShader", "shaders/sprite/font.fx", "PShader"));

		InitTexCoords(aFontPath);
		InitMetrics(aFontPath);

	}


	Font::Font()
	{
		myCharacterStart = 32;

		mySprite = std::make_unique<Sprite>();
		mySprite->SetTexture(std::make_shared< Texture>("text\\textAtlas.dds"));


		mySprite->SetEffect(std::make_shared< SpriteEffect>("shaders/sprite/sprite.fx", "VShader", "shaders/sprite/font.fx", "PShader"));

		InitTexCoords("text");
		InitMetrics("text");
	}

	void Font::InitTexCoords(const char *aFontPath)
{
		DataDocument atlasInfo;
		DataParser::Open(std::string(aFontPath) + "\\texCoords.json", atlasInfo);
		unsigned char amountLetters = static_cast<unsigned char> (atlasInfo.Size());
		myCharacterAtlas.Resize(amountLetters);
		for (unsigned int i = 0; i < amountLetters; ++i)
		{
			unsigned char target = static_cast<unsigned char> (atlasInfo[i]["character"].GetInt());
			myCharacterAtlas[ToArray(target)].position = Vector2f(atlasInfo[i]["x"].GetFloat(), atlasInfo[i]["y"].GetFloat());
			myCharacterAtlas[ToArray(target)].size = Vector2f(atlasInfo[i]["width"].GetFloat(), atlasInfo[i]["height"].GetFloat());
		}
	}

	void Font::InitMetrics(const char *aFontPath)
{
		DataDocument metricsInfo;
		DataParser::Open(std::string(aFontPath) + "\\glyphMetrics.json", metricsInfo);

		unsigned char amountLetters = static_cast<unsigned char> (metricsInfo.Size());
		myLetterMetricsInfo.Resize(amountLetters);

		for (unsigned int i = 0; i < amountLetters; ++i)
		{
			unsigned char character = static_cast<unsigned char> (metricsInfo[i]["character"].GetInt());

			myLetterMetricsInfo[ToArray(character)].scale = Vector2f( 1.f /metricsInfo[i]["width"].GetFloat(), 1.f / metricsInfo[i]["height"].GetFloat());
			myLetterMetricsInfo[ToArray(character)].horizontalBearing = Vector2f(-metricsInfo[i]["horizontalBearingX"].GetFloat(), metricsInfo[i]["horizontalBearingY"].GetFloat());
			myLetterMetricsInfo[ToArray(character)].horiAdvance = metricsInfo[i]["horizontalAdvance"].GetFloat();
			//myLetterMetricsInfo[ToArray(character)].vertBearingX = verticalBearingX;
			//myLetterMetricsInfo[ToArray(character)].vertBearingY = verticalBearingY;
			//myLetterMetricsInfo[ToArray(character)].vertAdvance = verticalAdvance;
		}
	}

	Font::~Font()
	{
	}

	void Font::RenderText(const Text &aText)
	{
		Vector2f position(aText.GetPosition());
		Vector2f scale = aText.GetScale();
		Vector2f bearing;
		Vector2f renderPosition;
		char charToRender;

		for (size_t i = 0; i < aText.GetText().size(); ++i)
		{
			charToRender = aText.GetText()[i];

			if (HandleSpecialCharacter(charToRender, position, aText.GetPosition()))
			{
				continue;
			}

			bearing = (MetricBearingInfo(charToRender)) * scale;
			renderPosition = position + bearing;
			UpdateSprite(charToRender, renderPosition, scale);
			mySprite->Render();

			position.x += MetricsInfo(charToRender).horiAdvance * scale.x;
		}
	}

	Vector2f Font::GetSizeOfText(const Text &aText)
	{
		float rowHeight = 0.f;
		Vector2f size(0.f, 0.f);
		Vector2f scale = aText.GetScale();

		char currentChar;
		for (size_t i = 0; i < aText.GetText().size(); ++i)
		{
			currentChar = aText.GetText()[i];

			if (HandleSpecialCharacter(currentChar, size, aText.GetPosition()))
			{
				size.y += rowHeight;
				rowHeight = 0.f;
				continue;
			}

			float characterHeight = 64 * MetricScaleInfo(currentChar).y;
			if (rowHeight < characterHeight)
			{
				rowHeight = characterHeight;
			}

			

			size.x += MetricsInfo(currentChar).horiAdvance * scale.x;
		}
		size.y += rowHeight;

		return size;
	}

	bool Font::HandleSpecialCharacter(char charToRender, Vector2f &position, const Vector2f &aTextOrigin)
	{
		if (charToRender == '\n')
		{
			position.y += 64.f;
			position.x = aTextOrigin.x;
			return true;
		}
		return false;
	}

	bool Font::IsSpecialCharacter(char charToRender)
	{
		if (charToRender == '\n')
		{
			return true;
		}
		return false;
	}

	void Font::UpdateSprite(char aCharToRender, const Vector2f &aRenderPosition, const Vector2f &aScale)
	{
		if (IsSpecialCharacter(aCharToRender))
		{
			return;
		}

		mySprite->SetTextureRect(AtlasPosInfo(aCharToRender), AtlasSizeInfo(aCharToRender));
		mySprite->SetPosition(aRenderPosition);
		mySprite->SetOrigin(GetOrigin(aCharToRender) * aScale);
		mySprite->SetScale((MetricScaleInfo(aCharToRender) * aScale));
	}

	Vector2f Font::GetOrigin(char aCharacter)
	{
		return Vector2f(0.f, AtlasSizeInfo(aCharacter).x) * MetricScaleInfo(aCharacter);
	}

	const Vector2f & Font::AtlasPosInfo(char aCharacter)
	{
		return AtlasInfo(aCharacter).position;
	}

	const Vector2f & Font::AtlasSizeInfo(char aCharacter)
	{
		return AtlasInfo(aCharacter).size;

	}

	const Vector2f &Font::MetricScaleInfo(char aCharacter)
	{
		Vector2f ret = MetricsInfo(aCharacter).scale;
		ret;
		return MetricsInfo(aCharacter).scale;
	}

	const Vector2f & Font::MetricBearingInfo(char aCharacter)
	{
		return MetricsInfo(aCharacter).horizontalBearing;
	}

	const TextureRect &Font::AtlasInfo(char aCharacter)
	{
		return myCharacterAtlas[ToArray(aCharacter)];
	}

	const LetterMetricsInfo &Font::MetricsInfo(char aCharacter)
	{
		return myLetterMetricsInfo[ToArray(aCharacter)];
	}

	unsigned char Font::ToArray(unsigned char aCharacter)
	{
		unsigned char returnValue = aCharacter - myCharacterStart;
		return returnValue;
	}

};