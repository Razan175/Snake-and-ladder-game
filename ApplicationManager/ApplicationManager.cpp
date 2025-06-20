#include "ApplicationManager.h"

///TODO: Add #include for all action types
#include "../Grid/Grid.h"
#include "../Actions/Add and Remove Actions/AddLadderAction.h"
#include "../Actions/Add and Remove Actions/AddCardAction.h"
#include "../Actions/Game Mode Actions/RollDiceAction.h"
#include "../Actions/Add and Remove Actions/AddSnakeAction.h"
#include "../Actions/Save and Load/SaveAction.h"
#include "../Actions/Save and Load/LoadAction.h"
#include "../Actions/Add and Remove Actions/DeleteObjectAction.h"
#include "../Actions/Copy, Cut and Paste/CopyAction.h"
#include "../Actions/Copy, Cut and Paste/PasteAction.h"
#include "../Actions/Copy, Cut and Paste/CutAction.h"
#include "../Actions/Add and Remove Actions/ClearAction.h"
#include "../Actions/Game Mode Actions/NewGameAction.h"
#include "../Actions/SwitchAction.h"

ApplicationManager::ApplicationManager()
{
	// Create Input, output and Grid
	pOut = new Output();
	pIn = pOut->CreateInput();
	pGrid = new Grid(pIn, pOut);
}

////////////////////////////////////////////////////////////////////////////////////

ApplicationManager::~ApplicationManager()
{
	delete pGrid;
}

//==================================================================================//
//								Interface Management Functions						//
//==================================================================================//

Grid * ApplicationManager::GetGrid() const
{
	return pGrid;
}

void ApplicationManager::UpdateInterface() const
{
	pGrid->UpdateInterface();
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//

ActionType ApplicationManager::GetUserAction() const
{
	// Ask the input to get the action from the user.
	return pIn->GetUserAction();
}

////////////////////////////////////////////////////////////////////////////////////

// Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType) 
{
	Action* pAct = NULL;

	// According to Action Type, create the corresponding action object
	switch (ActType)
	{
	case ADD_LADDER:
		pAct = new AddLadderAction(this);
		break;
	case ADD_SNAKE:
		pAct = new AddSnakeAction(this);
		break;
	case ADD_CARD:
		// create an object of AddCardAction here
		pAct = new AddCardAction(this);
		break;
	case DELETE_OBJECT:
		pAct = new DeleteObjectAction(this);
		break;
	case COPY:
		pAct = new CopyAction(this);
		break;
	case CUT:
		pAct = new CutAction(this);
		break;
	case PASTE:
		pAct = new PasteAction(this);
		break;
	case SAVE:
		pAct = new SaveAction(this);
		break;
	case LOAD:
		pAct = new LoadAction(this);
		break;
	case CLEAR:
		pAct = new ClearAction(this);
		break;
	case EXIT:
		break;
	case TO_DESIGN_MODE:
	case TO_PLAY_MODE:
		pAct = new SwitchAction(this);
		break;
	case ROLL_DICE:
		// create an object of RollDiceAction here
		if (pGrid->IsGameOn())
			pAct = new RollDiceAction(this);
		break;
	case NEW_GAME:
		pAct = new NewGameAction(this);
		break;
		///TODO: Add a case for EACH Action type in the Design mode or Play mode

	case STATUS:	// a click on the status bar ==> no action
		return;
	}

	// Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute(); // Execute
		delete pAct;	 // Action is not needed any more after executing ==> delete it
		pAct = NULL;
	}
}
