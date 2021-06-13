#ifndef COPY_ACTION
#define COPY_ACTION

#include "Action.h"

class copyAction: public Action
{

public:
	copyAction(ApplicationManager * p);
	void ReadActionParameters();
	void Execute();

	////To undo this action (code depends on action type)
	//virtual void Undo();

	////To redo this action (code depends on action type)
	//virtual void Redo();

	//virtual bool CanUndo() const;
};

#endif