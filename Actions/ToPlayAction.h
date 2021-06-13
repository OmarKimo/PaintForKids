#ifndef TO_PLAY_ACTION
#define TO_PLAY_ACTION

#include "Action.h"

class ToPlayAction : public Action
{

public:

	ToPlayAction(ApplicationManager* pApp);

	virtual void ReadActionParameters();
	virtual void Execute();

	////To undo this action (code depends on action type)
	//virtual void Undo();

	////To redo this action (code depends on action type)
	//virtual void Redo();

	//virtual bool CanUndo() const;
};

#endif