#pragma once

namespace DX2D
{
	class CSprite;
}



namespace HUG
{

	class TextureManager
	{
	public:
		TextureManager();
		~TextureManager();


		void Init(const unsigned short aInitNumber = 1024);

		unsigned short AddTexture(const std::string & aFilePath);
		DX2D::CSprite * GetTexture(const unsigned short aIndex);

	private:
		CU::GrowingArray<DX2D::CSprite*> mySprites;


	};

}