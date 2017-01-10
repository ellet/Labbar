#pragma once

namespace SB
{
	void RenderingEvent(const wchar_t* aEventDescription);

	class RenderingEventGroup
	{
	public:
		RenderingEventGroup(const wchar_t* aEventDescription);
		~RenderingEventGroup();
	};
}
