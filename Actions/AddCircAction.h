#ifndef ADD_CIRC_ACTION_H
#define ADD_CIRC_ACTION_H

#include "Action.h"

//Add Circle Action class
class AddCircAction: public Action
{
private:
	Point Center, P; //Circle center and point on it
	GfxInfo CircGfxInfo;
	int id;

public:
	AddCircAction(ApplicationManager *pApp);

	//Reads circle parameters
	virtual void ReadActionParameters();
	
	//Add circle to the ApplicationManager
	virtual void Execute();

	////To undo this action (code depends on action type)
	//virtual void Undo();

	////To redo this action (code depends on action type)
	//virtual void Redo();

	//virtual bool CanUndo() const;
	
};

#endif