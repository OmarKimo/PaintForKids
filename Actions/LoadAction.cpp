#include "LoadAction.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"


LoadAction::LoadAction(ApplicationManager* pApp):Action(pApp)
{}

void LoadAction::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	isOpen = false;

	pOut->PrintMessage("Load the graph. Enter the file name.");

	filename = pIn->GetSrting(pOut);
	filename += ".txt";
	File.open(filename, ifstream::in);

	if(!File.is_open()) pOut->PrintMessage("Error! Can't open the file! Unsuccessful loading!");
	else isOpen = true;

}

void LoadAction::Execute()
{
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();

	if(isOpen){
		pManager->DeleteFigures();
		pManager->LoadAll(File);
		File.close();
	}
	//pOut->ClearStatusBar();
}