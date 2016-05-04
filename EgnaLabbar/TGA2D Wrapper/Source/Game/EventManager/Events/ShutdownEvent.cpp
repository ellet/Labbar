#include "stdafx.h"
#include "ShutdownEvent.h"

#include <tga2d/engine.h>

ShutdownEvent::ShutdownEvent()
{
	myName = "ShutdownEvent";
	myIsActive = true;
}
ShutdownEvent::~ShutdownEvent()
{
}

void ShutdownEvent::OneShotEvent()
{
	DX2D::CEngine::GetInstance()->Shutdown();
}
