#ifndef SCRAMBLE_FIND_H
#define SCRAMBLE_FIND_H

#include "Action.h"
#include "..\Figures\CFigure.h"

class ScrambleFind : public Action
{
	bool TheGameIsOn; int CorrectCount; int IncorrectCount;

public:
	
	ScrambleFind(ApplicationManager * pApp);
	~ScrambleFind();
	void ScrambleCopyPaste(CFigure* Fig);
	CFigure* DevSelect(CFigure* Fig);
	CFigure* SelectOneFigure();
	//void Save();
	void Load();
	virtual void ReadActionParameters();
	virtual void Execute();
};

#endif