#include "stdafx.h"
#include "FontLoader.h"
#include "Font.h"

namespace SB
{
	Font * ResourceLoader<Font>::Load(const std::string& aPath, LoadError& aError)
	{
		return new Font(aPath);
	}
}
