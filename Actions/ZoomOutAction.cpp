#include "ZoomOutAction.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

ZoomOutAction::ZoomOutAction(ApplicationManager* pApp):Action(pApp)
{}

void ZoomOutAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("Zoom Out: Click on the point where you want to zoom out.");
	pIn->GetPointClicked(ZoomPoint.x, ZoomPoint.y);
	pOut->ClearStatusBar();
}

void ZoomOutAction::Execute()
{
	ReadActionParameters();

	Output* pOut = pManager->GetOutput();
	pOut->CreateToolBar_Zoom();

	pOut->setZoomScale(pOut->getZoomScale()-1);
	pOut->setZoomPoint(ZoomPoint);
}