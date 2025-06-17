#pragma once
#include "../Action.h"
class PasteAction : public Action
{

	CellPosition cellPaste;
public:

	PasteAction(ApplicationManager* pApp);  // Constructor

	// ============ Virtual Functions ============

	virtual void ReadActionParameters(); // Reads parameters required for action to execute 
	// (code depends on action type so virtual)

	virtual void Execute();  // Executes action (code depends on action type so virtual)

	virtual ~PasteAction();  // Virtual Destructor
};

