#ifndef	ZOOM_IN_ACTION_H
#define ZOOM_IN_ACTION_H

#include "Action.h"

class ZoomInAction : public Action
{
	Point ZoomPoint;

public:

	ZoomInAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();

	////To undo this action (code depends on action type)
	//virtual void Undo();

	////To redo this action (code depends on action type)
	//virtual void Redo();

	//virtual bool CanUndo() const;
};

#endif