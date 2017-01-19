#pragma once



class BDText
{
public:
	friend class BDTextRenderer;

	BDText();
	~BDText();

	void Render() const;
	void Render(const std::string & aText) const;

	void SetScale(const float aScale);
	void SetText(const std::string & aString);
	void SetPosition(const SB::Vector2f & aPosition);

private:
	std::string myText;
	float myScale;
	SB::Vector2f myPosition;
};

