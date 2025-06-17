#pragma once
#include "Card.h"
class CardThreeFour :
    public Card
{

public:
	CardThreeFour(const CellPosition& pos, int cardnum); // A Constructor takes card position
	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardOne on the passed Player

	virtual ~CardThreeFour(); // A Virtual Destructor
};

