#pragma once

namespace SB
{
	class GameObject;
}

struct ShotHitEvent
{
	ShotHitEvent(const SB::GameObject & aGameObject) : myObjectHit(&aGameObject)
	{}

	const SB::GameObject * myObjectHit;
};