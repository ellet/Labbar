#pragma once
#include "Utilities\Math\Vector2.h"
#include "Utilities\Color\Color.h"

class BDSprite
{
public:
	friend class BDRenderer;

	BDSprite();
	~BDSprite();

	void Init(const std::string & aFilePath);
	void Render() const;

	void SetColor(const SB::Color & aColor);

	void SetPosition(const SB::Vector2f & aPosition);
	const SB::Vector2f & GetPosition() const;

private:
	SB::Color myColor;
	std::string myFilePath;
	unsigned short mySpriteIndex;
	SB::Vector2f myPosition;
	SB::Vector2f myOrigin;
};

