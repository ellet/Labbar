#include "RenderText.h"

RenderText::RenderText()
	:myText(nullptr)
{
}
RenderText::RenderText(const std::string &aText)
	: myText(&aText)
{
}
RenderText::~RenderText()
{
}

void RenderText::Render() const
{

}
