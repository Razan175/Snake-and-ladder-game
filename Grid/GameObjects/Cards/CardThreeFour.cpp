#include "CardThreeFour.h"
#include "../Ladder.h"

CardThreeFour::CardThreeFour(const CellPosition& pos, int cardnum):Card(pos)
{
	cardNumber = cardnum;
}

void CardThreeFour::Apply(Grid* pGrid, Player* pPlayer)
{
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("You have reached Card " + to_string(cardNumber) + " Click to Continue...");
	pIn->GetCellClicked();

	if (cardNumber == 3) 
	{
		Ladder* nextLadder = pGrid->GetNextLadder(pPlayer->GetCell()->GetCellPosition());
		if (nextLadder)
		{
			pGrid->UpdatePlayerCell(pPlayer, nextLadder->GetPosition());
			nextLadder->Apply(pGrid,pPlayer);
		}
	}
	else
	{
		Ladder* nextLadder = pGrid->GetNextSnake(pPlayer->GetCell()->GetCellPosition());
		if (nextLadder)
		{
			pGrid->UpdatePlayerCell(pPlayer, nextLadder->GetPosition());
			nextLadder->Apply(pGrid, pPlayer);
		}
	}
}

CardThreeFour::~CardThreeFour()
{
}
