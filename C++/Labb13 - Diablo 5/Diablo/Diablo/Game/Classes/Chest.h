#pragma once
#include "Player\Item.h"
#include <vector>
#include "Player.h"

class Chest
{
public:
	Chest();
	~Chest();

	void AddItem(Item* aItem);

	bool ChestMenu(Player & aPlayer);

	

	bool IHaveItems();

private:
	bool ImClosedMenu(Player & aPlayer);

	bool ImOpenMenu(Player & aPlayer);


	bool StrengthTest(Player & aPlayer);

	bool IntelligenceTest(Player & aPlayer);

	void MakeVectorOfItemNamesInChest(std::vector<std::string> & aStringVectorToFill) const;

	Item* RemoveItem(const unsigned int aItemInChestIndex);

	std::vector<Item*> myItems;

	bool myImOpen;
};