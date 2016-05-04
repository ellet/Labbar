#include "MouseInputResolutionAdaption.h"

#include <tga2d\engine.h>

namespace MouseFix
{

	Vector2f GetFixedMousePosition()
	{
		
		Vector2f tempBorder = ScreenResolution::GetViewTransform();
		Vector2f tempScale = ScreenResolution::GetViewScale();
		Vector2ui windowSize = ScreenResolution::GetWindowSize();
		Vector2f tempMousePosition = CommonUtilities::InputWrapper::GetMouseWindowPosition();

		tempMousePosition.x -= windowSize.x * tempBorder.x;
		tempMousePosition.y -= windowSize.y * tempBorder.y;

		tempMousePosition.x /= windowSize.x * tempScale.x;
		tempMousePosition.y /= windowSize.y * tempScale.y;

		tempMousePosition.x *= DX2D::CEngine::GetInstance()->GetWindowSize().x;
		tempMousePosition.y *= DX2D::CEngine::GetInstance()->GetWindowSize().y;

		return tempMousePosition;

	}
}
