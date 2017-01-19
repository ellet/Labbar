#pragma once
#include "Utilities\Math\Vector2.h"

class BDSprite
{
public:
	friend class BDRenderer;

	BDSprite();
	~BDSprite();

	void Init(const std::string & aFilePath);
	void Render() const;

	void SetPosition(const SB::Vector2f & aPosition);
	const SB::Vector2f & GetPosition() const;

private:
	std::string myFilePath;
	unsigned short mySpriteIndex;
	SB::Vector2f myPosition;
	SB::Vector2f myOrigin;
};

