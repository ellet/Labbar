#pragma once

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

	void SetTileData(const TileData & aTileData);
	void SetPosition(const SB::Vector2f & aPosition);
	const SB::Vector2f & GetPosition() const;

private:
	BDSprite mySprite;
	SB::Vector2f myPosition;
};

