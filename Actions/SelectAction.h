#ifndef SELECT_ACTION_H
#define SELECT_ACTION_H

#include "Action.h"

class SelectAction : public Action
{
	Point P;
	Point temp;

public:

	SelectAction(ApplicationManager*);

	virtual void ReadActionParameters();
	virtual void Execute();

	////To undo this action (code depends on action type)
	//virtual void Undo();

	////To redo this action (code depends on action type)
	//virtual void Redo();

	//virtual bool CanUndo() const;
};

#endif