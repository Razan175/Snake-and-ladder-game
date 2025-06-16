#include "PasteAction.h"

#include "Grid.h"

PasteAction::PasteAction(ApplicationManager* pApp) :Action(pApp)
{
}

void PasteAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("Please enter the Cell you want to Paste to ...");
	cellPaste = pIn->GetCellClicked();
	pOut->ClearStatusBar();

}

void PasteAction::Execute()
{
	ReadActionParameters();
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	if (!pGrid->Paste(cellPaste))
		pGrid->PrintErrorMessage("Cannot Add Card to Cell");
	else
		pOut->PrintMessage("Item Pasted");

}

PasteAction::~PasteAction()
{
}
