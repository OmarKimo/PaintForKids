#include "ZoomInAction.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

ZoomInAction::ZoomInAction(ApplicationManager* pApp):Action(pApp)
{}

void ZoomInAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("Zoom In: Click on the point where you want to zoom in.");
	pIn->GetPointClicked(ZoomPoint.x, ZoomPoint.y);
	pOut->ClearStatusBar();
}

void ZoomInAction::Execute()
{
	ReadActionParameters();

	Output* pOut = pManager->GetOutput();
	pOut->CreateToolBar_Zoom();

	pOut->setZoomScale(pOut->getZoomScale()+1);
	pOut->setZoomPoint(ZoomPoint);
}