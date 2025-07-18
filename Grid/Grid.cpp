#include "Grid.h"
#include "Cell.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Ladder.h"
#include "GameObjects/Cards/Card.h"
#include "../Player/Player.h"
#include "GameObjects//Cards/CardOne.h"
#include "GameObjects//Cards/CardThreeFour.h"
#include "GameObjects//Cards/CardFiveSix.h"

Grid::Grid(Input * pIn, Output * pOut) : pIn(pIn), pOut(pOut) // Initializing pIn, pOut
{
	// Allocate the Cell Objects of the CellList
	for (int i = NumVerticalCells-1; i >= 0 ; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			CellList[i][j] = new Cell(i, j);
		}
	}

	// Allocate thePlayer Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++) 
	{
		PlayerList[i] = new Player(CellList[NumVerticalCells-1][0], i); // first cell
		PlayerList[i]->Draw(pOut); // initially draw players in the first cell
	}

	// Initialize currPlayerNumber with 0 (first player)
	currPlayerNumber = 0; // start with the first player

	// Initialize Clipboard with NULL
	Clipboard = NULL;

	// Initialize endGame with false
	endGame = false;

	gameOn = false;

	ladderNumber = 0;
	snakeNumber = 0;
	cardNumber = 0;
}


// ========= Adding or Removing GameObjects to Cells =========

bool Grid::AddObjectToCell(GameObject * pNewObject)  // think if any validation is needed
{
	// Get the cell position of pNewObject
	CellPosition pos = pNewObject->GetPosition();
	if (pos.IsValidCell()) // Check if valid position
	{
		// Get the previous GameObject of the Cell
		GameObject * pPrevObject = CellList[pos.VCell()][pos.HCell()]->GetGameObject();

		if( pPrevObject)  // the cell already contains a game object
			return false; // do NOT add and return false
		// Set the game object of the Cell with the new game object

		if (pNewObject->GetType() == LadderType || pNewObject->GetType() == SnakeType)
		{
			Ladder* p = dynamic_cast<Ladder*>(pNewObject);
			pPrevObject = CellList[p->GetEndPosition().VCell()][p->GetEndPosition().HCell()]->GetGameObject();
			if (pPrevObject)  // the cell already contains a game object
				return false; // do NOT add and return false
		}
		
		CellList[pos.VCell()][pos.HCell()]->SetGameObject(pNewObject);

		if (CellList[pos.VCell()][pos.HCell()]->HasSnake())
			snakeNumber++;
		else if (CellList[pos.VCell()][pos.HCell()]->HasLadder())
			ladderNumber++;
		else if (CellList[pos.VCell()][pos.HCell()]->HasCard())
			cardNumber++;

		return true; // indicating that addition is done
	}
	return false; // if not a valid position
}

void Grid::RemoveObjectFromCell(const CellPosition & pos)
{
	if (pos.IsValidCell()) // Check if valid position
	{
		// Note: you can deallocate the object here before setting the pointer to null if it is needed
		if (CellList[pos.VCell()][pos.HCell()]->HasSnake())
			snakeNumber--;
		else if (CellList[pos.VCell()][pos.HCell()]->HasLadder())
			ladderNumber--;
		else if (CellList[pos.VCell()][pos.HCell()]->HasCard())
			cardNumber--;

		if (CellList[pos.VCell()][pos.HCell()]->GetGameObject() != Clipboard)
			delete CellList[pos.VCell()][pos.HCell()]->GetGameObject();

		CellList[pos.VCell()][pos.HCell()]->RemoveGameObject();
	}
}

void Grid::UpdatePlayerCell(Player * player, const CellPosition & newPosition)
{
	// Clear the player's circle from the old cell position
	player->ClearDrawing(pOut);

	// Set the player's CELL with the new position
	Cell * newCell = CellList[newPosition.VCell()][newPosition.HCell()];
	player->SetCell(newCell);	

	// Draw the player's circle on the new cell position
	player->Draw(pOut);
}

void Grid::ResetPlayers()
{
	currPlayerNumber = 0;
	endGame = false;
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		PlayerList[i]->ResetPlayer();
		UpdatePlayerCell(PlayerList[i], CellList[NumVerticalCells - 1][0]->GetCellPosition());
	}

}

void Grid::ClearGrid()
{
	// Allocate the Cell Objects of the CellList
	for (int i = NumVerticalCells - 1; i >= 0; i--) // to allocate cells from bottom up
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
			CellList[i][j]->RemoveGameObject();

	ResetPlayers();
}


// ========= Setters and Getters Functions =========


Input * Grid::GetInput() const
{
	return pIn;
}

Output * Grid::GetOutput() const
{
	return pOut;
}

void Grid::SetClipboard(Card * pCard) // to be used in copy/cut
{
	// you may update slightly in implementation if you want (but without breaking responsibilities)
	Clipboard = pCard;
}

Card * Grid::GetClipboard() const // to be used in paste
{
	return Clipboard;
}

void Grid::SetEndGame(bool endGame)
{
	this->endGame = endGame;
}

bool Grid::GetEndGame() const
{
	return endGame;
}

void Grid::AdvanceCurrentPlayer()
{
	currPlayerNumber = (currPlayerNumber + 1) % MaxPlayerCount; // this generates value from 0 to MaxPlayerCount - 1
}

bool Grid::IsGameOn() 
{
	return gameOn;
}

void Grid::SetGameOn(bool gOn)
{
	gameOn = gOn;
}

// ========= Other Getters =========


Player * Grid::GetCurrentPlayer() const
{
	return PlayerList[currPlayerNumber];
}

Ladder * Grid::GetNextLadder(const CellPosition & position)
{
	
	int startH = position.HCell(); // represents the start hCell in the current row to search for the ladder in
	for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{


			///TODO: Check if CellList[i][j] has a ladder, if yes return it
			if (CellList[i][j]->HasLadder())
				return (Ladder*)CellList[i][j]->GetGameObject();
		}
		startH = 0; // because in the next above rows, we will search from the first left cell (hCell = 0) to the right
	}
	return NULL; // not found
}

Ladder* Grid::GetNextSnake(const CellPosition& position)
{

	int startH = position.HCell(); // represents the start hCell in the current row to search for the ladder in
	for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{


			///TODO: Check if CellList[i][j] has a ladder, if yes return it
			if (CellList[i][j]->HasSnake())
				return (Ladder*)CellList[i][j]->GetGameObject();
		}
		startH = 0; // because in the next above rows, we will search from the first left cell (hCell = 0) to the right
	}
	return NULL; // not found
}
// ========= User Interface Functions =========


void Grid::UpdateInterface() const
{
	if (UI.InterfaceMode == MODE_DESIGN)
	{
		// 1- Draw cells with or without cards 
		for (int i = NumVerticalCells-1; i >= 0 ; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawCellOrCard(pOut);
			}
		}

		// 2- Draw other cell objects (ladders, snakes)
		for (int i = NumVerticalCells-1; i >= 0 ; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawLadderOrSnake(pOut);
			}
		}

		// 3- Draw players
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->Draw(pOut);
		}
	}
	else // In PLAY Mode
	{
		// 1- Print Player's Info
		pOut->CreatePlayModeToolBar();
		string playersInfo = "";
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->AppendPlayerInfo(playersInfo); // passed by reference
			if (i < MaxPlayerCount-1) // except the last player
				playersInfo += ", ";
		}
		playersInfo += " | Curr = " + to_string(currPlayerNumber);

		pOut->PrintPlayersInfo(playersInfo);

		// Note: UpdatePlayerCell() function --> already update drawing players in Play Mode
		//       so we do NOT need draw all players again in UpdateInterface() of the Play mode
		// In addition, cards/snakes/ladders do NOT change positions in Play Mode, so need to draw them here too
	}
}

void Grid::PrintErrorMessage(string msg)
{
	pOut->PrintMessage(msg);
	int x, y;
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();
}


bool Grid::Copy(CellPosition cellCopy)
{
	if (CellList[cellCopy.VCell()][cellCopy.HCell()]->HasCard())
	{
		SetClipboard((Card*)CellList[cellCopy.VCell()][cellCopy.HCell()]->GetGameObject());
		return true;
	}
	return false;
}

bool Grid::Paste(CellPosition cellPaste)
{
	CardOne* newCard1;
	CardThreeFour* newCard2;
	if (!CellList[cellPaste.VCell()][cellPaste.HCell()]->GetGameObject() && Clipboard)
	{
		bool flag = false;
		switch (Clipboard->GetCardNumber())
		{
			case 1:
			case 2:
			CardOne * tempCard1;
			tempCard1 = dynamic_cast<CardOne*>(Clipboard);
			newCard1 = new CardOne(cellPaste, Clipboard->GetCardNumber());
			newCard1->setWallet(tempCard1->getWallet());
			flag = AddObjectToCell(newCard1);
			break;

			case 3:
			case 4:
			newCard2 = new CardThreeFour(cellPaste, Clipboard->GetCardNumber());
			flag = AddObjectToCell(newCard2);
			break;

			case 5:
			case 6:
			CardFiveSix * newCard3 = new CardFiveSix(cellPaste, Clipboard->GetCardNumber());
			flag = AddObjectToCell(newCard3);
			break;
		}
		return flag;
	}
	return false;
}

void Grid::SaveAll(ofstream& OutFile, GameObjectType Type)
{
	switch (Type)
	{
	case LadderType:
		OutFile << ladderNumber << endl;
		for (int i = NumVerticalCells - 1; i >= 0; i--)
			for (int j = 0; j < NumHorizontalCells; j++)
				if (CellList[i][j]->HasLadder())
					CellList[i][j]->GetGameObject()->Save(OutFile);
		break;
	case SnakeType:
		OutFile << snakeNumber << endl;
		for (int i = NumVerticalCells - 1; i >= 0; i--)
			for (int j = 0; j < NumHorizontalCells; j++)
				if (CellList[i][j]->HasSnake())
					CellList[i][j]->GetGameObject()->Save(OutFile);
		break;
	case CardType:
		OutFile << cardNumber << endl;
		for (int i = NumVerticalCells - 1; i >= 0; i--)
			for (int j = 0; j < NumHorizontalCells; j++)
				if (CellList[i][j]->HasCard())
					CellList[i][j]->GetGameObject()->Save(OutFile);
	}

}

void Grid::LoadAll(ifstream& InFile)
{
	ClearGrid();

	int lNum;
	InFile >> lNum;
	Ladder* l = NULL;
	for (int i = 0; i < lNum; i++)
	{
		l = new Ladder(0,0,LadderType);
		l->Load(InFile);
		AddObjectToCell(l);
		l = NULL;
	}
	int sNum;
	InFile >> sNum;
	Ladder* s = NULL;
	for (int i = 0; i < sNum; i++)
	{
		s = new Ladder(0,0,SnakeType);
		s->Load(InFile);
		AddObjectToCell(s);
		s = NULL;
	}

	int cNum;
	InFile >> cNum;
	Card* c = NULL;
	for (int i = 0; i < cNum; i++)
	{
		int cardNo;
		InFile >> cardNo;
		switch (cardNo)
		{
			case 1:
			case 2:
			c = new CardOne(0,cardNo);
			break;
		}
		c->Load(InFile);
		AddObjectToCell(c);
		c = NULL;
	}
}

Grid::~Grid()
{
	delete pIn;
	delete pOut;

	// Deallocate the Cell Objects of the CellList
	for (int i = NumVerticalCells-1; i >= 0 ; i--) 
	{
		for (int j = 0; j < NumHorizontalCells; j++) 
		{
			delete CellList[i][j];
		}
	}

	// Deallocate the Player Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++) 
	{
		delete PlayerList[i];
	}
}