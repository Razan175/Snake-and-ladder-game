#include "RollDiceAction.h"

#include "../../Grid/Grid.h"
#include "../../Player/Player.h"

#include <time.h> // used to in srand to generate random numbers with different seed

RollDiceAction::RollDiceAction(ApplicationManager *pApp) : Action(pApp)
{
}

void RollDiceAction::ReadActionParameters()
{
	// no parameters to read from user
}

void RollDiceAction::Execute()
{
		
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Check if the Game is ended (Use the GetEndGame() function of pGrid), if yes, make the appropriate action
	
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	if (pGrid->GetEndGame())
		return; //////////////to be changed
	// -- If not ended, do the following --:

	// 2- Generate a random number from 1 to 6 --> This step is done for you
	srand((int)time(NULL)); // time is for different seed each run
	int diceNumber = 1 + (rand() % 6); // from 1 to 6 --> should change seed

	// 3- Get the "current" player from pGrid
	Player* p = pGrid->GetCurrentPlayer();
	// 4- Move the currentPlayer using function Move of class player
	p->Move(pGrid, diceNumber);
	// 5- Advance the current player number of pGrid
	pGrid->AdvanceCurrentPlayer();

	// NOTE: the above guidelines are the main ones but not a complete set (You may need to add more steps).
	if (!pGrid->GetEndGame())
		pOut->PrintMessage(pGrid->GetCurrentPlayer()->GetPlayerColor() + " 's turn. Please roll the dice..");
	else
		pOut->PrintMessage(p->GetPlayerColor() + " Won!!! play again?[y/n]");
}

RollDiceAction::~RollDiceAction()
{
}
