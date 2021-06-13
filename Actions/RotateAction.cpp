#include "RotateAction.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

RotateAction::RotateAction(ApplicationManager* pApp):Action(pApp)
{}

void RotateAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("Rotate the selected figure(s): choose the rotate angle.");
	pOut->CreateRotateMenu();

	RotateAngle = pIn->GetChosenAngle();
	pOut->ClearDrawArea();
	pOut->ClearStatusBar();
}

void RotateAction::Execute()
{
	Output* pOut = pManager->GetOutput();

	if(pManager->getSelectedFigCount() == 0){
		pOut->PrintMessage("Error!! You can't choose 'Rotate' operation without selecting any figure!");
		return;
	}
	ReadActionParameters();

	if(RotateAngle != 0 && !(pManager->RotateSelected(RotateAngle))) {pOut->PrintMessage("Error!! The rotated version of selected figure(s) exceeded the limits of drawing area!"); return;}
	if(RotateAngle != 0) pManager->UpdateInterface(true);
	else pManager->UpdateInterface();
}