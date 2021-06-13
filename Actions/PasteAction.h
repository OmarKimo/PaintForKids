#ifndef PASTE_ACTION
#define PASTE_ACTION

#include "Action.h"

class PasteAction:public Action
{
	Point NewLocation;
public:
	PasteAction(ApplicationManager* p);

	virtual void ReadActionParameters();
	virtual void Execute();

	////To undo this action (code depends on action type)
	//virtual void Undo();

	////To redo this action (code depends on action type)
	//virtual void Redo();

	//virtual bool CanUndo() const;
};

#endif