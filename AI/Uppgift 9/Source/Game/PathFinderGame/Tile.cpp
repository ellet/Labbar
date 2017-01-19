#include "stdafx.h"
#include "Tile.h"


Tile::Tile()
{
}


Tile::~Tile()
{
}

void Tile::Render() const
{
	mySprite.Render();
}

void Tile::SetTileData(const TileData & aTileData)
{
	mySprite.Init(aTileData.SpriteFilePath);
}

void Tile::SetPosition(const SB::Vector2f & aPosition)
{
	mySprite.SetPosition(aPosition);
}

const SB::Vector2f & Tile::GetPosition() const
{
	return mySprite.GetPosition();
}
