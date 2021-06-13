#include "SaveAction.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"

SaveAction::SaveAction(ApplicationManager* pApp) : Action(pApp)
{}

void SaveAction::ReadActionParameters()
{
	isOpen = false;
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	pOut->PrintMessage("Save the graph. Enter the file name.");
	filename = pIn->GetSrting(pOut);
	filename += ".txt";
	File.open(filename, ofstream::out);

	if(!File.is_open()) pOut->PrintMessage("Error!! Can't find the file! Unsuccessful saving!");
	else isOpen = true;
}

void SaveAction::Execute()
{
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();

	if(isOpen){
		pManager->SaveAll(File);
		File.close();
	}
	pOut->ClearStatusBar();
}