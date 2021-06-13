#include "ChangFillClrAction.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

ChangFillClrAction::ChangFillClrAction(ApplicationManager * pApp):Action(pApp)
{}

void ChangFillClrAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("Change Filling color: choose if you want becoming figures (or selected figures) to be filled or not?");
	pOut->CreateFillStatusMenu(pManager->isInZoom());
	exit = pIn->GetChosenStatus(fillStatus, pManager->isInZoom());
	if(!exit){
		pOut->ClearDrawArea();
		pOut->ClearStatusBar();
		return;
	}
	pOut->ClearDrawArea();
	pManager->UpdateInterface();
	if(fillStatus){
		pOut->PrintMessage("Change Filling color: Choose the color");
		pOut->CreatePaletteBar();
		Clr = pIn->GetChosenColor(1);
	}
	pOut->ClearDrawArea();
	pOut->ClearStatusBar();
}

void ChangFillClrAction::Execute()
{
	ReadActionParameters();
	if(!exit) return;

	if(pManager->getSelectedFigCount() > 0){
		if(fillStatus) pManager->ChangFillClrSelected_Status(fillStatus, Clr);
		else pManager->ChangFillClrSelected_Status(fillStatus);
		pManager->UpdateInterface(true);
	}
	else{
		pManager->ChangeDefaultFillStatus(fillStatus); //Becoming
		if(fillStatus){
			Output* pOut = pManager->GetOutput();
			pOut->changeCrntFillColor(Clr); 
		}
	}
}