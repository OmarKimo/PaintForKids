#ifndef BACK_ACTION
#define BACK_ACTION

#include "Action.h"

class BackAction : public Action
{
public:
	BackAction(ApplicationManager * p);
	virtual void ReadActionParameters();
	virtual void Execute();

	////To undo this action (code depends on action type)
	//virtual void Undo();

	////To redo this action (code depends on action type)
	//virtual void Redo();

	//virtual bool CanUndo() const;
};

#endif