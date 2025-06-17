#pragma once
#include "../Action.h"
class ClearAction : public Action
{
	// [Action Parameters]
	bool clear;
	// Note: These parameters should be read in ReadActionParameters()

public:
	ClearAction(ApplicationManager* pApp); // A Constructor

	virtual void ReadActionParameters(); // Reads AddCardAction action parameters (cardNumber, cardPosition)

	virtual void Execute(); // Creates a new Card Object of the specific Card Number
	// and Reads the Parameters of This Card Number (if any)
	// then Sets this Card Object to GameObject Pointer of its Cell

	virtual ~ClearAction(); // A Virtual Destructor
};

