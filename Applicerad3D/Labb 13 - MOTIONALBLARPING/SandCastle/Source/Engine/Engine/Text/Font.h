#pragma once



namespace ENGINE_NAMESPACE
{
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

	class Font
	{
	public:
		Font(const char *aFontPath);
		Font();
		~Font();
		void RenderText(const Text &aText);

		Vector2f GetSizeOfText(const Text &aText);

	private:

		void InitTexCoords(const char *aFontPath);
		void InitMetrics(const char *aFontPath);
		bool HandleSpecialCharacter(char charToRender, Vector2f &position, const Vector2f &aTextOrigin);
		bool IsSpecialCharacter(char charToRender);
		void UpdateSprite(char charToRender, const Vector2f &renderPosition, const Vector2f &scale);

		Vector2f GetOrigin(char aCharacter);
		const Vector2f & AtlasPosInfo(char aCharacter);
		const Vector2f & AtlasSizeInfo(char aCharacter);
		const Vector2f & MetricScaleInfo(char aCharacter);
		const Vector2f &MetricBearingInfo(char aCharacter);
		const TextureRect &AtlasInfo(char aCharacter);
		const LetterMetricsInfo &MetricsInfo(char aCharacter);

		unsigned char ToArray(unsigned char aCharacter);


		std::unique_ptr< Sprite > mySprite;
		GrowingArray<TextureRect, unsigned char> myCharacterAtlas;
		GrowingArray<LetterMetricsInfo, unsigned char> myLetterMetricsInfo;

		unsigned char myCharacterStart;
	};

};