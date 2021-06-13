#ifndef CUT_ACTION
#define CUT_ACTION

#include "Action.h"

class CutAction : public Action 
{
public:
	CutAction(ApplicationManager * p);
	virtual void ReadActionParameters();
	virtual void Execute() ;

	////To undo this action (code depends on action type)
	//virtual void Undo();

	////To redo this action (code depends on action type)
	//virtual void Redo();

	//virtual bool CanUndo() const;
};

#endif