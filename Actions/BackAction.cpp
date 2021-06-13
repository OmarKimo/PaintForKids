#include "BackAction.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

BackAction::BackAction(ApplicationManager * p):Action(p)
{}

void BackAction::ReadActionParameters() 
{}

void BackAction::Execute() 
{
	if (pManager->getSelectedFigCount() == 0)
	{
		pManager->GetOutput()->PrintMessage("Error!! There are no figure(s) for sending to front or to back");
		return;
	}
	pManager->Back();
	Output* pOut = pManager->GetOutput();
	pOut->ClearDrawArea();
	pOut->ClearStatusBar();
}
