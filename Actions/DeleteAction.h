#ifndef DELETE_ACTION
#define DELETE_ACTION

#include "Action.h"

class DeleteAction : public Action 
{

public:
	DeleteAction(ApplicationManager * p);

	void ReadActionParameters() ;
	virtual void Execute() ;

	////To undo this action (code depends on action type)
	//virtual void Undo();

	////To redo this action (code depends on action type)
	//virtual void Redo();

	//virtual bool CanUndo() const;
};

#endif