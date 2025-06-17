#include "SwitchAction.h"
#include "../Grid/Grid.h"

SwitchAction::SwitchAction(ApplicationManager* pApp):Action(pApp)
{
}

void SwitchAction::ReadActionParameters()
{
}

void SwitchAction::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	if (UI.InterfaceMode == MODE_DESIGN)
	{
		pOut->PrintMessage("Do you want to save your progress?[y/n]");
		if (toupper((pIn->GetSrting(pOut))[0]) == 'Y')
			pManager->ExecuteAction(SAVE);
		pOut->CreatePlayModeToolBar();
	}
	else
	{
		pOut->PrintMessage("Are you sure you want to exit?[y/n]");
		if (toupper((pIn->GetSrting(pOut))[0]) == 'Y')
		{
			pGrid->ResetPlayers();
			pGrid->SetGameOn(false);
			pOut->CreateDesignModeToolBar();
		}
	}
	pOut->ClearStatusBar();
}

SwitchAction::~SwitchAction()
{
}
