#include "AddCircAction.h"
#include "..\Figures\CCircle.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

AddCircAction::AddCircAction(ApplicationManager * pApp):Action(pApp)
{}

void AddCircAction::ReadActionParameters() 
{	
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Circle: Click at Center");
	
	//Read center and store in point Center
	pIn->GetPointClicked(Center.x, Center.y);

	pOut->PrintMessage("New Circle: Click at a point on the circle");

	//Read a point on the circle and store in point P
	pIn->GetPointClicked(P.x, P.y);
	//////////////////
	Center.x = (int)((Center.x - pOut->getZoomPoint().x) / pow(2, pOut->getZoomScale()) + pOut->getZoomPoint().x);
	Center.y = (int)((Center.y - pOut->getZoomPoint().y) / pow(2, pOut->getZoomScale()) + pOut->getZoomPoint().y);

	P.x = (int)((P.x - pOut->getZoomPoint().x) / pow(2, pOut->getZoomScale()) + pOut->getZoomPoint().x);
	P.y = (int)((P.y - pOut->getZoomPoint().y) / pow(2, pOut->getZoomScale()) + pOut->getZoomPoint().y);

	CircGfxInfo.isFilled = pManager->getDefaultFillStatus();	//default is not filled

	//get drawing, filling colors and pen width from the interface
	CircGfxInfo.DrawClr = pOut->getCrntDrawColor();
	CircGfxInfo.FillClr = pOut->getCrntFillColor();
	CircGfxInfo.BorderWdth = pOut->getCrntPenWidth();

	pOut->ClearStatusBar();

}

//Execute the action
void AddCircAction::Execute() 
{
	//This action needs to read some parameters first
	ReadActionParameters();

	const int radius = sqrt(pow((P.x-Center.x),2) + pow((P.y-Center.y),2));

	//Create a circle with the parameters read from the user
	CCircle *C = new CCircle(Center, radius, CircGfxInfo);

	if(!(C->checkLimits()))
		pManager->GetOutput()->PrintMessage("Error!! You exceeded the limits of drawing area!");
	else{
		id = pManager->getNextID();
		C->setID(id);
		if(!pManager->AddFigure(C)) pManager->GetOutput()->PrintMessage("Error! You exceeded the number of MAX Figures (200)!"); //Add the circle to the list of figures
	}
}

//bool AddCircAction::CanUndo() const
//{
//	return true;
//}
//
//void AddCircAction::Undo()
//{
//	pManager->DeleteFigureByID(id);
//}
//
//void AddCircAction::Redo()
//{
//	//ReadActionParameters();
//
//	const int radius = sqrt(pow((P.x-Center.x),2) + pow((P.y-Center.y),2));
//
//	//Create a circle with the parameters read from the user
//	CCircle *C = new CCircle(Center, radius, CircGfxInfo);
//
//	if(!(C->checkLimits())){
//		Output* pOut = pManager->GetOutput();
//		pOut->PrintMessage("Error!! You exceeded the limits of drawing area!");
//	}
//	else{
//		id = pManager->getNextID();
//		C->setID(id);
//		pManager->AddFigure(C); //Add the circle to the list of figures
//	}
//}