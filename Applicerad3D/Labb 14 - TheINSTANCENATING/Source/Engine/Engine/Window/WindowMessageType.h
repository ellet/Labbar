#pragma once
#include "Engine\Size.h"
#include "FileDropping\FileExtensions.h"

namespace ENGINE_NAMESPACE
{
	enum class WindowMessageType
	{
		eUnknown,
		eCloseButtonPressed,
		eResizeBegins,
		eResizeEnds,
		eSizeChanged,
		ePaint,
		eCreate,
		eDestroy,
		eKeyDown,
		eKeyUp,

		eMouseMove,
		eMouseButtonDown,
		eMouseButtonUp,
		
		eFileDrop,

		eCount,
	};

	struct SizeChangedData
	{
		Size<int> newSize;
	};

	struct KeyData
	{
		KeyboardKey key;
		int repeatCount;
	};

	struct MouseData
	{
		MouseButton button;
		int x;
		int y;
		int deltaX;
		int deltaY;
	};

	struct FiledDroppedOnWindow
	{
		FileExtensionsEnum myFileExtension;
		std::string * myFilePath;
	};
}
