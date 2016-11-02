#include "StdAfx.h"
#include "Transformation.h"

void CommonUtilities::RayFromScreenCordinates(const CU::Matrix44f& aProjectionMatrix,const CU::Matrix44f& aInverseViewMatrix,const CU::Vector2f aScreenSize,const CU::Vector2f& aScreenPosition,CU::Vector3f& aResultRayStartPosition,CU::Vector3f& aResultRayDirection)
{
	CU::Vector3f v;
	v.myX = (((2.0f * aScreenPosition.myX) / aScreenSize.myX)-1.0f)/aProjectionMatrix.myMatrix[0][0];
	v.myY = -(((2.0f * aScreenPosition.myY) / aScreenSize.myY)-1.0f)/aProjectionMatrix.myMatrix[1][1]; 
	v.myZ = 1.0f;

	aResultRayDirection.myX = v.myX * aInverseViewMatrix.myMatrix[0][0] + v.myY * aInverseViewMatrix.myMatrix[1][0] + v.myZ * aInverseViewMatrix.myMatrix[2][0];
    aResultRayDirection.myY = v.myX * aInverseViewMatrix.myMatrix[0][1] + v.myY * aInverseViewMatrix.myMatrix[1][1] + v.myZ * aInverseViewMatrix.myMatrix[2][1]; 
    aResultRayDirection.myZ = v.myX * aInverseViewMatrix.myMatrix[0][2] + v.myY * aInverseViewMatrix.myMatrix[1][2] + v.myZ * aInverseViewMatrix.myMatrix[2][2]; 
    aResultRayDirection*=1000000.0f;

    aResultRayStartPosition.myX = aInverseViewMatrix.myMatrix[3][0];
    aResultRayStartPosition.myY = aInverseViewMatrix.myMatrix[3][1];
    aResultRayStartPosition.myZ = aInverseViewMatrix.myMatrix[3][2];
}
