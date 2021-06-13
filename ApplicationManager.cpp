#include "ApplicationManager.h"

//Actions
#include "Actions\AddRectAction.h"
#include "Actions\AddCircAction.h"
#include "Actions\AddTriAction.h"
#include "Actions\AddLineAction.h"
#include "Actions\ChangDrawClrAction.h"
#include "Actions\ChangFillClrAction.h"
#include "Actions\ChangBrdWdthAction.h"
#include "Actions\ChangBkGrndClrAction.h"
#include "Actions\ExitAction.h"
#include "Actions\ResizeAction.h"
#include "Actions\RotateAction.h"
#include "Actions\SelectAction.h"
#include "Actions\MoveAction.h"
#include "Actions\BackAction.h"
#include "Actions\CopyAction.h"
#include "Actions\CutAction.h"
#include "Actions\DeleteAction.h"
#include "Actions\FrontAction.h"
#include "Actions\PasteAction.h"
#include "Actions\ToDrawAction.h"
#include "Actions\ToPlayAction.h"
#include "Actions\SaveAction.h"
#include "Actions\LoadAction.h"
#include "Actions\ZoomInAction.h"
#include "Actions\ZoomOutAction.h"
#include "Actions\ScrambleFind.h"
#include "Actions\PickHide.h"

//Figures
#include "Figures\CFigure.h"
#include "Figures\CCircle.h"
#include "Figures\CRectangle.h"
#include "Figures\CTriangle.h"
#include "Figures\CLine.h"

#include <fstream>

//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();
	FigList = new CFigure*[MaxFigCount];
	FigCount = 0;
	SelectedFigCount = 0;
	nextID = 1;
	DefaultFillStatus = false;
	lastSave = false;
	isExited = false;
	inZoom = false;
	inScrambleFind = false;

	copycount = 0;
	mycopy = NULL;
	//Create an array of figure pointers and set them to NULL		
	for (int i = 0; i < MaxFigCount; i++)
		FigList[i] = NULL;
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
ActionType ApplicationManager::GetUserAction(bool isInZoom) const
{
	//Ask the input to get the action from the user.
	return pIn->GetUserAction(isInZoom);
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType)
{
	Action* pAct = NULL;
	clear();
	pOut->ClearStatusBar();

	//According to Action Type, create the corresponding action object
	switch (ActType)
	{
	case DRAW_RECT:
		pAct = new AddRectAction(this);
		break;

	case DRAW_CIRC:
		pAct = new AddCircAction(this);
		break;

	case DRAW_LINE:
		pAct = new AddLineAction(this);
		break;

	case DRAW_TRI:
		pAct = new AddTriAction(this);
		break;

	case DRAW_CLR_d:
		pAct = new ChangDrawClrAction(this);
		break;

	case FILL_CLR_d:
		pAct = new ChangFillClrAction(this);
		break;

	case BORDER_WIDTH_d:
		pAct = new ChangBrdWdthAction(this);
		break;

	case BACKGROUND_CLR:
		pAct = new ChangBkGrndClrAction(this);
		break;

	case SELECT:
		pAct = new SelectAction(this);
		break;

	case RESIZE:
		pAct = new ResizeAction(this);
		break;

	case ZOOM_IN:
		pAct = new ZoomInAction(this);
		break;

	case ZOOM_OUT:
		pAct = new ZoomOutAction(this);
		break;

	case ROTATE:
		pAct = new RotateAction(this);
		break;

	case MOVE:
		pAct = new MoveAction(this);
		break;

	case DEL:
		pAct = new DeleteAction(this);
		break;

	case PASTE:
		pAct = new PasteAction(this);
		break;

	case CUT:
		pAct = new CutAction(this);
		break;

	case COPY:
		pAct = new copyAction(this);
		break;

	case FRONT:
		pAct = new FrontAction(this);
		break;

	case BACK:
		pAct = new BackAction(this);
		break;

	case SAVE:
		pAct = new SaveAction(this);
		break;

	case LOAD:
		pAct = new LoadAction(this);
		break;

	case TO_DRAW:
		pAct = new ToDrawAction(this);
		break;

	case TO_PLAY:
		pAct = new ToPlayAction(this);
		break;

	case SCRAMBLE_FIND:
		pAct = new ScrambleFind(this);
		break;

	case PICK_HIDE:
		pAct = new PickHide(this);
		break;

	case EXIT:
		pAct = new ExitAction(this);
		break;

	case STATUS:	//a click on the status bar ==> no action
		pOut->ClearStatusBar();
		return;

	case EMPTY:
		pOut->ClearStatusBar();
		return;
	}

	//Execute the created action
	if (pAct != NULL)
	{
		pAct->Execute();//Execute
		delete pAct;	//Action is not needed any more ==> delete it
		pAct = NULL;
		if (ActType != SAVE && ActType != LOAD) lastSave = false;
	}
}
//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//

//Add a figure to the list of figures
bool ApplicationManager::AddFigure(CFigure* pFig)
{
	if (FigCount < 200) {
		FigList[FigCount++] = pFig;
		return true;
	}
	return false;
}

void ApplicationManager::AddSelectedFigure(CFigure* pFig)
{
	set<CFigure*>::iterator it = SelectedFigList.find(pFig);
	if (SelectedFigCount < MaxFigCount && it == SelectedFigList.end()) {
		SelectedFigList.insert(pFig);
		SelectedFigCount++;
	}
	else if (it != SelectedFigList.end()) {
		SelectedFigList.erase(pFig);
		pFig->SetSelected(false);
		SelectedFigCount--;
	}
}

void ApplicationManager::UnSelectFigures()
{
	for (set<CFigure*>::iterator it = SelectedFigList.begin(); it != SelectedFigList.end(); it++)
		(*it)->SetSelected(false);
	SelectedFigList.clear();
	SelectedFigCount = 0;
}

int ApplicationManager::getNextID()
{
	return nextID++;
}

void ApplicationManager::PrintInfoSelected(Output* pOut)
{
	for (set<CFigure*>::iterator it = SelectedFigList.begin(); it != SelectedFigList.end(); ++it)
		(*it)->PrintInfo(pOut);
}

bool ApplicationManager::ResizeSelected(float rf)
{
	for (set<CFigure*>::iterator it = SelectedFigList.begin(); it != SelectedFigList.end(); ++it) {
		if (!((*it)->Resize(rf))) {
			for (set<CFigure*>::iterator it1 = SelectedFigList.begin(); it1 != it; ++it1)
				(*it1)->Resize(1 / rf);
			return false;
		}
	}
	return true;
}

bool ApplicationManager::MoveSelected(Point dist)
{
	for (set<CFigure*>::iterator it = SelectedFigList.begin(); it != SelectedFigList.end(); ++it) {
		if (!((*it)->Move(dist))) {
			dist.x *= -1;
			dist.y *= -1;
			for (set<CFigure*>::iterator it1 = SelectedFigList.begin(); it1 != it; ++it1)
				(*it1)->Move(dist);
			return false;
		}
	}
	Front(); //////////////////////
	return true;
}

bool ApplicationManager::RotateSelected(int angle)
{
	for (set<CFigure*>::iterator it = SelectedFigList.begin(); it != SelectedFigList.end(); ++it)
	{
		if (!((*it)->Rotate(angle))) {
			for (set<CFigure*>::iterator it1 = SelectedFigList.begin(); it1 != it; ++it1)
				(*it1)->Rotate(360 - angle);
			return false;
		}
	}
	return true;
}

void ApplicationManager::ChangBrdWdthSelected(int width)
{
	for (set<CFigure*>::iterator it = SelectedFigList.begin(); it != SelectedFigList.end(); ++it)
		(*it)->ChngBrdWdth(width);
}

void ApplicationManager::ChangFillClrSelected_Status(bool status, color clr)
{
	if (status)
		for (set<CFigure*>::iterator it = SelectedFigList.begin(); it != SelectedFigList.end(); ++it)
			(*it)->ChngFillClr(clr);
	else
		for (set<CFigure*>::iterator it = SelectedFigList.begin(); it != SelectedFigList.end(); ++it)
			(*it)->SetFilled(status);
}

void ApplicationManager::ChangDrawClrSelected(color clr)
{
	for (set<CFigure*>::iterator it = SelectedFigList.begin(); it != SelectedFigList.end(); ++it)
		(*it)->ChngDrawClr(clr);
}

void ApplicationManager::SaveAll(ofstream& File)
{
	File << UI.DrawColor.ucRed << ' ' << UI.DrawColor.ucGreen << ' ' << UI.DrawColor.ucBlue;
	if (getDefaultFillStatus()) File << "    " << getDefaultFillStatus() << "  " << UI.FillColor.ucRed << ' ' << UI.FillColor.ucGreen << ' ' << UI.FillColor.ucBlue << "   ";
	else File << "   0   ";
	File << UI.BkGrndColor.ucRed << ' ' << UI.BkGrndColor.ucGreen << ' ' << UI.BkGrndColor.ucBlue;

	File << "\n" << FigCount << "\n";
	for (int i = 0; i < FigCount; i++)
		FigList[i]->Save(File);

	lastSave = true;
}

void ApplicationManager::LoadAll(ifstream& File)
{
	CFigure* Fig = NULL;
	string FigName;
	int figCount;

	File >> UI.DrawColor.ucRed >> UI.DrawColor.ucGreen >> UI.DrawColor.ucBlue >> DefaultFillStatus;
	if (getDefaultFillStatus()) File >> UI.FillColor.ucRed >> UI.FillColor.ucGreen >> UI.FillColor.ucBlue;
	File >> UI.BkGrndColor.ucRed >> UI.BkGrndColor.ucGreen >> UI.BkGrndColor.ucBlue;
	File >> figCount;

	//nextID = figCount;
	//nextID=1;
	FigCount = 0;
	for (int i = 0; i < figCount; i++) {
		File >> FigName;
		if (FigName == "LINE") Fig = new CLine();
		else if (FigName == "CIRCLE") Fig = new CCircle();
		else if (FigName == "RECTANGLE") Fig = new CRectangle();
		else Fig = new CTriangle();

		Fig->Load(File);
		AddFigure(Fig);
	}
	lastSave = true;
}

void ApplicationManager::deleteselect()
{
	for (set<CFigure*>::iterator it = SelectedFigList.begin(); it != SelectedFigList.end(); ++it)
	{
		for (int j = 0; j < FigCount; j++)
		{
			if (*(it) == FigList[j])
			{
				delete FigList[j];
				FigList[j] = NULL;
				for (int i = j; i < FigCount - 1; i++)
					FigList[i] = FigList[i + 1];
				FigList[FigCount - 1] = NULL;
				FigCount--;
			}
		}
	}
	SelectedFigList.clear();
}

void ApplicationManager::copyselect()
{
	copycount = SelectedFigCount;
	if (!mycopy) delete[] mycopy;
	mycopy = new CFigure*[copycount];
	int j = 0;

	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->IsSelected())
		{
			mycopy[j] = FigList[i]->copy();
			j++;
		}
	}
	/*string str = "there are ";
	str = str + to_string(copycount);
	str = str + " had been selected.";
	GetOutput()->PrintMessage(str);*/
}

bool ApplicationManager::pasteselect(Point p)
{
	int start = FigCount;
	for (int j = 0; j < copycount; j++)
		FigList[FigCount++] = mycopy[j]->copy();
	Point C = mycopy[0]->center();
	p.x = p.x - C.x;
	p.y = p.y - C.y;

	for (int i = start; i < FigCount; i++)
	{
		if (!(FigList[i]->Move(p)))
		{
			for (int j = start; j < i; j++) {
				delete FigList[j];
				FigList[j] = NULL;
			}
			FigCount -= copycount;
			return false;
		}
		FigList[i]->setID(getNextID());
		FigList[i]->SetSelected(true);
	}
	return true;
}

void ApplicationManager::Front()
{
	int i = FigCount - 1;
	for (set<CFigure*>::iterator it = SelectedFigList.begin(); it != SelectedFigList.end(); it++)
	{
		CFigure* target = *(it);
		int j = 0;
		for (j = 0; j < FigCount; j++)
			if (FigList[j] == target)
				break;
		for (int k = j; k < i; k++)
			FigList[k] = FigList[k + 1];
		FigList[i] = target;
		i--;
	}

}

void ApplicationManager::Back()
{
	int i = 0;
	for (set<CFigure*>::iterator it = SelectedFigList.begin(); it != SelectedFigList.end(); it++)
	{
		CFigure* target = *(it);
		int j = 0;
		for (j = 0; j < FigCount; j++)
			if (FigList[j] == target)
				break;
		for (int k = j; k > i; k--)
			FigList[k] = FigList[k - 1];
		FigList[i] = target;
		i++;
	}
}

void ApplicationManager::clear()
{
	for (int i = 0; i < FigCount; i++)
		if (FigList[i]) FigList[i]->SetSelected(false);
	for (set <CFigure*>::iterator it = SelectedFigList.begin(); it != SelectedFigList.end(); it++)
		(*it)->SetSelected(true);
}

set<CFigure*>::iterator ApplicationManager::getFirstFigSelected() const
{
	return SelectedFigList.begin();
}

CFigure** ApplicationManager::getFigList() const
{
	return FigList;
}

void ApplicationManager::DeleteSelectedFigure(CFigure* pFig)
{
	SelectedFigList.erase(pFig);
}

void ApplicationManager::ClearSelectedFigList()
{
	SelectedFigList.clear();
}

int ApplicationManager::getFigCount() const
{
	return FigCount;
}

int ApplicationManager::getSelectedFigCount() const
{
	return SelectedFigCount;
}

void ApplicationManager::setfigcount(int n)
{
	FigCount = n;
}

int ApplicationManager::getcopycount()
{
	return copycount;
}

CFigure ** ApplicationManager::getmycopy()
{
	return mycopy;
}

void ApplicationManager::setcopycount(int n)
{
	copycount = n;
}

void ApplicationManager::setmycopy(CFigure ** target)
{
	mycopy = target;
}

void ApplicationManager::ChangeDefaultFillStatus(bool fillStatus)
{
	DefaultFillStatus = fillStatus;
}

bool ApplicationManager::getDefaultFillStatus() const
{
	return DefaultFillStatus;
}

bool ApplicationManager::getlastSave() const
{
	return lastSave;
}

bool ApplicationManager::IsExited() const
{
	return isExited;
}

void ApplicationManager::setExited(bool is)
{
	isExited = is;
}

bool ApplicationManager::isInZoom() const
{
	return inZoom;
}

void ApplicationManager::setInZoom(bool is)
{
	inZoom = is;
}

bool ApplicationManager::isInScrambleFind() const
{
	return inScrambleFind;
}

void ApplicationManager::setInScrambleFind(bool is)
{
	inScrambleFind = is;
}

void ApplicationManager::DeleteFigures()
{
	for (int i = 0; i < FigCount; i++) {
		delete FigList[i];
		FigList[i] = NULL;
	}
	FigCount = 0;
	UnSelectFigures();
}

void ApplicationManager::DeleteFigureByID(int id)
{
	for (int i = 0; i < FigCount; i++) {
		if (FigList[i]->getID() == id) {
			delete FigList[i];
			FigList[i] = NULL;
			for (int j = i; j < FigCount - 1; j++)
				FigList[j] = FigList[j + 1];
			FigList[FigCount - 1] = NULL;
			FigCount--;
			return;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////
CFigure* ApplicationManager::GetFigure(Point P) const
{
	//If a figure is found return a pointer to it.
	//if this point (x,y) does not belong to any figure return NULL

	CFigure* h = NULL;
	for (int i = 0; i < FigCount; i++) {
		if (FigList[i] && FigList[i]->isInside(P))
			h = FigList[i];
	}
	return h;
	//return NULL;
}

//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface(bool s)
{
	pOut->ClearDrawArea();
	if (s) {
		for (set<CFigure*>::iterator it = SelectedFigList.begin(); it != SelectedFigList.end(); ++it)
			(*it)->Draw(pOut);
	}
	else {
		for (int i = 0; i < FigCount; i++)
			FigList[i]->Draw(pOut);		//Call Draw function (virtual member fn)
	}

	if (pOut->getZoomScale() == 0) {
		inZoom = false;
		if (UI.InterfaceMode == MODE_DRAW) pOut->CreateDrawToolBar();
		else pOut->CreatePlayToolBar();
	}
	else {
		inZoom = true;
		pOut->CreateToolBar_Zoom();
		pOut->CreateStatusBar();
	}

	if (inScrambleFind && UI.InterfaceMode == MODE_PLAY) {
		pOut->getpwind()->SetPen(BLACK, 3);
		pOut->getpwind()->SetBrush(BLACK);
		pOut->getpwind()->DrawRectangle(UI.width / 2 - 5, 50, UI.width / 2 + 5, UI.height - UI.StatusBarHeight, FILLED);
	}
	else if (inScrambleFind) inScrambleFind = false;
}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input *ApplicationManager::GetInput() const
{
	return pIn;
}
//Return a pointer to the output
Output *ApplicationManager::GetOutput() const
{
	return pOut;
}
////////////////////////////////////////////////////////////////////////////////////

//Destructor
ApplicationManager::~ApplicationManager()
{
	for (int i = 0; i < FigCount; i++)
		delete FigList[i];
	delete[] FigList;
	delete pIn;
	delete pOut;
}
