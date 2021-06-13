#include "CutAction.h"
#include "copyAction.h"
#include "DeleteAction.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

CutAction::CutAction(ApplicationManager* p):Action(p)
{}

void CutAction::ReadActionParameters()
{}

void CutAction::Execute() 
{
	if(pManager->getSelectedFigCount() == 0){
		pManager->GetOutput()->PrintMessage("Error!! You can't choose 'CUT' action without selecting figure(s)!");
		return;
	}
	pManager->ExecuteAction(COPY);
	pManager->ExecuteAction(DEL);
}