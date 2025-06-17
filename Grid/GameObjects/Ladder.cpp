#include "Ladder.h"

Ladder::Ladder(const CellPosition & startCellPos, const CellPosition & endCellPos,GameObjectType t) : GameObject(startCellPos)
{
	Type = t;
	this->endCellPos = endCellPos;

	///TODO: Do the needed validation
}

void Ladder::Draw(Output* pOut) const
{
	if (Type == LadderType)
		pOut->DrawLadder(position, endCellPos);
	else
		pOut->DrawSnake(position, endCellPos);
}

void Ladder::Apply(Grid* pGrid, Player* pPlayer) 
{
	

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==
	
	// 1- Print a message "You have reached a ladder. Click to continue ..." and wait mouse click
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	if (Type == LadderType)
		pOut->PrintMessage("You have reached a ladder. Click to continue ...");
	else
		pOut->PrintMessage("You have reached a snake. Click to continue ...");

	pIn->GetUserAction();
	// 2- Apply the ladder's effect by moving the player to the endCellPos
	//    Review the "pGrid" functions and decide which function can be used for that
	pGrid->UpdatePlayerCell(pPlayer, endCellPos);
	
}

CellPosition Ladder::GetEndPosition() const
{
	return endCellPos;
}

void Ladder::Save(ofstream& OutFile)
{
	OutFile << position.GetCellNum() << "\t" << endCellPos.GetCellNum() << endl;
}

void Ladder::Load(ifstream& Infile)
{
	int start, end;
	Infile >> start >> end;
	position = position.GetCellPositionFromNum(start);
	endCellPos = endCellPos.GetCellNumFromPosition(end);
}
Ladder::~Ladder()
{
}
