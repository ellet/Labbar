#ifndef TRANSFORMATIONS_HEADER
#define TRANSFORMATIONS_HEADER

#include "Matrix44.h"
#include "Vector3.h"
#include "Vector2.h"

namespace CommonUtilities
{
	void RayFromScreenCordinates(const CU::Matrix44f& aProjectionMatrix,const CU::Matrix44f& aInverseViewMatrix,const CU::Vector2f aScreenSize,const CU::Vector2f& aScreenPosition,CU::Vector3f& aResultRayStartPosition,CU::Vector3f& aResultRayDirection); 
};

#endif
