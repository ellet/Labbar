#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <stdio.h>
#include <Winsock2.h>
#include <ws2tcpip.h>
#include "MessageStruct.h"
#include "Time/Time.h"
#include "Time/Stopwatch.h"

