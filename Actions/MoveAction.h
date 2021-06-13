#ifndef MOVE_ACTION_H
#define MOVE_ACTION_H

#include "Action.h"

class MoveAction : public Action
{

	Point Destination;
	Point RelPos;

public:

	MoveAction(ApplicationManager* pApp);

	virtual void ReadActionParameters();
	virtual void Execute();

	////To undo this action (code depends on action type)
	//virtual void Undo();

	////To redo this action (code depends on action type)
	//virtual void Redo();

	//virtual bool CanUndo() const;
};

#endif