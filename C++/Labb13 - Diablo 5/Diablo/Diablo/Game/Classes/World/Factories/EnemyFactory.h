#pragma once
#include "../../Creature.h"
#include <vector>

class EnemyFactory
{
public:
	EnemyFactory();
	~EnemyFactory();

	Creature & GetNewCreature();

private:
	void CreateAllCreatureTemplates();

	std::vector<Creature> myCreatureTemplates;
};