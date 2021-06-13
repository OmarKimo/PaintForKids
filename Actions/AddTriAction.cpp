#include "AddTriAction.h"
#include "..\Figures\CTriangle.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

AddTriAction::AddTriAction(ApplicationManager * pApp):Action(pApp)
{}

void AddTriAction::ReadActionParameters() 
{	
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Triangle: Click at first corner");
	
	//Read 1st corner and store in point P1
	pIn->GetPointClicked(P1.x, P1.y);

	pOut->PrintMessage("New Triangle: Click at second corner");

	//Read 2nd corner and store in point P2
	pIn->GetPointClicked(P2.x, P2.y);
	///////////////////////////////////
	P1.x = (int)((P1.x - pOut->getZoomPoint().x) / pow(2, pOut->getZoomScale()) + pOut->getZoomPoint().x);
	P1.y = (int)((P1.y - pOut->getZoomPoint().y) / pow(2, pOut->getZoomScale()) + pOut->getZoomPoint().y);

	P2.x = (int)((P2.x - pOut->getZoomPoint().x) / pow(2, pOut->getZoomScale()) + pOut->getZoomPoint().x);
	P2.y = (int)((P2.y - pOut->getZoomPoint().y) / pow(2, pOut->getZoomScale()) + pOut->getZoomPoint().y);

	P3.x = (int)((P3.x - pOut->getZoomPoint().x) / pow(2, pOut->getZoomScale()) + pOut->getZoomPoint().x);
	P3.y = (int)((P3.y - pOut->getZoomPoint().y) / pow(2, pOut->getZoomScale()) + pOut->getZoomPoint().y);

	pOut->PrintMessage("New Triangle: Click at third corner");
	
	//Read 3rd corner and store in point P3
	pIn->GetPointClicked(P3.x, P3.y);

	TriGfxInfo.isFilled = pManager->getDefaultFillStatus();	//default is not filled
	//get drawing, filling colors and pen width from the interface
	TriGfxInfo.DrawClr = pOut->getCrntDrawColor();
	TriGfxInfo.FillClr = pOut->getCrntFillColor();
	TriGfxInfo.BorderWdth = pOut->getCrntPenWidth();

	pOut->ClearStatusBar();

}

//Execute the action
void AddTriAction::Execute() 
{
	//This action needs to read some parameters first
	ReadActionParameters();
	
	//Create a Triangle with the parameters read from the user
	CTriangle *T = new CTriangle(P1, P2, P3, TriGfxInfo);

	if(!(T->checkLimits())){
		Output* pOut = pManager->GetOutput();
		pOut->PrintMessage("Error!! You exceeded the limits of drawing area!");
	}
	else{
		id = pManager->getNextID();
		T->setID(id);
		if(!pManager->AddFigure(T)) pManager->GetOutput()->PrintMessage("Error! You exceeded the number of MAX Figures (200)!"); //Add the Triangle to the list of figures
	}
}

//bool AddTriAction::CanUndo() const
//{
//	return true;
//}
//
//void AddTriAction::Undo()
//{
//	pManager->DeleteFigureByID(id);
//}
//
//void AddTriAction::Redo()
//{
//	Execute();
//}