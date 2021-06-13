#ifndef RESIZE_ACTION_H
#define RESIZE_ACTION_H

#include "Action.h"

class ResizeAction : public Action
{
	float ResizeFactor;

public:

	ResizeAction(ApplicationManager*);
	virtual void ReadActionParameters();
	virtual void Execute();

	////To undo this action (code depends on action type)
	//virtual void Undo();

	////To redo this action (code depends on action type)
	//virtual void Redo();

	//virtual bool CanUndo() const;
};

#endif