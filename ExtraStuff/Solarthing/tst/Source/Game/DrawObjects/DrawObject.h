#pragma once
class DrawObject
{
public:
	DrawObject();
	~DrawObject();

	void Init(const std::string & aFilePath);
	void Draw() const;

	void SetSize(const float aSize);
	void SetPosition(const PixelPositionFloat & aPosition);
	void Update(const CU::Time & aDeltaTime);

private:
	HUG::Sprite mySprite;
	PixelPositionFloat myPosition;
};