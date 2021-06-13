#include "copyAction.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

copyAction::copyAction(ApplicationManager * p):Action(p)
{}

void copyAction::ReadActionParameters()
{}

void copyAction::Execute()
{
	if (pManager->getSelectedFigCount() == 0){
		pManager->GetOutput()->PrintMessage("Error!! There are no selected figure(s)! You can't choose 'COPY' action without selecting any figure(s).");
		return;
	}
	
	/*pManager->setcopycount(pManager->getSelectedFigCount());
	CFigure **mycopy = pManager->getmycopy();
	set <CFigure*>::iterator SelectedFigList = pManager->getFirstFigSelected();
	mycopy = new CFigure*[pManager->getcopycount()];
	pManager->setmycopy(mycopy);
	int j=0, i=0;
	int nSelected = pManager->getSelectedFigCount();
	for (SelectedFigList; i<nSelected; SelectedFigList++)
	{
		mycopy[j++] = (*SelectedFigList)->copy();
		i++;
	}*/

	pManager->copyselect();
	string str = "There are ";
	str += to_string(pManager->getcopycount());
	str += " figures had been selected.";
	pManager->GetOutput()->PrintMessage(str);
}
