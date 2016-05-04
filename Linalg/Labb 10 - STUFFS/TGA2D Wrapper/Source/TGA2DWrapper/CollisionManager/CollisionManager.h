#pragma once
#include <GrowingArray/GrowingArray.h>
#include <DLDebug/DL_Debug.h>

struct EventCollider;
class BaseTriggerCollider;
class BaseCollisionShape;
struct CollisionData;

class CollisionManager
{
public:
	static void Create();
	static void Destroy();

	static void inline AddCollisionData(const CollisionData & aCollisonData);
	static void inline AddWorldCollisionData(const CollisionData & aCollisionData);

	static inline void Update();

#pragma region Private
private:
	CollisionManager();
	~CollisionManager();

	static CollisionManager * ourInstance;
	static inline CollisionManager & GetInstance();
	
	void InsideUpdate();

	void ClearBuffers();
	void CheckACollision(const CollisionData & aFirstCollider, const CollisionData & aSecondCollider) const;

	

	CU::GrowingArray<const CollisionData*, size_t> myCollisionData;
	CU::GrowingArray<const CollisionData*, size_t> myWorldColliders;

	
#pragma endregion
};

#pragma region Inline
inline CollisionManager & CollisionManager::GetInstance()
{
	DL_ASSERT(ourInstance != nullptr, "CollisionManager instance is nullptr");
	return (*ourInstance);
}

void CollisionManager::AddCollisionData(const CollisionData & aCollisonData)
{
	GetInstance().myCollisionData.Add(&aCollisonData);
}

void CollisionManager::AddWorldCollisionData(const CollisionData & aCollisionData)
{
	GetInstance().myWorldColliders.Add(&aCollisionData);
}

inline void CollisionManager::Update()
{
	GetInstance().InsideUpdate();
}

#pragma endregion