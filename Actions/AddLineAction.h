#ifndef ADD_LINE_ACTION_H
#define ADD_LINE_ACTION_H

#include "Action.h"

//Add Line Action class
class AddLineAction: public Action
{
private:
	Point P1, P2; //Line edges (ends)
	GfxInfo LineGfxInfo;
	int id;

public:
	AddLineAction(ApplicationManager *pApp);

	//Reads line parameters
	virtual void ReadActionParameters();
	
	//Add line to the ApplicationManager
	virtual void Execute() ;

	////To undo this action (code depends on action type)
	//virtual void Undo();

	////To redo this action (code depends on action type)
	//virtual void Redo();

	//virtual bool CanUndo() const;
	
};

#endif