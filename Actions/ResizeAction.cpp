#include "ResizeAction.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

ResizeAction::ResizeAction(ApplicationManager* pApp):Action(pApp)
{}

void ResizeAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("Resize the selected figure(s): choose the resize factor.");
	pOut->CreateResizeMenu();

	ResizeFactor = pIn->GetChosenFactor();
	pOut->ClearDrawArea();
	pOut->ClearStatusBar();
}

void ResizeAction::Execute()
{
	Output* pOut = pManager->GetOutput();

	if(pManager->getSelectedFigCount() == 0){
		pOut->PrintMessage("Error!! You can't choose 'Resize' operation without selecting any figure!");
		return;
	}

	ReadActionParameters();

	if(ResizeFactor != 1 && !(pManager->ResizeSelected(ResizeFactor))) {pOut->PrintMessage("Error!! The new size of selected figure(s) exceeded the limits of drawing area or is too small!"); return;}
	if(ResizeFactor != 1) pManager->UpdateInterface(true);
	else pManager->UpdateInterface();
}