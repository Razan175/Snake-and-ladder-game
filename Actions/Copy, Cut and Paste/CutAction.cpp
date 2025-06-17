#include "CutAction.h"
#include "../../Grid/Grid.h"
#include "../../Grid//GameObjects/Cards/Card.h"

CutAction::CutAction(ApplicationManager* pApp) :Action(pApp)
{
}

void CutAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("Please enter the Card you want to Cut ...");
	cellCut = pIn->GetCellClicked();

	pOut->ClearStatusBar();
}

void CutAction::Execute()
{
	ReadActionParameters();
	Grid* pGrid = pManager->GetGrid();
	bool isCopied = pGrid->Copy(cellCut);

	if (!isCopied)
	{
		pGrid->PrintErrorMessage("Item not Cut");
		return;
	}

	pGrid->RemoveObjectFromCell(cellCut);

}

CutAction::~CutAction()
{
}
