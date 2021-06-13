#include "ToPlayAction.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include <fstream>

ToPlayAction::ToPlayAction(ApplicationManager* pApp):Action(pApp)
{}

void ToPlayAction::ReadActionParameters()
{}

void ToPlayAction::Execute()
{
	if(pManager->getFigCount() < 2) {pManager->GetOutput()->PrintMessage("Error! You can't play with less than two figures!"); return;}
	Output* pOut = pManager->GetOutput();
	ofstream DrawModeFile;
	DrawModeFile.open("DrawMode.txt", ios::out);
	pManager->SaveAll(DrawModeFile);
	DrawModeFile.close();

	pOut->PrintMessage("Switch to Play mode Action.");
	pOut->CreatePlayToolBar();
	pOut->ClearDrawArea();
}