#ifndef FRONT_ACTION
#define FRONT_ACTION

#include "Action.h"

class FrontAction : public Action
{
public:
	FrontAction(ApplicationManager * p);
	virtual void ReadActionParameters() ;
	virtual void Execute();

	////To undo this action (code depends on action type)
	//virtual void Undo();

	////To redo this action (code depends on action type)
	//virtual void Redo();

	//virtual bool CanUndo() const;
};

#endif