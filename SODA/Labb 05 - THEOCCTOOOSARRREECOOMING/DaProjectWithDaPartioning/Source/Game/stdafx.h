// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers



// TODO: reference additional headers your program requires here
#include <CU/Timer/Time.h>
#include <CU/Timer/TimeManager.h>
#include <CU/NameSpaceAliases.h>
#include <CU/DLDebug/DL_Debug.h>
#include <CU/Vectors/vector2.h>
#include <CU/GrowingArray/GrowingArray.h>
#include <CU/Macros/Macros.h>
#include <CU/InputWrapper/SingletonInputWrapper.h>
#include <CU/Intersection/Shapes2D/Circle2D.h>
#include <CU/Intersection/Shapes2D/AABB2D.h>
#include <CU/Intersection/Shapes2D/LineSegment2D.h>
#include <CU/Intersection/Intersections.h>
#include <CU/GridArray/GridArray.h>
#include <Rend/RenderConverter.h>
#include <CU/StaticArray/StaticArray.h>