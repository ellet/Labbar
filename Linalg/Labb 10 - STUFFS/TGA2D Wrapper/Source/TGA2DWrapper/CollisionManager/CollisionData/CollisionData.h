#pragma once

class BaseCollisionShape;
class BaseGameObject;

struct CollisionData
{
public:
	CollisionData();
	~CollisionData();

	BaseCollisionShape * myCollisionShape;
	BaseGameObject * myObject;				
};

