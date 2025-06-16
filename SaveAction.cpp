#include "SaveAction.h"
#include "Grid.h"


SaveAction::SaveAction(ApplicationManager* pApp):Action(pApp)
{
}

void SaveAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("Please enter the filename ...");
	filename = pIn->GetSrting(pOut);

	pOut->ClearStatusBar();
	
}

void SaveAction::Execute()
{
	ReadActionParameters();
	ofstream file;
	file.open(filename + ".txt");

	if (file.fail())
		return;
	Grid* pGrid = pManager->GetGrid();
	pGrid->SaveAll(file, LadderType);
	pGrid->SaveAll(file, SnakeType);
	pGrid->SaveAll(file, CardType);

	file.close();
}

SaveAction::~SaveAction()
{
}
