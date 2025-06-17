#include "AddSnakeAction.h"

#include "Input.h"
#include "Output.h"
#include "Ladder.h"

AddSnakeAction::AddSnakeAction(ApplicationManager* pApp) : Action(pApp)
{
}

void AddSnakeAction::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// Read the startPos parameter

	pOut->PrintMessage("New Snake: Click on its Start Cell ...");
	startPos = pIn->GetCellClicked();

	// Read the endPos parameter
	pOut->PrintMessage("New Snake: Click on its End Cell ...");
	endPos = pIn->GetCellClicked();
	
	///TODO: Make the needed validations on the read parameters
	if (startPos.GetCellNum() < endPos.GetCellNum() || startPos.HCell() != endPos.HCell() || startPos.VCell() == NumVerticalCells - 1)
		pOut->PrintMessage("Invalid start and end positions.. please try again");

	// Clear messages
	pOut->ClearStatusBar();
}

void AddSnakeAction::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();
	if (startPos.GetCellNum() < endPos.GetCellNum() || startPos.HCell() != endPos.HCell() || startPos.VCell() == NumVerticalCells - 1)
	return;
	// Create a Ladder object with the parameters read from the user
	Ladder* pSnake = new Ladder(startPos, endPos,SnakeType);

	Grid* pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager

	// Add the card object to the GameObject of its Cell:
	bool added = pGrid->AddObjectToCell(pSnake);

	// if the GameObject cannot be added
	if (!added)
	{
		// Print an appropriate message
		pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
		delete pSnake;
	}
	// Here, the ladder is created and added to the GameObject of its Cell, so we finished executing the AddLadderAction

}

AddSnakeAction::~AddSnakeAction()
{
}
