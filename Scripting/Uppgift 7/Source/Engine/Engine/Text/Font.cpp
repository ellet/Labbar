#include "stdafx.h"
#include "Font.h"
#include "Engine\Sprite\SpriteEffect.h"
#include "Engine\Text\Text.h"

#include <Engine\Texture\Texture.h>
#include <Engine\DataParser\DataParser.h>
#include "Engine/Texture/GuiRenderTarget.h"

namespace SB
{

	Font::Font(const std::string &aFontPath) : AsynchronousResource(aFontPath)
	{
	}


	Font::Font() : Font("text")
	{
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

	void Font::RenderText(const GuiRenderTarget & aRenderTarget, const Text &aText)
	{
		Prepare(false);
		mySprite->SetColor(myFontColor);
		Vector2f position(aText.GetPosition());
		Vector2f scale = aText.GetScale();
		Vector2f bearing;
		Vector2f renderPosition;
		char charToRender;

		for (unsigned short i = 0; i < aText.GetLastCharacterToRender()+1; ++i)
		{
			/*if (position.x > aText.GetMaxPosition().x
				&& aText.GetMaxPosition().x > 0)
			{
				charToRender = '\n';
				i--;
			}
			else
			{
			}
			*/
			charToRender = aText.GetText()[i];

			if (charToRender == '\0')
			{
				break;
			}

			if (HandleSpecialCharacter(charToRender, position, aText.GetPosition()))
			{
				continue;
			}

			bearing = (MetricBearingInfo(charToRender)) * scale;
			renderPosition = position + bearing;
			UpdateSprite(charToRender, renderPosition, scale);
			aRenderTarget.Render(*mySprite);

			position.x += MetricsInfo(charToRender).horiAdvance * scale.x;
		}
	}

	void Font::CalculateMaxHeight()
	{
		if (myCharacterMaxHeight == 0)
		{
			myCharacterMaxHeight = GetMaxHeight();
		}
	}

	float Font::GetMaxHeight() const
	{
		const_cast<Font*>(this)->Prepare(false);
		float size = 0;

		for (char i = 0; i < myLetterMetricsInfo.Size(); ++i)
		{
			float characterHeight = 64 * myLetterMetricsInfo[i].scale.y;
			if (size < characterHeight)
			{
				size = characterHeight;
			}
		}
		return size;
	}

	Vector2f Font::GetSizeOfText(const Text &aText) const
	{
		const_cast<Font*>(this)->Prepare(false);

		Vector2f size(0.f, 0.f);
		Vector2f scale = aText.GetScale();

		unsigned short aRowAmount = 1;
		char currentChar;
		for (size_t i = 0; i < aText.GetText().size(); ++i)
		{
			currentChar = aText.GetText()[i];

			if (HandleSpecialCharacter(currentChar, size, aText.GetPosition()))
			{
				aRowAmount++;
				continue;
			}

			size.x += MetricsInfo(currentChar).horiAdvance * scale.x;
		}
		size.y = myCharacterMaxHeight * aRowAmount;

		return size;
	}

	void Font::Reload()
	{
		myCharacterMaxHeight = 0;
		myCharacterStart = 32;
		myCharacterAtlas.Resize(95);
		myLetterMetricsInfo.Resize(95);
		myFontColor = Vector4f(1.f, 1.f, 1.f, 1.f);
		mySprite = std::make_unique<Sprite>();

		std::shared_ptr<Texture> texture = Engine::GetResourceManager().Get<Texture>(GetPath() + "\\textAtlas.dds");

		texture->Prepare(false);
		mySprite->SetTexture(texture);
		mySprite->SetEffect(std::make_shared<SpriteEffect>("shaders/sprite/font.fx", "VShader", "shaders/sprite/font.fx", "PShader"));

		InitTexCoords(GetPath().c_str());
		InitMetrics(GetPath().c_str());

		//GetMaxHeight();
	}

	void Font::Load()
	{
		Reload();
	}

	bool Font::HandleSpecialCharacter(char charToRender, Vector2f &position, const Vector2f &aTextOrigin) const
	{
		if (charToRender == '\n')
		{
			position.y += myCharacterMaxHeight;
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
		mySprite->SetColor(myFontColor);
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

	const Vector2f & Font::MetricScaleInfo(char aCharacter) const
	{
		return MetricsInfo(aCharacter).scale;
	}

	const Vector2f & Font::MetricBearingInfo(char aCharacter) const
	{
		return MetricsInfo(aCharacter).horizontalBearing;
	}

	const TextureRect & Font::AtlasInfo(char aCharacter) const
	{
		return myCharacterAtlas[ToArray(aCharacter)];
	}

	const SB::LetterMetricsInfo & Font::MetricsInfo(char aCharacter) const
	{
		return myLetterMetricsInfo[ToArray(aCharacter)];
	}

	unsigned char Font::ToArray(unsigned char aCharacter) const
	{
		unsigned char returnValue = aCharacter - myCharacterStart;
		return returnValue;
	}

};