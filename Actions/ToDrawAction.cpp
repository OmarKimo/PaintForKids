#include "ToDrawAction.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include <fstream>

ToDrawAction::ToDrawAction(ApplicationManager* pApp):Action(pApp)
{}

void ToDrawAction::ReadActionParameters()
{}

void ToDrawAction::Execute()
{
	Output* pOut = pManager->GetOutput();

	pOut->PrintMessage("Switch to Draw mode Action.");
	pOut->CreateDrawToolBar();
	//pOut->count = 0;
	pOut->ClearDrawArea();

	ifstream DrawModeFile;
	DrawModeFile.open("DrawMode.txt", ios::in);
	pManager->LoadAll(DrawModeFile);
	DrawModeFile.close();
}