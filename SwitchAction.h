#pragma once
#include "Action.h"
class SwitchAction : public Action
{
	SwitchAction(ApplicationManager* pApp);  // Constructor

	// ============ Virtual Functions ============

	virtual void ReadActionParameters(); // Reads parameters required for action to execute 
	// (code depends on action type so virtual)

	virtual void Execute();  // Executes action (code depends on action type so virtual)

	virtual ~SwitchAction();  // Virtual Destructor
};

