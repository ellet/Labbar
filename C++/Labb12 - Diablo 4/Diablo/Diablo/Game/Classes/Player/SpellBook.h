#pragma once
#include <vector>
#include "Item.h"

class SpellBook
{
public:
	SpellBook();
	~SpellBook();

	void AddSpell(const Item* aSpellItems);

	const Item* ActivateSpell(const size_t aSpellIndex);

	void GetSpellsPrintable(std::vector<std::string>& aStringVectorToAddTo) const;

	bool IHaveSpells();

	const size_t GetSpellBookSize() const;
private:
	void RemoveSpell(const size_t aSpellIndex);

	std::vector<const Item*> mySpells;
};

