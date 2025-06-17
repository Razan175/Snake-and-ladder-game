#include "ClearAction.h"
#include "../../Grid/Grid.h"
#include <string.h>
ClearAction::ClearAction(ApplicationManager* pApp) :Action(pApp)
{
	clear = false;
}

void ClearAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("Are you Sure you want to clear the grid? [y/n]");
	string s = pIn->GetSrting(pOut);

	if ('y' == tolower(s[0]))
		clear = true;

	pOut->ClearStatusBar();

}

void ClearAction::Execute()
{
	ReadActionParameters();
	if (clear)
	{
		Grid* pGrid = pManager->GetGrid();
		pGrid->ClearGrid();
	}
}

ClearAction::~ClearAction()
{
}
