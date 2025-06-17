#include "DeleteObjectAction.h"
#include "../../Grid/Grid.h"


DeleteObjectAction::DeleteObjectAction(ApplicationManager* pApp) :Action(pApp)
{
}

void DeleteObjectAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("Please Click On the Object to be deleted ...");
	toDelete = pIn->GetCellClicked();
	pOut->ClearStatusBar();

}

void DeleteObjectAction::Execute()
{
	ReadActionParameters();
	Grid* pGrid = pManager->GetGrid();
	pGrid->RemoveObjectFromCell(toDelete);
	
}

DeleteObjectAction::~DeleteObjectAction()
{
}
