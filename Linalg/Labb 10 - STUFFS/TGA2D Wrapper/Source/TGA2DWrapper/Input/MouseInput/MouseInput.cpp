#include "MouseInput.h"
#include "../../Utility/MouseInputResolutionAdaption.h"
#include <InputWrapper/InputWrapper.h>
#include "../../CollisionManager/CollisionManager.h"
#include "../../CollisionManager/CollisionShapes/PointShape.h"

MouseInput * MouseInput::ourInstance;



void MouseInput::Create()
{
	ourInstance = new MouseInput();
	ShowCursor(false);
	
	GetInstance().myPointer.VariableSetup();
}

void MouseInput::Destroy()
{
	delete ourInstance;

	ourInstance = nullptr;
}











void MouseInput::InsideUpdate()
{
	myPointer.SetPosition(MouseFix::GetFixedMousePosition());


	if (CU::InputWrapper::GetMouseButtonPressed(CU::enumMouseButtons::eRight) == true)
	{
		myPointer.TriggerClick();
	}
}









MouseInput::MouseInput()
{
}


MouseInput::~MouseInput()
{
}