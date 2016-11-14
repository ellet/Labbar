#pragma once
#include "Engine\Window\WindowMessageType.h"

namespace ENGINE_NAMESPACE
{
	union WindowMessageData
	{
		SizeChangedData resizeEvent;
		KeyData keyEvent;
		MouseData mouseEvent;
		FiledDroppedOnWindow FileDropEvent;

		inline WindowMessageData();
		inline ~WindowMessageData();
	};

	inline WindowMessageData::WindowMessageData()
	{
		memset(this, 0, sizeof(*this));
	}

	inline WindowMessageData::~WindowMessageData()
	{
	}

	struct WindowMessage
	{
		WindowMessageType type;
		WindowMessageData data;
	};
}
