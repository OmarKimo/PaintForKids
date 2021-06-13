#include "AddRectAction.h"
#include "..\Figures\CRectangle.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

AddRectAction::AddRectAction(ApplicationManager * pApp):Action(pApp)
{}

void AddRectAction::ReadActionParameters() 
{	
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Rectangle: Click at first corner");
	
	//Read 1st corner and store in point P1
	pIn->GetPointClicked(P1.x, P1.y);

	pOut->PrintMessage("New Rectangle: Click at second corner");

	//Read 2nd corner and store in point P2
	pIn->GetPointClicked(P2.x, P2.y);
	////////////////
	P1.x = (int)((P1.x - pOut->getZoomPoint().x) / pow(2, pOut->getZoomScale()) + pOut->getZoomPoint().x);
	P1.y = (int)((P1.y - pOut->getZoomPoint().y) / pow(2, pOut->getZoomScale()) + pOut->getZoomPoint().y);

	P2.x = (int)((P2.x - pOut->getZoomPoint().x) / pow(2, pOut->getZoomScale()) + pOut->getZoomPoint().x);
	P2.y = (int)((P2.y - pOut->getZoomPoint().y) / pow(2, pOut->getZoomScale()) + pOut->getZoomPoint().y);

	RectGfxInfo.isFilled = pManager->getDefaultFillStatus();	//default is not filled
	//get drawing, filling colors and pen width from the interface
	RectGfxInfo.DrawClr = pOut->getCrntDrawColor();
	RectGfxInfo.FillClr = pOut->getCrntFillColor();
	RectGfxInfo.BorderWdth = pOut->getCrntPenWidth();

	pOut->ClearStatusBar();

}

//Execute the action
void AddRectAction::Execute() 
{
	//This action needs to read some parameters first
	ReadActionParameters();
	
	//Create a rectangle with the parameters read from the user
	CRectangle *R = new CRectangle(P1, P2, RectGfxInfo);

	if(!(R->checkLimits())){
		Output* pOut = pManager->GetOutput();
		pOut->PrintMessage("Error!! You exceeded the limits of drawing area!");
	}
	else{
		id = pManager->getNextID();
		R->setID(id);
		if(!pManager->AddFigure(R)) pManager->GetOutput()->PrintMessage("Error! You exceeded the number of MAX Figures (200)!"); //Add the rectangle to the list of figures
	}
}

//bool AddRectAction::CanUndo() const
//{
//	return true;
//}
//
//void AddRectAction::Undo()
//{
//	pManager->DeleteFigureByID(id);
//}
//
//void AddRectAction::Redo()
//{
//	Execute();
//}