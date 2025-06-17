#include "Player.h"

#include "../Grid/GameObjects/GameObject.h"

Player::Player(Cell * pCell, int playerNum) : stepCount(0), wallet(100), playerNum(playerNum)
{
	this->pCell = pCell;
	this->turnCount = 0;
	if (UI.PlayerColors[playerNum] == BLUE)
		playerColor = "BLUE";
	else if (UI.PlayerColors[playerNum] == RED)
		playerColor = "RED";
	else if (UI.PlayerColors[playerNum] == GREEN)
		playerColor = "GREEN";
	else if (UI.PlayerColors[playerNum] == PURPLE)
		playerColor = "PURPLE";

	// Make all the needed initialization or validations
}

// ====== Setters and Getters ======

void Player::SetCell(Cell * cell)
{
	pCell = cell;
}

Cell* Player::GetCell() const
{
	return pCell;
}

void Player::SetWallet(int wallet)
{
	this->wallet = wallet;
	// Make any needed validations
}

int Player::GetWallet() const
{
	return wallet;
}

int Player::GetTurnCount() const
{
	return turnCount;
}

int Player::GetPlayerNum()
{
	return playerNum;
}

void Player::ResetPlayer()
{
	stepCount = 0;
	wallet = 100;
	turnCount = 0;
}

int Player::GetDice()
{
	return justRolledDiceNum;
}

// ====== Drawing Functions ======

void Player::Draw(Output* pOut) const
{
	color playerColor = UI.PlayerColors[playerNum];

	pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, playerColor);
	///TODO: use the appropriate output function to draw the player with "playerColor"

}

void Player::ClearDrawing(Output* pOut) const
{
	color cellColor = pCell->HasCard() ? UI.CellColor_HasCard : UI.CellColor_NoCard;
	
	
	///TODO: use the appropriate output function to draw the player with "cellColor" (to clear it)
	pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, cellColor);
}

// ====== Game Functions ======

void Player::Move(Grid * pGrid, int diceNumber)
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==


	// 1- Increment the turnCount because calling Move() means that the player has rolled the dice once
	turnCount++;
	// 2- Check the turnCount to know if the wallet recharge turn comes (recharge wallet instead of move)
	//    If yes, recharge wallet and reset the turnCount and return from the function (do NOT move)
	if (turnCount == 3)
	{
		wallet += (10 * diceNumber);
		turnCount = 0;
		return;
	}
		// 3- Set the justRolledDiceNum with the passed diceNumber
	justRolledDiceNum = diceNumber;
	// 4- Get the player current cell position, say "pos", and add to it the diceNumber (update the position)
	//    Using the appropriate function of CellPosition class to update "pos"
	CellPosition pos = pCell->GetCellPosition();
	pos.AddCellNum(diceNumber);
	// 5- Use pGrid->UpdatePlayerCell() func to Update player's cell POINTER (pCell) with the cell in the passed position, "pos" (the updated one)
	//    the importance of this function is that it Updates the pCell pointer of the player and Draws it in the new position
	pGrid->UpdatePlayerCell(this, pos);
	// 6- Apply() the game object of the reached cell (if any)
	if (pCell->GetGameObject())
		pCell->GetGameObject()->Apply(pGrid,this);
	// 7- Check if the player reached the end cell of the whole game, and if yes, Set end game with true: pGrid->SetEndGame(true)
	if (pCell->GetCellPosition().GetCellNum() == 99)
	{
		pGrid->SetEndGame(true);
		pGrid->SetGameOn(false);
	}
}

void Player::AppendPlayerInfo(string & playersInfo) const
{
	playersInfo += playerColor + "(" ;
	playersInfo += to_string(wallet) + ", ";
	playersInfo += to_string(turnCount) + ")";
}

void Player::IncrementWallet(int amount)
{
	wallet += amount;
}

void Player::DecrementWallet(int amount)
{
	wallet -= amount;
}

string Player::GetPlayerColor()
{
	return playerColor;
}
