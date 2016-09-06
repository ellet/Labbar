/*
This class handles all texts that will be rendered, don't use this to show text, only use the CText class
*/

#pragma once

#define FONT_BUFF_SIZE 4096

#include "text/fontfile.h"
#include "math/color.h"
#include "arrays/simple_pointer_array.h"
#include <unordered_map>




namespace Tga2D
{
	struct SCharData
	{
		Tga2D::Vector2<float> myTopLeftUV;
		Tga2D::Vector2<float> myBottomRightUV;

		short myWidth;
		short myHeight;
		short myAdvanceX; //Distance to next character.
		short myBearingX;
		short myBearingY;
		char myChar;
	};

	struct STextToRender
	{
		Vector2f mySize;
		Vector2f myUV;
		Vector2f uvScale;
		Vector2f myPosition;
		CColor myColor;
	};
	class SFontData
	{
	public:
		SFontData()
		{
			myBufferedObjects.Init(FONT_BUFF_SIZE + 1);
			for (int i = 0; i < myBufferedObjects.TotalCount(); i++)
			{
				STextToRender *text = new STextToRender();
				myBufferedObjects.myData[i] = text;
			}
		}
		~SFontData();
		std::unordered_map<char, SCharData> myCharData;
		unsigned int myAtlasWidth;
		unsigned int myAtlasHeight;
		float myLineSpacing;
		unsigned int myWordSpacing;
		unsigned int myFontHeightWidth;
		int* myAtlas;
		std::string myName;
		CSpriteBatch* myBatch;
		SSimplePointerArray<STextToRender*> myBufferedObjects;

		ID3D11ShaderResourceView* myAtlasView;
	};


	struct TextVertexNew
	{
		TextVertexNew(){ myPosition.Set(0, 0); myTexCoord.Set(0, 0); }
		TextVertexNew(Vector2f aPos, Vector2f aTexCoord, Vector4f color = Vector4f(1, 1, 1, 1))
		{
			myPosition = aPos;
			myTexCoord = aTexCoord;
			myColor = color;
		}
		Vector2f myPosition;
		Vector2f myTexCoord;
		Vector4f myColor;
	};

	class CSpriteBatch;
	class CTexture;
	class CSprite;
	class CText;
	class CTextService
	{
		struct SText
		{
			std::string myText;
			std::string myName;
			Vector2f myPosition;
			float mySize;
			CColor myColor;
		};
	public:
		CTextService();
		~CTextService();

		void Init();
		
		//void Render();

		void Update();

		void InitAndLoad(std::string aFontPathAndName, unsigned char aBorderSize, int aSize);
		bool AddTextToRender(const std::string& aText, const Vector2f& aPosition, CColor aColor, float aSize, const std::string& aName, ESamplerType aSamplerType);
		float GetSentenceWidth(Tga2D::CText* aText);
		std::string GetRenderName(std::string aFontPathAndName, enum EFontSize aSize);

		void ClearMemory(std::string aRenderName);
	private:
		bool UpdateTextAndDraw(const std::string& aText, const Vector2f& aPosition, CColor aColor, float aSize, const std::string& aName, ESamplerType aSamplerType);

		void BuildText(const std::string& aText, const Vector2f& aPosition, CColor aColor, float aSize, const std::string& aName, SSimplePointerArray<STextToRender*>& aTextBuffer);
		void InitTexture();
		
		float minS;
		float minT;
		float maxS;
		float maxT;
		int currentFontChar;

		SSimplePointerArray<SText*> myTextsToRender;
		int myCurrentSprite;
		std::vector<Tga2D::CSprite*> mySprites;


	/*	class SFontData
		{
		public:
			SFontData()
			{ 
				myBufferedObjects.Init(FONT_BUFF_SIZE + 1); 
				for (int i = 0; i < myBufferedObjects.TotalCount(); i++)
				{
					STextToRender *text = new STextToRender();
					myBufferedObjects.myData[i] = text;
				}
			}
			~SFontData()
			{
				for (int i = 0; i < myBufferedObjects.TotalCount(); i++)
				{
					delete myBufferedObjects.myData[i];
				}
			}
			std::vector<fontChar> myFontChars;
			CSpriteBatch* myBatch;
			CTexture* myTexture;
			//STextToRender myTextBuffer[FONT_BUFF_SIZE];


			SSimplePointerArray<STextToRender*> myBufferedObjects;
		};*/

	//	std::map<std::string, SFontData*> myFontDatas;
		unsigned int myTextsToDraw;

		struct FT_LibraryRec_* myLibrary;

		void LoadGlyph(int index, int& atlasX, int& atlasY, int& maxY
			, float atlasWidth, float atlasHeight, SFontData* aFontData, struct FT_FaceRec_* aFace, int aBorderWidth = 0);

		void LoadOutline(const int index, const int atlasX, const int atlasY
			, const float atlasWidth, SFontData* aFontData, struct FT_FaceRec_* aFace, int aBorderWidth);



		void CalculateOutlineOffsets(const int index, struct FT_FaceRec_* aFace, int aBorderWidth);
		void CalculateGlyphOffsets(const int index, struct FT_GlyphSlotRec_* glyph);

		struct SCountData
		{
			int xNCount = 0;
			int xPCount = 0;
			int yNCount = 0;
			int yPCount = 0;
		};

		void CountOffsets(const int& x, const int& y, const int& width, const int& height, SCountData& countData);
		void CountDeltas(const int& width, const int& height, int& deltaX, int& deltaY, SCountData& countData);
		struct SOutlineOffset
		{
			int xDelta = 0;
			int yDelta = 0;

		} myOffset;

		std::unordered_map<std::string, SFontData*> myFontData;
		
	};
}