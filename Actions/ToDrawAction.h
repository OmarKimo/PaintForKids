#ifndef TO_DRAW_ACTION
#define TO_DRAW_ACTION

#include "Action.h"

class ToDrawAction : public Action
{

public:

	ToDrawAction(ApplicationManager* pApp);

	virtual void ReadActionParameters();
	virtual void Execute();

	////To undo this action (code depends on action type)
	//virtual void Undo();

	////To redo this action (code depends on action type)
	//virtual void Redo();

	//virtual bool CanUndo() const;
};

#endif