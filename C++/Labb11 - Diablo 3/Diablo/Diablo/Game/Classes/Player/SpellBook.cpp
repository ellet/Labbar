#include "stdafx.h"
#include "SpellBook.h"


SpellBook::SpellBook()
{
}


SpellBook::~SpellBook()
{
}

void SpellBook::AddSpell(const Item * aSpellItems)
{
	mySpells.push_back(aSpellItems);
}

const Item* SpellBook::ActivateSpell(const size_t aSpellIndex)
{
	const Item* aTempBuffToActivate = mySpells[aSpellIndex];

	RemoveSpell(aSpellIndex);

	return aTempBuffToActivate;
}

void SpellBook::RemoveSpell(const size_t aSpellIndex)
{
	mySpells.erase(mySpells.begin() + aSpellIndex);
}

void SpellBook::GetSpellsPrintable(std::vector<std::string> & aStringVectorToAddTo) const
{
	for (unsigned int iItem = 0; iItem < mySpells.size(); ++iItem)
	{
		aStringVectorToAddTo.push_back(mySpells[iItem]->itemNameAndDescription.name);
	}
}

bool SpellBook::IHaveSpells()
{
	if (mySpells.size() > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

const size_t SpellBook::GetSpellBookSize() const
{
	return mySpells.size();
}
