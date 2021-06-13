#include "MoveAction.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

MoveAction::MoveAction(ApplicationManager* pApp):Action(pApp)
{}


void MoveAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("Move: Click on a position to move the selected figure(s).");
	pIn->GetPointClicked(Destination.x, Destination.y);

	set<CFigure*>::iterator it = pManager->getFirstFigSelected();
	RelPos.x = Destination.x - (*it)->center().x;
	RelPos.y = Destination.y - (*it)->center().y;

}

void MoveAction::Execute()
{
	Output* pOut = pManager->GetOutput();

	if(pManager->getSelectedFigCount() == 0) {
		pOut->PrintMessage("Error!! You can't choose 'Move' operation without selecting any figure!"); 
		return;
	}
	ReadActionParameters();
	pOut->ClearStatusBar();

	if(!(pManager->MoveSelected(RelPos))){
		pOut->PrintMessage("Error! Some Selected Figures exceeded the limits of drawing area when moved!");
		return;
	}
	else pManager->UpdateInterface(true);
	pOut->ClearDrawArea();
}