#pragma once

#pragma region Pi

#define M_E 2.71828182845904523536
#define M_LOG2E 1.44269504088896340736
#define M_LOG10E 0.434294481903251827651
#define M_LN2 0.693147180559945309417
#define M_LN10 2.30258509299404568402
#define M_PIF 3.141592f
#define M_PI 3.14159265358979323846
#define M_PI_2 1.57079632679489661923
#define M_PI_4 0.785398163397448309616
#define M_1_PI 0.318309886183790671538
#define M_2_PI 0.636619772367581343076
#define M_1_SQRTPI 0.564189583547756286948
#define M_2_SQRTPI 1.12837916709551257390
#define M_SQRT2 1.41421356237309504880
#define M_SQRT_2 0.707106781186547524401

#define M_EPSILONF 0.0001f

#pragma endregion


#pragma region Angles

// Converts degrees to radians.
#define DEGREES_TO_RADIANS(angleDegrees) ((angleDegrees) * (M_PI / 180.0))

// Converts radians to degrees.
#define RADIANS_TO_DEGREES(angleRadians) ((angleRadians) * (180.0 / M_PI))

// Converts degrees to radians.
#define DEGREES_TO_RADIANSF(angleDegrees) ((angleDegrees) * (static_cast<float>(M_PI) / 180.0f))

// Converts radians to degrees.
#define RADIANS_TO_DEGREESF(angleRadians) ((angleRadians) * (180.0f / static_cast<float>(M_PI)))