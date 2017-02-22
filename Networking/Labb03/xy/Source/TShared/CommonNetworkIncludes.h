#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif



#include <windows.h>
#include <unordered_map>
#include <chrono>
#include "CommonErrorHandling.h"
#include <stdio.h>
#include <Winsock2.h>
#include <ws2tcpip.h>
#include "Messages/NetMessage.h"
#include "Time/Time.h"
#include "Time/Stopwatch.h"

const unsigned short globalServerID = 1337;
const float globalImportantMessageTimeout = 0.05f;

const float globalImportantPacketKeepTimeout = 5.f;