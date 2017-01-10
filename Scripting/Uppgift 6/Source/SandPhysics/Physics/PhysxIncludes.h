#pragma once

#include "PxPhysicsAPI.h"
#include "PxPhysics.h"
#include "foundation\PxErrorCallback.h"
#include "PxSceneDesc.h"
#include "extensions\PxDefaultCpuDispatcher.h"
#include "extensions\PxDefaultSimulationFilterShader.h"

#ifdef _DEBUG
#pragma comment (lib, "..\\..\\extlibs\\Physx\\debug\\PhysX3DEBUG_x64.lib")
#pragma comment (lib, "..\\..\\extlibs\\Physx\\debug\\PhysX3CommonDEBUG_x64.lib")
#pragma comment (lib, "..\\..\\extlibs\\Physx\\debug\\PhysX3ExtensionsDEBUG.lib")
#pragma comment (lib, "..\\..\\extlibs\\Physx\\debug\\PhysXProfileSDKDEBUG.lib")
#pragma comment (lib, "..\\..\\extlibs\\Physx\\debug\\PhysXVisualDebuggerSDKDEBUG.lib")
#else
#pragma comment (lib, "..\\..\\extlibs\\Physx\\release\\PhysX3_x64.lib")
#pragma comment (lib, "..\\..\\extlibs\\Physx\\release\\PhysX3Common_x64.lib")
#pragma comment (lib, "..\\..\\extlibs\\Physx\\release\\PhysX3Extensions.lib")
#pragma comment (lib, "..\\..\\extlibs\\Physx\\release\\PhysXProfileSDK.lib")
#endif

namespace physx
{
}

using namespace physx;