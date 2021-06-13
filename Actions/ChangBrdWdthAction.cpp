#include "ChangBrdWdthAction.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

ChangBrdWdthAction::ChangBrdWdthAction(ApplicationManager * pApp):Action(pApp)
{}

void ChangBrdWdthAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("Change Border width: Choose the width");
	
	pOut->CreateBorderMenu();
	width = pIn->GetChosenPenWidth();
	pOut->ClearStatusBar();
}

void ChangBrdWdthAction::Execute()
{
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();

	if(pManager->getSelectedFigCount() > 0) {
		pManager->ChangBrdWdthSelected(width);
		pManager->UpdateInterface(true);
	}
	else pOut->changeCrntPenWidth(width);

	pOut->ClearDrawArea();
}