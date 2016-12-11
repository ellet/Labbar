#include "stdafx.h"
#include "Engine\FileWatcher\FileChangedEvent.h"

namespace SB
{
	FileChangedEvent::FileChangedEvent(const std::string &aPath)
	{
		myPath = aPath;
	}

	FileChangedEvent::~FileChangedEvent()
	{
	}
}
