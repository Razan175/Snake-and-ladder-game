#pragma once
#include "../Action.h"

class CellPosition;

class CopyAction : public Action
{
	CellPosition cellCopy;
public:

	CopyAction(ApplicationManager* pApp);  // Constructor

	// ============ Virtual Functions ============

	virtual void ReadActionParameters(); // Reads parameters required for action to execute 
	// (code depends on action type so virtual)

	virtual void Execute();  // Executes action (code depends on action type so virtual)

	virtual ~CopyAction();  // Virtual Destructor
};

