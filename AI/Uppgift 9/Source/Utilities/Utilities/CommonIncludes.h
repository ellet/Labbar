#pragma once

#define NOMINMAX

template<typename T>
__forceinline T max(T a, T b)
{
	return (((a) > (b)) ? (a) : (b));
}

template<typename T>
__forceinline T min(T a, T b)
{
	return (((a) < (b)) ? (a) : (b));
}

#include <memory>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <set>
#include <memory>
#include <cmath>
#include <thread>
#include <assert.h>
#include <array>
#include <atomic>
#include <mutex>
#include <type_traits>

#include <Windows.h>
// ty windows
#undef DrawState
#undef GetObject
#undef GetWindowFont
#undef PlaySound
#undef CreateWindow
#undef DrawText
#undef GetMessage

#define Error(e) { std::string _errorString = "Error in execution:\r\n"; _errorString += e; _errorString += "\r\nAt "; _errorString += __FILE__; _errorString += ":"; _errorString += std::to_string(__LINE__); std::cout << _errorString << std::endl; MessageBoxA(nullptr, _errorString.c_str(), "Error", MB_ICONERROR | MB_DEFAULT_DESKTOP_ONLY); terminate(); }
#define Warning(e) { std::cout << e << std::endl; }
#define FLOOR(aValue, aFloorValue) ((aValue) < (aFloorValue) ? aValue : aFloorValue)
#define CEILING(aValue, aCeilingValue) ((aValue) > (aCeilingValue) ? aValue : aCeilingValue)
#define CLAMP(a, min, max) ((a)<(min)?(min):((a)>(max)?(max):(a)))
#define MIN(a, b) (((a)<(b))?(a):(b))
#define MAX(a, b) (((a)>(b))?(a):(b))
#define ABS(a) (a)<0?(a)*-1:(a) 
#define SWAP(a, b)	(a) = (a) ^ (b); (b) = (a) ^ (b); (a) = (a) ^ (b);

__forceinline float Lerp(const float aStart, const float anEnd, const float aProgress)
{
	return (aStart * aProgress) + ((1.f - aProgress) * anEnd);
}

#include "Utilities/ConcurrentQueue.h"
namespace SB
{
	template <typename TObjectType>
	using ConcurrentQueue = moodycamel::ConcurrentQueue<TObjectType>;
}

#include "Utilities/MessageQueue/MessageReceiver.h"
#include "Utilities/MessageQueue/MessageQueue.h"

#include "Utilities/StringFormatter.h"
#include "Utilities\Math\MathMacros.h"
#include "Utilities\Math\Vector2.h"
#include "Utilities\Math\Vector3.h"
#include "Utilities\Math\Vector4.h"
#include "Utilities\Math\Matrix33.h"
#include "Utilities\Math\Matrix44.h"
#include "Utilities\Math\Quaternion.h"
#include "Utilities\Container\Stack.h"
#include "Utilities/Container/StaticList.h"

#include "Utilities/Time/Time.h"
#include "Utilities/Time/Stopwatch.h"

#include "Utilities/Color/Color.h"

#include "Utilities\Shapes\SphereShape.h"
#include "Utilities\Shapes\BoxShape.h"
#include "Utilities\Shapes\LineSegmentShape.h"
#include "Utilities\Shapes\CapsuleShape.h"

//#include "..\ImGui\imgui.h"

static const float Pi = 3.14159265358979323846f;
static const float HalfPi = Pi / 2.f;
static const float QuarterPi = Pi / 4.f;
static const float TwoPi = Pi * 2.f;
static const float Tau = TwoPi;
static const float FullRotation = TwoPi;
static const float HalfRotation = Pi;
static const float QuarterRotation = HalfPi;

static const int MaxMessageTypesCount = 1024;
static const int MaxStoredMessages = 1024;

static const std::string EmptyString("");
