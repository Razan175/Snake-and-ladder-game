#include "AddCardAction.h"

#include "../../GUIClasses/Input.h"
#include "../../GUIClasses/Output.h"
#include "../../Grid/GameObjects/Cards/CardOne.h"
#include "../../Grid/GameObjects/Cards/CardThreeFour.h"
#include "../../Grid/GameObjects/Cards/CardFiveSix.h"

AddCardAction::AddCardAction(ApplicationManager *pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

AddCardAction::~AddCardAction()
{
}

void AddCardAction::ReadActionParameters() 
{	

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	// 2- Read the "cardNumber" parameter and set its data member
	pOut->PrintMessage("New Card: Enter its number ...");
	cardNumber = pIn->GetInteger(pOut);

	// 3- Read the "cardPosition" parameter (its cell position) and set its data member
	pOut->PrintMessage("New Card: Click on its Cell ...");
	cardPosition = pIn->GetCellClicked();
	// 4- Make the needed validations on the read parameters

	// 5- Clear status bar
	pOut->ClearStatusBar();
}

void AddCardAction::Execute() 
{

	
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- The first line of any Action Execution is to read its parameter first
	ReadActionParameters();
	// 2- Switch case on cardNumber data member and create the appropriate card object type
	Card * pCard = NULL; // will point to the card object type
	switch (cardNumber)
	{
	case 1:
	case 2:
		pCard = new CardOne(cardPosition,cardNumber);
		break;
	case 3:
	case 4:
		pCard = new CardThreeFour(cardPosition, cardNumber);
		break;
	case 5:
	case 6:
		pCard = new CardFiveSix(cardPosition, cardNumber);
		break;
		// A- Add the remaining cases
	}

	// 3- if pCard is correctly set in the switch case (i.e. if pCard is pointing to an object -- NOT NULL)
	if (pCard)
	{
		// A- We get a pointer to the Grid from the ApplicationManager
		Grid* pGrid = pManager->GetGrid();
		// B- Make the "pCard" reads its card parameters: ReadCardParameters(), It is virtual and depends on the card type
		pCard->ReadCardParameters(pGrid);
		// C- Add the card object to the GameObject of its Cell:
		bool added = pGrid->AddObjectToCell(pCard);
		// D- if the GameObject cannot be added in the Cell, Print the appropriate error message on statusbar
		if (!added)
		{
			// Print an appropriate message
			pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
			delete pCard;
		}
	}

	// Here, the card is created and added to the GameObject of its Cell, so we finished executing the AddCardAction

}
