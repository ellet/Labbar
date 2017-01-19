#pragma once
#include "Rendering\BDText.h"

struct TileData
{
	std::string SpriteFilePath;

};

class Tile
{
public:
	Tile();
	~Tile();

	void Render() const;
	void Render(const std::string & aTextToPrint) const;

	unsigned int GetXIndex() const;
	unsigned int GetYIndex() const;

	float GetTileCost() const;

	void PathReset();
	void FlagAsPath();

	void SetTileData(const TileData & aTileData);
	void SetPosition(const SB::Vector2f & aPosition);
	void SetTileIndiceData(const unsigned short aX, const unsigned short aY);
	const SB::Vector2f & GetPosition() const;

private:
	BDText myText;
	BDSprite mySprite;
	SB::Vector2f myPosition;
	SB::Vector2ui myIndice;
};

