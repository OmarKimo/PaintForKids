#ifndef ROTATE_ACTION_H
#define ROTATE_ACTION_H

#include "Action.h"

class RotateAction : public Action
{
	int RotateAngle;
	bool isSelected;

public:

	RotateAction(ApplicationManager*);
	virtual void ReadActionParameters();
	virtual void Execute();

	////To undo this action (code depends on action type)
	//virtual void Undo();

	////To redo this action (code depends on action type)
	//virtual void Redo();

	//virtual bool CanUndo() const;
};

#endif