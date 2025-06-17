#include "NewGameAction.h"
#include "../../Grid/Grid.h"
#include "../../Player/Player.h"

NewGameAction::NewGameAction(ApplicationManager* pApp):Action(pApp)
{
}

void NewGameAction::ReadActionParameters()
{
}

void NewGameAction::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	if (pGrid->IsGameOn())
	{
		pOut->PrintMessage("Are you sure you want to restart the game?[y/n]");
		if (toupper((pIn->GetSrting(pOut))[0]) == 'Y')
			pGrid->ResetPlayers();

		pOut->ClearStatusBar();
	}
	else
	{
		pOut->PrintMessage("Welcome.. " + pGrid->GetCurrentPlayer()->GetPlayerColor() + " 's turn. Please roll the dice..");
		pGrid->SetGameOn(true);
		pGrid->ResetPlayers();
	}
}

NewGameAction::~NewGameAction()
{
}
