#pragma once

class ShapeContainer;

namespace ModelStuff
{
	std::string GetWord(const std::string &aStr, int& aStartIndex);

	void LoadModel(const std::string &aFile, ShapeContainer& aModel);
}

