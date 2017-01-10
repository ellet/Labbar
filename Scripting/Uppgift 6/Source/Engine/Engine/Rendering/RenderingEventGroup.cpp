#include "stdafx.h"
#include "RenderingEventGroup.h"
#include <d3d11_1.h>

namespace SB
{
	void RenderingEvent(const wchar_t* aEventDescription)
	{
		Engine::GetRenderer().GetAnnotationWriter()->SetMarker(aEventDescription);
	}

	RenderingEventGroup::RenderingEventGroup(const wchar_t* aEventDescription)
	{
		Engine::GetRenderer().GetAnnotationWriter()->BeginEvent(aEventDescription);
	}

	RenderingEventGroup::~RenderingEventGroup()
	{
		Engine::GetRenderer().GetAnnotationWriter()->EndEvent();
	}
}
