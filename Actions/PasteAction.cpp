#include "PasteAction.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

PasteAction::PasteAction(ApplicationManager * p):Action(p)
{}

void PasteAction::ReadActionParameters()
{
	pManager->GetInput()->GetPointClicked(NewLocation.x,NewLocation.y);
}

void PasteAction::Execute()
{
	pManager->GetOutput()->PrintMessage("Paste Action: Choose the new postion.");
	ReadActionParameters();

	int FigCount = pManager->getFigCount();
	int CopyCount = pManager->getcopycount();

	if (FigCount + CopyCount > 200)
	{
		pManager->GetOutput()->PrintMessage("Error!! You can't paste, number of figures will be more than 200 (Max no. of figures)! ");
		return;
	}
	if(!pManager->pasteselect(NewLocation)){
		pManager->GetOutput()->PrintMessage("Error! You can't paste at this point. Some figure(s) will exceed the limits of drawing area!");
		return;
	}

	pManager->GetOutput()->PrintMessage("Paste is done!");
	//pManager->GetOutput()->ClearStatusBar();
}