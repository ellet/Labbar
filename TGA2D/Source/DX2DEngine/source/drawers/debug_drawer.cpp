#include "stdafx.h"

#include "drawers/debug_drawer.h"
#include "drawers/debug_performancegraph.h"
#include "primitives/line_primitive.h"
#include "text/Text.h"
#include "engine.h"
#include "d3d/direct_3d.h"
#include "sprite/sprite.h"

#include <windows.h>
#include <stdio.h>
#include <psapi.h>

#pragma comment(lib, "psapi.lib")

using namespace Tga2D;

CDebugDrawer::CDebugDrawer(int aFlagset)
	:myNumberOfRenderedLines(0)
	,myMaxLines(10000)
{
	myDebugFeatureSet = aFlagset;
	tickindex = 0;
	ticksum = 0;
	myRealFPS = 0;
}


CDebugDrawer::~CDebugDrawer(void)
{
	for (int i=0; i< myMaxLines; i++)
	{
		delete myLineBuffer[i];
	}
	myLineBuffer.clear();
	delete myFPS;
	delete myMemUsage;
	delete myDrawCallText;
	delete myCPUText;
	delete myPerformanceGraph;
	delete myLineMultiBuffer;
	delete myErrorsText;
}

void CDebugDrawer::Init()
{
	for (int i=0; i< myMaxLines; i++)
	{
		LinePrimitive* newLine = new LinePrimitive();
		myLineBuffer.push_back(newLine);
	}

	const float theSize = 1.0f;
	myFPS = new Tga2D::CText("Text/BOMBARD_.ttf", EFontSize_14);
	myFPS->myText = "--";
	myFPS->myPosition = Tga2D::Vector2f(0, 0.02f);
	myFPS->myColor.Set(1, 1, 1, 1.0f);
	myFPS->myScale = theSize;

	myMemUsage = new Tga2D::CText("Text/BOMBARD_.ttf");
	myMemUsage->myText = "--";
	myMemUsage->myPosition = Tga2D::Vector2f(0.0f, 0.05f);
	myMemUsage->myColor.Set(1, 1, 1, 1.0f);
	myMemUsage->myScale = theSize;

	myDrawCallText = new Tga2D::CText("Text/BOMBARD_.ttf");
	myDrawCallText->myText = "--";
	myDrawCallText->myPosition = Tga2D::Vector2f(0.0f, 0.08f);
	myDrawCallText->myColor.Set(1, 1, 1, 1.0f);
	myDrawCallText->myScale = theSize;

	myCPUText = new Tga2D::CText("Text/BOMBARD_.ttf");
	myCPUText->myText = "--";
	myCPUText->myPosition = Tga2D::Vector2f(0.0f, 0.11f);
	myCPUText->myColor.Set(1, 1, 1, 1.0f);
	myCPUText->myScale = theSize;

	myErrorsText = new Tga2D::CText("Text/BOMBARD_.ttf");
	myErrorsText->myText = "--";
	myErrorsText->myPosition = Tga2D::Vector2f(0.0f, 0.14f);
	myErrorsText->myColor.Set(1, 0.7f, 0.7f, 1.0f);
	myErrorsText->myScale = theSize;

	myErrorSprite = new CSprite("sprites/error.dds");
	myErrorSprite->SetPosition(Tga2D::Vector2f(0.9f, 0.0f));
	myErrorSprite->SetPivot(Tga2D::Vector2f(0.5f, 0.0f));
	myShowErrorTimer = 0.0f;


	myPerformanceGraph = new CPerformanceGraph(this);
	Tga2D::CColor bgColor(0, 1, 0, 0.4f);
	Tga2D::CColor lineColro(1, 1, 1, 1.0f);
	myPerformanceGraph->Init(bgColor, lineColro, "FPS spike detector");

	myLineMultiBuffer = new CLineMultiPrimitive();
}


ULONGLONG FixCPUTimings(const FILETIME &a, const FILETIME &b)
{
	LARGE_INTEGER la, lb;
	la.LowPart = a.dwLowDateTime;
	la.HighPart = a.dwHighDateTime;
	lb.LowPart = b.dwLowDateTime;
	lb.HighPart = b.dwHighDateTime;

	return la.QuadPart - lb.QuadPart;
}

float GetCPUUsage(FILETIME *prevSysKernel, FILETIME *prevSysUser,
	FILETIME *prevProcKernel, FILETIME *prevProcUser,
	bool firstRun = false)
{
	FILETIME sysIdle, sysKernel, sysUser;
	FILETIME procCreation, procExit, procKernel, procUser;

	if (!GetSystemTimes(&sysIdle, &sysKernel, &sysUser) ||
		!GetProcessTimes(GetCurrentProcess(), &procCreation, &procExit, &procKernel, &procUser))
	{
		// can't get time info so return
		return -1.;
	}

	// check for first call
	if (firstRun)
	{
		// save time info before return
		prevSysKernel->dwLowDateTime = sysKernel.dwLowDateTime;
		prevSysKernel->dwHighDateTime = sysKernel.dwHighDateTime;

		prevSysUser->dwLowDateTime = sysUser.dwLowDateTime;
		prevSysUser->dwHighDateTime = sysUser.dwHighDateTime;

		prevProcKernel->dwLowDateTime = procKernel.dwLowDateTime;
		prevProcKernel->dwHighDateTime = procKernel.dwHighDateTime;

		prevProcUser->dwLowDateTime = procUser.dwLowDateTime;
		prevProcUser->dwHighDateTime = procUser.dwHighDateTime;

		return -1.;
	}

	ULONGLONG sysKernelDiff = FixCPUTimings(sysKernel, *prevSysKernel);
	ULONGLONG sysUserDiff = FixCPUTimings(sysUser, *prevSysUser);

	ULONGLONG procKernelDiff = FixCPUTimings(procKernel, *prevProcKernel);
	ULONGLONG procUserDiff = FixCPUTimings(procUser, *prevProcUser);

	ULONGLONG sysTotal = sysKernelDiff + sysUserDiff;
	ULONGLONG procTotal = procKernelDiff + procUserDiff;

	return (float)((100.0 * procTotal) / sysTotal);
}


const int CONVERSION_VALUE = 1024;
void CDebugDrawer::Update(float aTimeDelta)
{
	if (!myDebugFeatureSet)
	{
		return;
	}

	std::string fpsText;
	
	fpsText.append("FPS: ");

	myRealFPS = static_cast<unsigned short>(1.0f / aTimeDelta);

	myPerformanceGraph->FeedValue(myRealFPS);

	fpsText.append(std::to_string(myRealFPS));
	myFPS->myText = fpsText;

	PROCESS_MEMORY_COUNTERS memCounter;
	BOOL result = GetProcessMemoryInfo(GetCurrentProcess(),
		&memCounter,
		sizeof(memCounter));

	if (!result)
	{
		return;
	}

	int memUsed = static_cast<int>(memCounter.WorkingSetSize) / 1024;
	int memUsedMb = static_cast<int>(memCounter.WorkingSetSize) / 1024 / 1024;
	myMemUsage->myText.clear();
	myMemUsage->myText.append("Mem: ");
	myMemUsage->myText.append(std::to_string(memUsed));
	myMemUsage->myText.append("Kb (");
	myMemUsage->myText.append(std::to_string(memUsedMb));
	myMemUsage->myText.append("Mb)");

	static FILETIME prevSysKernel, prevSysUser;
	static FILETIME prevProcKernel, prevProcUser;
	float usage = 0.0;

	// first call
	static bool firstTime = true;
	usage = GetCPUUsage(&prevSysKernel, &prevSysUser, &prevProcKernel, &prevProcUser, firstTime);
	firstTime = false;

	std::string cpuText;
	cpuText.append("CPU: ");
	cpuText.append(std::to_string(static_cast<int>(usage)));
	cpuText.append("%");
	myCPUText->myText = cpuText;

	if (myShowErrorTimer > 0.0f)
	{
		if (myErrorSprite && myErrorSprite->HasValidTexture())
		{
			float theRandomShake = (((rand() % 100) / 100.0f) - 0.5f) * 0.06f;
			myErrorSprite->SetRotation(theRandomShake);
			myErrorSprite->SetColor(Tga2D::CColor(1, 1, 1, min(myShowErrorTimer, 1.0f)));
			myErrorSprite->Render();
		}
	}


	myShowErrorTimer -=  aTimeDelta;
	myShowErrorTimer = max(myShowErrorTimer, 0.0f);

	unsigned int errors = CEngine::GetInstance()->GetErrorManager().GetErrorsReported();
	if (errors > 0)
	{
		std::string errorsString;
		errorsString.append("Errors: ");
		errorsString.append(std::to_string(errors));
		myErrorsText->myText = errorsString;
	}

	
}


double CDebugDrawer::CalcAverageTick(int newtick)
{
	ticksum -= ticklist[tickindex];  /* subtract value falling off */
	ticksum += newtick;              /* add new value */
	ticklist[tickindex] = newtick;   /* save new value so it can be subtracted later */
	if (++tickindex == MAXSAMPLES)    /* inc buffer index */
		tickindex = 0;

	/* return average */
	return((double)ticksum / MAXSAMPLES);
}

void CDebugDrawer::Render()
{
	myPerformanceGraph->Render();
	for (int i=0; i< myNumberOfRenderedLines; i++)
	{
		myLineBuffer[i]->Render();
	}
	myNumberOfRenderedLines = 0;

	if (myDebugFeatureSet != 0)
	{
		if (CEngine::GetInstance()->IsDebugFeatureOn(eDebugFeature_Fps))
		{
			myFPS->Render();
		}
		if (CEngine::GetInstance()->IsDebugFeatureOn(eDebugFeature_Mem))
		{
			myMemUsage->Render();
		}


		if (CEngine::GetInstance()->IsDebugFeatureOn(eDebugFeature_Cpu))
		{
			myCPUText->Render();
		}

	}

	unsigned int errors = CEngine::GetInstance()->GetErrorManager().GetErrorsReported();
	if (errors > 0)
	{
		myErrorsText->Render();
	}

	if (myDebugFeatureSet != 0 && CEngine::GetInstance()->IsDebugFeatureOn(eDebugFeature_Drawcalls))
	{
		std::string drawCalls;
		drawCalls.append("DrawCalls: ");
		int objCount = CEngine::GetInstance()->GetDirect3D().GetObjectRenderCount() + 1;
		drawCalls.append(std::to_string(objCount));
		myDrawCallText->myText = drawCalls;
		myDrawCallText->myColor.Set(1, 1, 1, 1);
		if (objCount > 1000)
		{
			myDrawCallText->myColor.Set(1, 0, 0, 1);
		}

		myDrawCallText->Render();
	}

}

void Tga2D::CDebugDrawer::DrawLine(Vector2f aFrom, Vector2f aTo, Vector4f aColor)
{
	if (myNumberOfRenderedLines > myMaxLines)
	{
		return;
	}
	myLineBuffer[myNumberOfRenderedLines]->myFromPosition = aFrom;
	myLineBuffer[myNumberOfRenderedLines]->myToPosition = aTo;
	myLineBuffer[myNumberOfRenderedLines]->myColor = aColor;
	myNumberOfRenderedLines++;
}

void Tga2D::CDebugDrawer::DrawLines(Vector2f* aFrom, Vector2f* aTo, CColor* aColor, unsigned int aCount)
{
	if (aCount <= 0)
	{
		return;
	}

	myLineMultiBuffer->myColor = aColor;
	myLineMultiBuffer->myFromPosition = aFrom;
	myLineMultiBuffer->myToPosition = aTo;
	myLineMultiBuffer->myCount = aCount;

	myLineMultiBuffer->Render();
}

void Tga2D::CDebugDrawer::ShowErrorImage()
{
	myShowErrorTimer = 4.0f;
}

void CDebugDrawer::DrawArrow(Vector2f aFrom, Vector2f aTo, Vector4f aColor)
{
	if (myNumberOfRenderedLines+3 > myMaxLines)
	{
		return;
	}

	Vector2f direction = aTo - aFrom;
	direction = direction.Normalize();

	direction *= 0.1f;

	Vector2f theNormal = direction.Normal();
	theNormal *= 0.5f;

	myLineBuffer[myNumberOfRenderedLines]->myFromPosition = aFrom;
	myLineBuffer[myNumberOfRenderedLines]->myToPosition = aTo;
	myLineBuffer[myNumberOfRenderedLines]->myColor = aColor;
	myNumberOfRenderedLines++;

	myLineBuffer[myNumberOfRenderedLines]->myFromPosition = aTo;
	myLineBuffer[myNumberOfRenderedLines]->myToPosition = aTo - direction + theNormal;
	myLineBuffer[myNumberOfRenderedLines]->myColor = aColor;
	myNumberOfRenderedLines++;

	myLineBuffer[myNumberOfRenderedLines]->myFromPosition = aTo;
	myLineBuffer[myNumberOfRenderedLines]->myToPosition =  aTo - direction - theNormal;
	myLineBuffer[myNumberOfRenderedLines]->myColor = aColor;
	myNumberOfRenderedLines++;

}