#include "AddLineAction.h"
#include "..\Figures\CLine.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

AddLineAction::AddLineAction(ApplicationManager * pApp):Action(pApp)
{}

void AddLineAction::ReadActionParameters() 
{	
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Line: Click at first end");
	
	//Read 1st end and store in point P1
	pIn->GetPointClicked(P1.x, P1.y);

	pOut->PrintMessage("New Line: Click at second end");

	//Read 2nd end and store in point P2
	pIn->GetPointClicked(P2.x, P2.y);
	///////////////////////////////////////
	P1.x = (int)((P1.x - pOut->getZoomPoint().x) / pow(2, pOut->getZoomScale()) + pOut->getZoomPoint().x);
	P1.y = (int)((P1.y - pOut->getZoomPoint().y) / pow(2, pOut->getZoomScale()) + pOut->getZoomPoint().y);

	P2.x = (int)((P2.x - pOut->getZoomPoint().x) / pow(2, pOut->getZoomScale()) + pOut->getZoomPoint().x);
	P2.y = (int)((P2.y - pOut->getZoomPoint().y) / pow(2, pOut->getZoomScale()) + pOut->getZoomPoint().y);

	LineGfxInfo.isFilled = false;	//default is not filled
	//get drawing, filling colors and pen width from the interface
	LineGfxInfo.DrawClr = pOut->getCrntDrawColor();
	LineGfxInfo.FillClr = pOut->getCrntFillColor();
	LineGfxInfo.BorderWdth = pOut->getCrntPenWidth();

	pOut->ClearStatusBar();
}

//Execute the action
void AddLineAction::Execute() 
{
	//This action needs to read some parameters first
	ReadActionParameters();

	//Create a line with the parameters read from the user
	CLine *L = new CLine(P1, P2, LineGfxInfo);

	if(!(L->checkLimits())){
		Output* pOut = pManager->GetOutput();
		pOut->PrintMessage("Error!! You exceeded the limits of drawing area!");
	}
	else{
		id = pManager->getNextID();
		L->setID(id);
		if(!pManager->AddFigure(L)) pManager->GetOutput()->PrintMessage("Error! You exceeded the number of MAX Figures (200)!"); //Add the line to the list of figures
	}
}

//bool AddLineAction::CanUndo() const
//{
//	return true;
//}
//
//void AddLineAction::Undo()
//{
//	pManager->DeleteFigureByID(id);
//}
//
//void AddLineAction::Redo()
//{
//	//ReadActionParameters();
//
//	//Create a line with the parameters read from the user
//	CLine *L = new CLine(P1, P2, LineGfxInfo);
//
//	if(!(L->checkLimits())){
//		Output* pOut = pManager->GetOutput();
//		pOut->PrintMessage("Error!! You exceeded the limits of drawing area!");
//	}
//	else{
//		id = pManager->getNextID();
//		L->setID(id);
//		pManager->AddFigure(L); //Add the line to the list of figures
//	}
//}