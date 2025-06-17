#pragma once
#include "Card.h"
class CardFiveSix : public Card
{
public:
	CardFiveSix(const CellPosition& pos, int cardnum); // A Constructor takes card position

	virtual void ReadCardParameters(Grid* pGrid); // Reads the parameters of CardOne which is: walletAmount
	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardOne on the passed Player

	void Save(ofstream& OutFile);                                            // by decrementing the player's wallet by the walletAmount data member
	void Load(ifstream& InFile);
	virtual ~CardFiveSix(); // A Virtual Destructor
};

