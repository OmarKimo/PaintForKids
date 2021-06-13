#ifndef CHNG_BRD_WDTH_ACT_H
#define CHNG_BRD_WDTH_ACT_H

#include "Action.h"

class ChangBrdWdthAction : public Action
{
	Point P; //The coordinates of chosen color.
	int width; //The chosen border width.

public:

	ChangBrdWdthAction(ApplicationManager *pApp);

	virtual void ReadActionParameters();
	virtual void Execute();

	////To undo this action (code depends on action type)
	//virtual void Undo();

	////To redo this action (code depends on action type)
	//virtual void Redo();

	//virtual bool CanUndo() const;
};

#endif