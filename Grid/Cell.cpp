#include "Cell.h"

#include "Grid.h"
#include "GameObjects/Ladder.h"
#include "GameObjects/Cards/Card.h"
#include "../Player/Player.h"


Cell::Cell(const CellPosition & pos) : position(pos)
{
	// initializes the data members (position & pGameObject)
	pGameObject = NULL;
}

Cell::Cell(int v, int h) : position(v, h)
{
	// initializes the data members (position & pGameObject)
	pGameObject = NULL;
}


// ======= Setters and Getters Functions ======= 


CellPosition Cell::GetCellPosition() const
{
	return position;
}

bool Cell::SetGameObject(GameObject * pGObj)
{
	if (pGameObject != NULL) // already contains one
		return false; // do NOT add it and return false

	pGameObject = pGObj;
	return true;
}

void Cell::RemoveGameObject()
{
	pGameObject = NULL;
}

GameObject * Cell::GetGameObject() const
{
	return pGameObject;
}

Ladder * Cell::HasLadder() const
{

	if (pGameObject && pGameObject->GetType() == LadderType)
		return dynamic_cast<Ladder*>(pGameObject); // THIS LINE SHOULD CHANGED WITH YOUR IMPLEMENTATION
	else
		return NULL;
}

Ladder * Cell::HasSnake() const
{

	///TODO: Implement the following function like HasLadder() function
	if (pGameObject && pGameObject->GetType() == SnakeType)
		return dynamic_cast<Ladder*>(pGameObject); // THIS LINE SHOULD CHANGED WITH YOUR IMPLEMENTATION
	else
		return NULL;
}

Card * Cell::HasCard() const
{

	///TODO: Implement the following function like HasLadder() function
		return dynamic_cast<Card*>(pGameObject); // THIS LINE SHOULD CHANGED WITH YOUR IMPLEMENTATION

}


// ======= Drawing Functions ======= 

void Cell::DrawCellOrCard(Output* pOut) const
{
	// Checks if there is a Card on the cell
	if (HasCard()) // means if not NULL
		pGameObject->Draw(pOut); // draw the card then
	else
		pOut->DrawCell(position, -1); // draw empty cell (no card -1)
}

// separate from the above function because ladders/snakes should be drawn AFTER All Cells are drawn
void Cell::DrawLadderOrSnake(Output* pOut) const
{
	if (HasLadder() || HasSnake())
		pGameObject->Draw(pOut); // draw it either ladder or snake

}

Cell::~Cell()
{
	if (pGameObject)
		delete pGameObject;
}
