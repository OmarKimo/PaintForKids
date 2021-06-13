#ifndef CHNG_FILL_CLR_ACT_H
#define CHNG_FILL_CLR_ACT_H

#include "Action.h"

class ChangFillClrAction : public Action
{
	Point P; //The coordinates of chosen color.
	color Clr; //The chosen color
	bool exit;
	bool fillStatus;

public:

	ChangFillClrAction(ApplicationManager *pApp);

	virtual void ReadActionParameters();
	virtual void Execute();

	////To undo this action (code depends on action type)
	//virtual void Undo();

	////To redo this action (code depends on action type)
	//virtual void Redo();

	//virtual bool CanUndo() const;
};

#endif