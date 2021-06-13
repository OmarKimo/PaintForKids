#include "DeleteAction.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

DeleteAction::DeleteAction(ApplicationManager * pApp):Action(pApp)
{}

void DeleteAction::ReadActionParameters()
{}

void DeleteAction::Execute()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	if (pManager->getSelectedFigCount() == 0)
	{
		pOut->PrintMessage("Error!! You didn't select any figure(s)! You can't choose 'DELETE' action without selecting any figure(s).");
		return;
	}

	/*set <CFigure*>::iterator SelectedFigList = pManager->getFirstFigSelected();
	CFigure ** listfig = pManager->getFigList();
	int nFigList = pManager->getFigCount();
	int nSelectedFig = pManager->getSelectedFigCount();
	int k=0;

	for (SelectedFigList; k < nSelectedFig; SelectedFigList++)
	{
		nFigList = pManager->getFigCount();
		for (int j=0; j < nFigList; j++)
		{
			if(*(SelectedFigList) == listfig[j])
			{
				delete listfig[j];
				listfig[j] = NULL;
				for (int i=j; i < nFigList-1; i++)
					listfig[i] = listfig[i+1];
				listfig[nFigList-1] = NULL;
				pManager->setfigcount(nFigList-1);
				break;
			}
		}
		k++;
	}
	pManager->ClearSelectedFigList();*/

	pManager->deleteselect();
	pManager->UpdateInterface();
	pOut->ClearStatusBar();
}