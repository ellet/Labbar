#pragma once
#include <GrowingArray/GrowingArray.h>
#include <DLDebug/DL_Debug.h>

struct EventCollider;
class BaseTriggerCollider;
class BaseCollisionShape;

class CollisionManager
{
public:
	static void Create();
	static void Destroy();

	static inline void AddAEventCollider(const EventCollider & aEventCollider);
	static inline void AddATriggerCollider(const BaseTriggerCollider & aTriggerCollider);
	
	static inline void AddAWorldCollider(const BaseCollisionShape & aBaseCollisionShape);
	static inline void ClearWorldCollisionBox();

	static inline void AddAInterfaceCollider(const EventCollider & aEventCollider);

	static inline bool CheckCollisionAgainstWorld(const BaseCollisionShape & aObjectToCheck);
	static inline bool CheckCollisionAgainstWorldObjects(const BaseCollisionShape & aObjectToCheck);

	static inline void Update();

#pragma region Private
private:
	CollisionManager();
	~CollisionManager();

	static CollisionManager * ourInstance;
	static inline CollisionManager & GetInstance();
	
	bool InsideCheckCollisionAgainstWorld(const BaseCollisionShape & aObjectToCheck) const;
	bool InsideCheckCollisionAgainstWorldObjects(const BaseCollisionShape & aObjectToCheck) const;
	void InsideUpdate();

	void ClearBuffers();
	bool CheckACollision(const BaseTriggerCollider & aTrigger, const EventCollider & aEventCollider) const;

	CU::GrowingArray<const EventCollider*> myEventsColliders;
	CU::GrowingArray<const BaseTriggerCollider*> myTriggerColliders;
	CU::GrowingArray<const BaseCollisionShape*> myWorldColliders;
	CU::GrowingArray<const EventCollider*> myInterfaceColliders;
#pragma endregion
};

#pragma region Inline
inline CollisionManager & CollisionManager::GetInstance()
{
	DL_ASSERT(ourInstance != nullptr, "CollisionManager instance is nullptr");
	return (*ourInstance);
}

inline void CollisionManager::AddAEventCollider(const EventCollider & aEventCollider)
{
	GetInstance().myEventsColliders.Add(&aEventCollider);
}

inline void CollisionManager::AddATriggerCollider(const BaseTriggerCollider & aTriggerCollider)
{
	GetInstance().myTriggerColliders.Add(&aTriggerCollider);
}

void CollisionManager::AddAInterfaceCollider(const EventCollider & aEventCollider)
{
	GetInstance().myInterfaceColliders.Add(&aEventCollider);
}

inline void CollisionManager::AddAWorldCollider(const BaseCollisionShape & aBaseCollisionShape)
{
	GetInstance().myWorldColliders.Add(&aBaseCollisionShape);
}

inline bool CollisionManager::CheckCollisionAgainstWorld(const BaseCollisionShape & aObjectToCheck)
{
	return GetInstance().InsideCheckCollisionAgainstWorld(aObjectToCheck);
}

bool CollisionManager::CheckCollisionAgainstWorldObjects(const BaseCollisionShape & aObjectToCheck)
{
	return GetInstance().InsideCheckCollisionAgainstWorldObjects(aObjectToCheck);
}

inline void CollisionManager::Update()
{
	GetInstance().InsideUpdate();
}

inline void CollisionManager::ClearWorldCollisionBox()
{
	GetInstance().myWorldColliders.RemoveAll();
}
#pragma endregion