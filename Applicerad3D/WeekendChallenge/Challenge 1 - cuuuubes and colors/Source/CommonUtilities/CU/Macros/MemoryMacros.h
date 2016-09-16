#pragma once

#define SAFE_DELETE(a) delete (a); (a) = nullptr;
#define ASSIGNED_DELETE(a) if ((a) != nullptr){ SAFE_DELETE((a)); }