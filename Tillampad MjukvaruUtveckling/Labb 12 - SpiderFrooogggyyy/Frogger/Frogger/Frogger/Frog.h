#ifndef FROG_HEADER
#define FROG_HEADER

#include "namespaces.h"
#include "defines.h"
#include "..\hgelibs\include\hge.h"
#include "..\hgelibs\include\hgesprite.h"
#include "StaticArray.h"
#include "Vector2.h"
#include <string>
#include "MainSingleton.h"
#include "Entity.h"

namespace FroggerGame
{
    struct Tile;
	class WaterEntity;

    class Frog : public Entity
    {

    public:

        Frog();
        ~Frog();
        void Init(HGE* aHGE);
		void ResetFrog();
        void Update();
        void Render();
		void KillFrog();
		void AlmostKilledFrog();
        void Respawn();
        void AddScore(int aScoreNumber);
		void SetFoundHome(bool aHasFoundHome);
		void SetCurrentWaterEntity(WaterEntity* aWaterEntity);

		void PhysicsUpdate(const float aDeltaTime);

		int GetScore();
		int GetNumberOfLives();
		CU::Vector2f GetPosition();
		
		bool IsDead();
		bool HasFoundHome();
		bool HasRespawned();

		Tile* GetCurrentTile();


		virtual void ApplyPosition() override;

	private:

		bool IsInsideWorld(CU::Vector2f& aPosition);
		void HandleInput();
		void HandleWalk(const float aDeltaTime);
		void HandleWaterEntityMovement(const float aDeltaTime);
		void HandleAnimation();
		void HandleDeath();
		void HandleRespawn();
		void SetWalkDirection(CU::Vector2i aDirection);
		void ArriveAtTile();

        FG::Tile* myCurrentTile;
		FG::Tile* myStartTile;

		WaterEntity* myCurrentWaterEntity;
		WaterEntity* myWantToApplyWaterEntity;

		//CU::Vector2f myPosition;
        CU::Vector2f myDesiredPosition;
		CU::Vector2i myWalkingDirection;
        int myCurrentSprite;
        int myNumberOfLives;
        int myCurrentScore;
		float myWalkTimer;
		float myDeathTimer;
		float myRespawnTimer;
		float myDeltaTime;
        float myWalkCooldown;
		bool myIsDead;
		bool myIReallyREAAAAALLYWantToDie;
		bool myIsRespawning;
		bool myHasFoundHome;
		bool myHasRespawned;
        HGE* myHGE;   
    };
};

#endif
