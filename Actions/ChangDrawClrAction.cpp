#include "ChangDrawClrAction.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

ChangDrawClrAction::ChangDrawClrAction(ApplicationManager * pApp):Action(pApp)
{}

void ChangDrawClrAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("Change Drawing color: Choose the color");
	
	pOut->CreatePaletteBar();
	Clr = pIn->GetChosenColor(0);
	pOut->ClearDrawArea();
	pOut->ClearStatusBar();
}

void ChangDrawClrAction::Execute()
{
	ReadActionParameters();
	
	if(pManager->getSelectedFigCount() > 0){
		pManager->ChangDrawClrSelected(Clr);
		pManager->UpdateInterface(true);
	}
	else{
		Output* pOut = pManager->GetOutput();
		pOut->changeCrntDrawColor(Clr);
	}
}