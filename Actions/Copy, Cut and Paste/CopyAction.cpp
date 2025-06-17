#include "CopyAction.h"
#include "../../Grid/Grid.h"
#include "../../Grid/GameObjects/Cards/Card.h"

CopyAction::CopyAction(ApplicationManager* pApp) :Action(pApp)
{
}

void CopyAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("Please enter the Card you want to Copy ...");
	cellCopy = pIn->GetCellClicked();
	pOut->ClearStatusBar();

}

void CopyAction::Execute()
{
	ReadActionParameters();
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	if (!pGrid->Copy(cellCopy))
		pGrid->PrintErrorMessage("No Card to Copy");
	else
		pOut->PrintMessage("Item Copied");

}

CopyAction::~CopyAction()
{
}
