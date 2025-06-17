#include "CellPosition.h"
#include "UI_Info.h"

CellPosition::CellPosition () 
{
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1; 
	hCell = -1; 
}

CellPosition::CellPosition (int v, int h)
{ 
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1; 
	hCell = -1; 

	SetVCell(v);
	SetHCell(h);
}

CellPosition::CellPosition (int cellNum)
{
	(*this) = GetCellPositionFromNum(cellNum); // the function call with build a cell position (vCell and hCell)
												// from the passed (cellNum)
												// (*this) = ... --> this will copy the returned (vCell and hCell)
												//                   to the data members (vCell and hCell)
}

bool CellPosition::SetVCell(int v) 
{
	///TODO: Implement this function as described in the .h file (don't forget the validation)
	if (v < NumVerticalCells && v >= 0)
		vCell = v;
	else
		return false; // this line sould be changed with your implementation
	return true;
}

bool CellPosition::SetHCell(int h) 
{
	///TODO: Implement this function as described in the .h file (don't forget the validation)

	if (h < NumHorizontalCells && h >= 0)
		hCell = h;
	else
		return false; // this line sould be changed with your implementation
	return true;
}

int CellPosition::VCell() const 
{
	return vCell;
}

int CellPosition::HCell() const 
{
	return hCell;
}

bool CellPosition::IsValidCell() const 
{
	///TODO: Implement this function as described in the .h file
	if (VCell() >= 0 && VCell() < NumVerticalCells && HCell() >= 0 && HCell() < NumHorizontalCells)
		return true; // this line sould be changed with your implementation
	return false;
}

int CellPosition::GetCellNum() const
{
	return GetCellNumFromPosition(*this); // (*this) is the calling object of GetCellNum
										  // which means the object of the current data members (vCell and hCell)
}

int CellPosition::GetCellNumFromPosition(const CellPosition & cellPosition)
{
	// Note:
	// this is a static function (do NOT need a calling object so CANNOT use the data members of the calling object, vCell&hCell)
	// just define an integer that represents cell number and calculate it using the passed cellPosition then return it

	///TODO: Implement this function as described in the .h file
	if (!cellPosition.IsValidCell())
		return -1;

	int num;
	num = (cellPosition.HCell() + 1) + ((NumVerticalCells - cellPosition.VCell() - 1) * NumHorizontalCells);
	return num; // this line should be changed with your implementation
}

CellPosition CellPosition::GetCellPositionFromNum(int cellNum)
{
	// this is a static function (do NOT need a calling object so CANNOT use the data members of the calling object, vCell&hCell)

	if (cellNum > NumVerticalCells * NumHorizontalCells || cellNum < 1)
		return { -1, - 1 };

	CellPosition position;
	
	/// TODO: Implement this function as described in the .h file
	int vPosAct = floor((double)cellNum / NumHorizontalCells);
	if (((double)cellNum / NumHorizontalCells) == vPosAct)
		vPosAct--;
	int vPos = NumVerticalCells - vPosAct - 1;
	int hPos = cellNum - ((NumVerticalCells - vPos - 1) * NumHorizontalCells) - 1;
	
	position.SetHCell(hPos);
	position.SetVCell(vPos);
	// Note: use the passed cellNum to set the vCell and hCell of the "position" variable declared inside the function
	//       I mean: position.SetVCell(...) and position.SetHCell(...) then return it

	return position;
}

void CellPosition::AddCellNum (int addedNum)
{
	
	/// TODO: Implement this function as described in the .h file

	int cellNum = GetCellNum() + addedNum;
	if (cellNum > 99)
		cellNum = 99;
	CellPosition p = GetCellPositionFromNum(cellNum);

	SetHCell(p.HCell());
	SetVCell(p.VCell());
	// Note: this function updates the data members (vCell and hCell) of the calling object

}