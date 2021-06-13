#include "FrontAction.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

FrontAction::FrontAction(ApplicationManager * p):Action(p)
{}

void FrontAction::ReadActionParameters() 
{
}
void FrontAction::Execute()
{
	if (pManager->getSelectedFigCount() ==0)
	{
		pManager->GetOutput()->PrintMessage("Error! There are no selected figure(s) to send to front or back.");
		return;
	}
	pManager->Front();
	this->pManager->GetOutput()->ClearDrawArea();
	this->pManager->GetOutput()->ClearStatusBar();
}