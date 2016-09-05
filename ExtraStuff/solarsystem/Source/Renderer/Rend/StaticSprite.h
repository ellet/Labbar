#pragma once

#include "Rend/RenderLayerEnum.h"
#include <CU/Vectors/vector2.h>
#include <CU/Vectors/vector4.h>
#include "Rend/RenderData.h"
#include <unordered_map>
#include <CU/Hashing/HashUtility.h>
#pragma warning  (push)
#pragma warning(disable : 4512)

#include <sstream>

class IndexKey
{
public:
	friend std::hash<IndexKey>;
	IndexKey() :myPath(""), myRect(CU::Vector4f::Zero)
	{
	};
	IndexKey(const std::string & aPath, const CU::Vector4f & aRect) :
		myPath(aPath),
		myRect(aRect)
		{}

	bool operator == (const IndexKey & aRight) const
	{
		if ((myRect == aRight.myRect) && (myPath == aRight.myPath))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	std::string GetPath() const
	{
		return  myPath;
	}

	CU::Vector4f GetRect() const
	{
		return myRect;
	}

private:
	std::string myPath;
	CU::Vector4f myRect;
};
#pragma warning (pop)
namespace std {
	template <> struct hash<IndexKey>
	{
		size_t operator()(const IndexKey & aKey) const
		{
			size_t aTempHash = 0;
			CU::hash_combine(aTempHash, aKey.myPath);
			CU::hash_combine(aTempHash, aKey.myRect.x);
			CU::hash_combine(aTempHash, aKey.myRect.y);
			CU::hash_combine(aTempHash, aKey.myRect.z * 10.f);
			CU::hash_combine(aTempHash, aKey.myRect.w * 100.f);
			
			return aTempHash;
		}
	};
}

typedef std::unordered_map<IndexKey, unsigned short> IndexMap;

namespace DX2D
{
	class CSprite;
	class CCustomShader;
}

class RenderCommand;
class RenderConverter;
class Renderer;

class StaticSprite
{
	friend RenderConverter;
	friend Renderer;

public:
	StaticSprite();
	~StaticSprite();

	void Init(const std::string & aFilePath = "Sprites/trashTestFiles/biggerTestTile.png", const CU::Vector4f & aRect = CU::Vector4f::Zero, const CU::Vector2f & aPivotPoint = CU::Vector2f::Zero,const bool aSync = true);
	
	void Draw(const CU::Vector2f & aPositionInPixel) const;
	void DrawWithNormalized(const CU::Vector2f & aNormalizedPosition) const;

	enumRenderLayer GetLayer() const;
	void SetLayer(const enumRenderLayer aRenderLayer);

	
	unsigned short GetImageIndex() const;
	unsigned short AddImage(const std::string& aFilePath, const CU::Vector4f& aRect = CU::Vector4f::One, const CU::Vector2f& aPivotPoint = CU::Vector2f::Zero);
	
	CU::Vector2f GetSizeInPixels() const;

	const CU::Vector4f & GetColor() const;
	void SetColor(const CU::Vector4f & aColor);

	CU::Vector2f GetSizeMultiplier() const;
	void SetSizeMultiplier(const float aMultiplierValue);
	void SetSizeMultiplier(const CU::Vector2f & aMultiplierValue);

	CU::Vector2f GetSize() const;
	
	const CU::Vector2f & GetPivotInPixels() const;

	/*
		Low value gets rendered first.
	*/
	void SetRenderPriority(const float aPriority);
	float GetRenderPriority() const;

	

	DX2D::CSprite * GetSprite() const;

	std::string myShaderName;
	
	
private:
	RenderData myRenderData;
	void SetSizeInPixels(const CU::Vector2f & aSizeInPixels);
	void CalculateSizeOfSprite(const CU::Vector4f & aSpriteCutout = CU::Vector4f::Zero);
	bool CheckIfSpriteExists(unsigned short & aIndexToSet, const std::string & aPath, const CU::Vector4f & aRect = CU::Vector4f::Zero);
	const RenderData & GetRenderData() const;

	static CU::GrowingArray<DX2D::CSprite*> ourSprites;
	
	static IndexMap ourIndexDictionary;

	bool myIsInitiedFlag;
	unsigned short myImageIndex;

	enumRenderLayer myLayer;
	float myPriority;
	

	CU::Vector2f myPositionOffset;
};



inline unsigned short StaticSprite::GetImageIndex() const
{
	return myImageIndex;
}
inline DX2D::CSprite * StaticSprite::GetSprite() const
{
	return ourSprites[myImageIndex];
}


inline enumRenderLayer StaticSprite::GetLayer() const
{
	return myLayer;
}
inline void StaticSprite::SetLayer(const enumRenderLayer aRenderLayer)
{
	myLayer = aRenderLayer;
}


inline const CU::Vector4f & StaticSprite::GetColor() const
{
	return myRenderData.myColor;
}
inline void StaticSprite::SetColor(const CU::Vector4f & aColor)
{
	myRenderData.myColor = aColor;
}

inline const CU::Vector2f & StaticSprite::GetPivotInPixels() const
{
	return myPositionOffset;
}

inline void StaticSprite::SetRenderPriority(const float aPriority)
{
	myPriority = aPriority;
}

inline float StaticSprite::GetRenderPriority() const
{
	return myPriority;
}

inline void StaticSprite::SetSizeMultiplier(const float aMultiplierValue)
{
	myRenderData.mySize = CU::Vector2f(aMultiplierValue, aMultiplierValue);
}

inline void StaticSprite::SetSizeMultiplier(const CU::Vector2f & aMultiplierValue)
{
	myRenderData.mySize = aMultiplierValue;
}

inline CU::Vector2f StaticSprite::GetSizeMultiplier() const
{
	return myRenderData.mySize;
}

typedef StaticSprite SSprite;