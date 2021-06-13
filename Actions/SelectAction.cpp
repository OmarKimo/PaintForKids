#include "SelectAction.h"
#include "..\Figures\CFigure.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

SelectAction::SelectAction(ApplicationManager * pApp):Action(pApp)
{}

void SelectAction::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	pOut->PrintMessage("Select Figure(s): Click on a figure");
	pIn->GetPointClicked(P.x, P.y);
	///////////////////////////////////////
	temp.x = (int)((P.x - pOut->getZoomPoint().x) / pow(2, pOut->getZoomScale()) + pOut->getZoomPoint().x);
	temp.y = (int)((P.y - pOut->getZoomPoint().y) / pow(2, pOut->getZoomScale()) + pOut->getZoomPoint().y);

	CFigure* Fig = pManager->GetFigure(temp);

	while(Fig){
		Fig->SetSelected(true);
		pManager->AddSelectedFigure(Fig);
		pManager->UpdateInterface();

		if(pManager->getSelectedFigCount() == 1) pManager->PrintInfoSelected(pOut);
		else if(pManager->getSelectedFigCount() == 0) pOut->PrintMessage("Select Figure(s): Click on a figure");
		else pOut->PrintMessage(to_string(pManager->getSelectedFigCount()));
		
		pIn->GetPointClicked(P.x, P.y);
		///////////////////////////////////////
		temp.x = (int)((P.x - pOut->getZoomPoint().x) / pow(2, pOut->getZoomScale()) + pOut->getZoomPoint().x);
		temp.y = (int)((P.y - pOut->getZoomPoint().y) / pow(2, pOut->getZoomScale()) + pOut->getZoomPoint().y);
		Fig = pManager->GetFigure(temp);
	}
	pOut->ClearStatusBar();

	//Write code to check if the user clicked on an icon that uses the select action
	ActionType Act = pIn->GetUserAction(P, pManager->isInZoom());
	if(Act == RESIZE || Act == ROTATE || Act == DRAW_CLR_d || Act == FILL_CLR_d || Act == BORDER_WIDTH_d || Act == CUT || Act == COPY || Act == DEL || Act == MOVE || Act == PICK_HIDE || Act == FRONT || Act == BACK || Act == MOVE_DRAG || Act == RESIZE_DRAG)
		pManager->ExecuteAction(Act);
}

void SelectAction::Execute()
{
	ReadActionParameters();
	
	pManager->UnSelectFigures();
	pManager->UpdateInterface();
}