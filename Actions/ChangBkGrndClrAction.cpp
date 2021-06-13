#include "ChangBkGrndClrAction.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

ChangBkGrndClrAction::ChangBkGrndClrAction(ApplicationManager * pApp):Action(pApp)
{}

void ChangBkGrndClrAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("Change Background color: Choose the color");
	
	pOut->CreatePaletteBar();
	string BGN="images\\MenuItems\\icon for background.jpg";
	pOut->getpwind()->DrawImage(BGN, PALETTE_COUNT*40,50,300,300);
	Clr = pIn->GetChosenColor(2);
	pOut->ClearStatusBar();
}

void ChangBkGrndClrAction::Execute()
{
	ReadActionParameters();

	Output* pOut = pManager->GetOutput();
	if ( Clr.ucBlue==0 && Clr.ucGreen ==0 && Clr.ucRed ==0)
	{
		if (pManager->GetOutput()->count >=18)
			pManager->GetOutput()->count =0;
		pManager->GetOutput()->count++;
	}
	else
	{
		pManager->GetOutput()->count=0;
		pOut->changeCrntBkGrndColor(Clr);
	}
	pOut->ClearDrawArea();
}