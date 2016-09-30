// TestShit.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

class GameObject;

class CollisionNotification
{
public:
	int otherObject;
};

class GenericNotificationSubscriber
{
public:
	~GenericNotificationSubscriber() {}
};

template <typename T>
class NotificationSubscriber : public GenericNotificationSubscriber
{
public:
	NotificationSubscriber()
	{
		dynamic_cast<BaseComponent*>(this)->AddNotificationSubscriber(this);
	}


	virtual void Notify(const T &aNotification) = 0;
};

template <typename T>
void NotificationSubscriber<T>::Notify(const T &aNotification)
{
}

class BaseComponent
{
public:
	void AddNotificationSubscriber(int identifier, GenericNotificationSubscriber * aSubscriber)
	{
		std::cout << "added subscriber" << std::endl;
	}

	void SetGameObject()
	{

	}

private:
	GameObject *obj;
};

class SpecificComponent : public BaseComponent, public NotificationSubscriber<CollisionNotification>
{
public:
	virtual void Notify(const CollisionNotification &aNotification) override
	{
		std::cout << "Notified" << std::endl;
	}

};

int main()
{
	SpecificComponent c;

	std::cin.get();

    return 0;
}

