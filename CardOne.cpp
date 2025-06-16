#include "CardOne.h"

CardOne::CardOne(const CellPosition& pos, int cardNum) : Card(pos)
{
	cardNumber = cardNum;
}

CardOne::~CardOne(void)
{
}

void CardOne::ReadCardParameters(Grid * pGrid)
{
	
	
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) (numbered below) to implement this function ==


	// 1- Get a Pointer to the Input / Output Interfaces from the Grid
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	// 2- Read an Integer from the user using the Input class and set the walletAmount parameter with it
	//    Don't forget to first print to a descriptive message to the user like:"New CardOne: Enter its wallet amount ..."
	if (cardNumber == 1)
		pOut->PrintMessage("New CardOne: Enter its wallet amount ...");
	else
		pOut->PrintMessage("New CardTwo: Enter its wallet amount ...");
	walletAmount = pIn->GetInteger(pOut);

	// [ Note ]:
	// In CardOne, the only parameter of CardOne is the "walletAmount" value to decrease from player
	// Card parameters are the inputs you need to take from the user in the time of adding the Card in the grid
	// to be able to perform his Apply() action

	// 3- Clear the status bar
	pOut->ClearStatusBar();

}

void CardOne::setWallet(int amount)
{
	walletAmount = amount;
}

int CardOne::getWallet()
{
	return walletAmount;
}

void CardOne::Apply(Grid* pGrid, Player* pPlayer)
{
		
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	

	// == Here are some guideline steps (numbered below) (numbered below) to implement this function ==

	// 1- Call Apply() of the base class Card to print the message that you reached this card number
	Card::Apply(pGrid, pPlayer);
	// 2- Decrement the wallet of pPlayer by the walletAmount data member of CardOne
	if (cardNumber == 1)
		pPlayer->DecrementWallet(walletAmount);
	else
		pPlayer->IncrementWallet(walletAmount);

}

void CardOne::Save(ofstream& OutFile)
{
	Card::Save(OutFile);
	OutFile << walletAmount << endl;
}

void CardOne::Load(ifstream& InFile)
{
	Card::Load(InFile);
	InFile >> walletAmount;
}

