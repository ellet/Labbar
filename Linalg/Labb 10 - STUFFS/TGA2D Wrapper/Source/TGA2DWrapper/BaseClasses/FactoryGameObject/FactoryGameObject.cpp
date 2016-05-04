#include "FactoryGameObject.h"

FactoryGameObject *FactoryGameObject::ourInstance;

void FactoryGameObject::Create()
{
	if (ourInstance == nullptr)
	{

		ourInstance = new FactoryGameObject();

	}
}
void FactoryGameObject::Destroy()
{
	delete ourInstance;
	ourInstance = nullptr;
}

FactoryGameObject::InternalFactory::InternalFactory()
{
}
FactoryGameObject::InternalFactory::~InternalFactory()
{
}

FactoryGameObject::FactoryGameObject()
{
	myFactories.Init(4);
}
FactoryGameObject::~FactoryGameObject()
{
	myFactories.DeleteAll();
}
