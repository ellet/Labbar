#include "stdafx.h"
#include "Tile.h"


Tile::Tile()
{
	myText.SetScale(0.5f);
}


Tile::~Tile()
{
}

void Tile::Render() const
{
	mySprite.Render();
}

void Tile::Render(const std::string & aTextToPrint) const
{
	Render();
	myText.Render(aTextToPrint);
}

unsigned short Tile::GetXIndex() const
{
	return myIndice.x;
}

unsigned short Tile::GetYIndex() const
{
	return myIndice.y;
}

float Tile::GetTileCost() const
{
	return 1.f;
}

void Tile::SetTileData(const TileData & aTileData)
{
	mySprite.Init(aTileData.SpriteFilePath);
}

void Tile::SetPosition(const SB::Vector2f & aPosition)
{
	mySprite.SetPosition(aPosition);
	myText.SetPosition(aPosition - SB::Vector2f(10.f, 0.f));
}

void Tile::SetTileIndiceData(const unsigned short aX, const unsigned short aY)
{
	myIndice = SB::Vector2ui(aX, aY);
}

const SB::Vector2f & Tile::GetPosition() const
{
	return mySprite.GetPosition();
}
