#pragma once
#include "HUGRender/SpriteData.h"

namespace HUG
{

	class Sprite
	{
	public:
		Sprite();
		~Sprite();

		void Init(const std::string & aFilepath);

		void Draw(const CU::Vector2f & aPosition) const;

		void SetPivot(const CU::Vector2f & aPivotPosition);
		void SetRotationDegrees(const float aRotationInDegrees);
		void SetRotationRadians(const float aRotationInRadians);
		void SetSize(const float aSize);
		//void SetColor();

		unsigned short GetIndex() const;

	private:
		SpriteData mySpriteData;

		unsigned short myIndex;
	};

}