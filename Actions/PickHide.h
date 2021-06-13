#ifndef PICK_HIDE_H
#define PICK_HIDE_H

#include "Action.h"
#include "..\Figures\CFigure.h"

class PickHide : public Action
{
	int GameMode, CorrectCount, IncorrectCount, FullCorrectCount;
	int TheGameIsOn;

public:

	PickHide(ApplicationManager * pApp);
	CFigure* SelectOneFigure();
	//void Save();
	void Load();
	virtual void ReadActionParameters();
	virtual void Execute();
	~PickHide();
};

#endif

