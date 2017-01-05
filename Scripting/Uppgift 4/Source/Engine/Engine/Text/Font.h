#pragma once

namespace SB
{
	class GuiRenderTarget;
	class Sprite;
	class Text;

	struct TextureRect
	{
		Vector2f position;
		Vector2f size;
	};

	struct LetterMetricsInfo
	{
		Vector2f scale;
		Vector2f horizontalBearing;
		float horiAdvance;
		float vertBearingX;
		float vertBearingY;
		float vertAdvance;
	};

	class Font : public AsynchronousResource
	{
	public:
		Font(const std::string &aFontPath);
		Font();
		~Font();
		void RenderText(const GuiRenderTarget & aRenderTarget, const Text &aText);

		void CalculateMaxHeight();
		float GetMaxHeight()const;
		Vector2f GetTextWidth(const char *aText)const;
		Vector2f GetSizeOfText(const Text &aText)const;

		inline void SetFontColor(const Vector4f& aColor)
		{
			myFontColor = aColor;
		}
		inline const Vector4f& GetColor() const
		{
			return myFontColor;
		}

		virtual void Reload() override;


		virtual void Load() override;

	private:

		void InitTexCoords(const char *aFontPath);
		void InitMetrics(const char *aFontPath);
		bool HandleSpecialCharacter(char charToRender, Vector2f &position, const Vector2f &aTextOrigin)const;
		bool IsSpecialCharacter(char charToRender);
		void UpdateSprite(char charToRender, const Vector2f &renderPosition, const Vector2f &scale);

		Vector2f GetOrigin(char aCharacter);
		const Vector2f & AtlasPosInfo(char aCharacter);
		const Vector2f & AtlasSizeInfo(char aCharacter);
		const Vector2f & MetricScaleInfo(char aCharacter)const;
		const Vector2f &MetricBearingInfo(char aCharacter)const;
		const TextureRect &AtlasInfo(char aCharacter)const;
		const LetterMetricsInfo &MetricsInfo(char aCharacter)const;

		unsigned char ToArray(unsigned char aCharacter)const;


		std::unique_ptr< Sprite > mySprite;
		GrowingArray<TextureRect, unsigned char> myCharacterAtlas;
		GrowingArray<LetterMetricsInfo, unsigned char> myLetterMetricsInfo;
		Vector4f myFontColor;

		float myCharacterMaxHeight;
		unsigned char myCharacterStart;
	};

};