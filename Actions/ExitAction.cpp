#include "ExitAction.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "SaveAction.h"

ExitAction::ExitAction(ApplicationManager* pApp):Action(pApp)
{}

void ExitAction::ReadActionParameters()
{}

void ExitAction::Execute()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("Are you sure you want to exit? (y/n)");
	string c = pIn->GetSrting(pOut);

	if(c == "n" || c == "N") return;
	pManager->setExited(true);
	if(UI.InterfaceMode == MODE_PLAY) return;

	if(!pManager->getlastSave() && pManager->getFigCount() != 0 && (c == "y" || c == "Y")){
		pOut->PrintMessage("Do you want to save before exit? (y/n)");
		c = pIn->GetSrting(pOut);
		if(c == "Y" || c == "y") pManager->ExecuteAction(SAVE);
		else pOut->ClearStatusBar();
	}

	pManager->DeleteFigures();
}