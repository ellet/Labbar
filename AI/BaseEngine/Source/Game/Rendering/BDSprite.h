#pragma once
class BDSprite
{
public:
	friend class BDRenderer;

	BDSprite();
	~BDSprite();

	void Init(const std::string & aFilePath);
	void Render();

	void SetPosition(const SB::Vector2f & aPosition);

private:
	std::string myFilePath;
	SB::Vector2f myPosition;
};

