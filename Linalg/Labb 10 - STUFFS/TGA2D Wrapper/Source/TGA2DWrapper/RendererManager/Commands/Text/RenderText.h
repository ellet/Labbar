#pragma once

#include <string>

#include <GrowingArray\GrowingArray.h>

class RenderText
{
public:

	RenderText();
	RenderText(const std::string &aText);
	~RenderText();

	void Render() const;

	inline void SetText(const std::string &aText);
	inline const std::string& GetText() const;

private:

	const std::string *myText;

};

inline void RenderText::SetText(const std::string &aText)
{
	myText = &aText;
}
inline const std::string& RenderText::GetText() const
{
	return *myText;
}
