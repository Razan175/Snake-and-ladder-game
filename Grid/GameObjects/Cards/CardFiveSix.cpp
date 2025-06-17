#include "CardFiveSix.h"

CardFiveSix::CardFiveSix(const CellPosition& pos, int cardNum) : Card(pos)
{
	cardNumber = cardNum;
}

void CardFiveSix::ReadCardParameters(Grid* pGrid)
{
}

void CardFiveSix::Apply(Grid* pGrid, Player* pPlayer)
{
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("Card " + to_string(cardNumber) + " Reached, Click to Continue... ");
	pIn->GetCellClicked();

	if (cardNumber == 5)
		pPlayer->Move(pGrid, pPlayer->GetDice());
	else
		pPlayer->Move(pGrid,-1 * pPlayer->GetDice());

}

void CardFiveSix::Save(ofstream& OutFile)
{
	Card::Save(OutFile);
}

void CardFiveSix::Load(ifstream& InFile)
{
	Card::Load(InFile);
}

CardFiveSix::~CardFiveSix()
{
}
