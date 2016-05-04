#include "stdafx.h"
#include "ExamineObject.h"
#include "../../Object/Object.h"

ExamineObject::ExamineObject()
{
	myObjectToExamin = nullptr;
}


ExamineObject::~ExamineObject()
{
}


void ExamineObject::OnMouseClickEvent()
{
	DL_ASSERT(myObjectToExamin != nullptr, "Object to examine is nullptr");
	myObjectToExamin->TriggerOnExamine();
}
