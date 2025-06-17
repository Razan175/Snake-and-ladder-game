#include "LoadAction.h"
#include "../../Grid/Grid.h"

#include <fstream>
#include <iostream>

using namespace std;
LoadAction::LoadAction(ApplicationManager* pApp) :Action(pApp)
{
}

void LoadAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("Please enter the filename ...");
	filename = pIn->GetSrting(pOut);

	pOut->ClearStatusBar();

}

void LoadAction::Execute()
{
	ReadActionParameters();
	ifstream file;
	file.open("SavedGrids/" + filename + ".txt");

	if (file.fail())
		return;

	Grid* pGrid = pManager->GetGrid();
	pGrid->LoadAll(file);

	file.close();
}

LoadAction::~LoadAction()
{
}
