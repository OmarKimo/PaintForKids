#include "ScrambleFind.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include <fstream>
#include <vector>

ScrambleFind::ScrambleFind(ApplicationManager * pApp) : Action(pApp)
{
	// call save
	//Save();
}

void ScrambleFind::ScrambleCopyPaste(CFigure* Fig)
{
	Output* pOut = pManager->GetOutput();
	CFigure* mycopy;
	mycopy = Fig->copy();

	if (pManager->getFigCount() > 200)
	{
		pOut->PrintMessage("Error!! You can't play 'Scramble & find' with Max Figures(200)!"); //////////////////////
		return;
	}

	mycopy->setID(mycopy->getID() + 200);
	pManager->AddFigure(mycopy);
	//pManager->getFigList[(pManager->getFigCount())++] = mycopy;
	Point t = mycopy->center();
	Point p;
	while (true)
	{
		p.x = rand() % ((UI.width / 2) - 200) +UI.width/2 +100 ;
		p.y = rand()%(UI.height -300)+150 ; 
		p.x = abs(p.x - t.x);
		p.y = abs(p.y - t.y);

		if (mycopy->ScrambleMove(p)) break;

	}
	//FigList[i]->SetSelected(true);

}

CFigure* ScrambleFind::SelectOneFigure()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	Point P;
	string str = "Correct Answers =";
	str = str + to_string(CorrectCount);
	str = str + " Incorrect Answers=";
	str = str + to_string(IncorrectCount);
	str = str + " Select the matching figure on the right.";
	pOut->PrintMessage(str);
	pIn->GetPointClicked(P.x, P.y);

	if (P.y >= 0 && P.y <= UI.ToolBarHeight && P.x <= 200) { if (P.x <= 100) { pManager->setInScrambleFind(!pManager->isInScrambleFind()); Load();} else if (P.x <= 150) pManager->ExecuteAction(TO_DRAW); else pManager->ExecuteAction(EXIT); TheGameIsOn = 0; return NULL; }////////////////////////////////////

	if (P.x < UI.width / 2) { pOut->PrintMessage("Please select from the RIGHT side"); return NULL;}

	CFigure* Fig = pManager->GetFigure(P);
	if(Fig) {pManager->AddSelectedFigure(Fig); return Fig;}

	pOut->ClearStatusBar();
	return Fig;
}

CFigure* ScrambleFind::DevSelect(CFigure* Fig)
{
	Fig->SetSelected(true);
	pManager->AddSelectedFigure(Fig);
	pManager->UpdateInterface();
	Output* pOut = pManager->GetOutput();
	pManager->PrintInfoSelected(pOut);
	return Fig;
}

void ScrambleFind::ReadActionParameters() 
{}

void ScrambleFind::Execute()
{
	pManager->setInScrambleFind(true);
	Output* pOut = pManager->GetOutput();
	size_t size = pManager->getFigCount();
	vector<CFigure*> vec(size);
	for (int i = 0; i < size; i++)
	{
		vec[i] = pManager->getFigList()[i];
		pManager->getFigList()[i]->ScrambleHalf();
	}
	CFigure** RightHalf = new CFigure*[pManager->getFigCount()];
	int j = 0;
	while (true)
	{
		int r = rand() % (vec.size()) ;
		RightHalf[j] = vec[r]; 
		ScrambleCopyPaste(vec[r]);
		vec.erase(vec.begin() + r);
		if (vec.size() == 0) break;
		j++;
	}
	j = (pManager->getFigCount()/2)-1;
	TheGameIsOn = true;
	CFigure* TFig1, *TFig2;  CorrectCount = 0; IncorrectCount = 0;
	while (TheGameIsOn)
	{
		//int r = rand() % (pManager->getFigCount() / 2);
		//TFig1=DevSelect(pManager->getFigList()[r]);
		TFig1 = DevSelect(RightHalf[j]); 
		pManager->Front();
		pManager->UpdateInterface();

		while (TheGameIsOn)
		{
			TFig2=SelectOneFigure();
			if (TFig2)
			{
				if (TFig1->getID() == TFig2->getID() - 200)
				{
					CorrectCount++;

					pManager->ExecuteAction(DEL);
					//pManager->UpdateInterface();
					break;
				}
				else
				{
					IncorrectCount++;

					pManager->DeleteSelectedFigure(TFig2);
				}
			} 
		}
		j--;
		if(pManager->getFigCount() == 0) TheGameIsOn = 0;
	}
	string str = "Game Over!";
	str += " Correct Answers = ";
	str += to_string(CorrectCount);
	str += " Incorrect Answers= ";
	str += to_string(IncorrectCount);
	str += "   Click anywhere.";
	pOut->PrintMessage(str);
	Point P;
	pManager->GetInput()->GetPointClicked(P.x, P.y);

	Load();
	str = "Game Over!";
	str += " Correct Answers = ";
	str += to_string(CorrectCount);
	str += " Incorrect Answers= ";
	str += to_string(IncorrectCount);
	pOut->PrintMessage(str);
	pManager->setInScrambleFind(false);
}

//void ScrambleFind::Save()
//{
//	ofstream DrawModeFile;
//	DrawModeFile.open("DrawMode.txt", ios::out);
//	pManager->SaveAll(DrawModeFile);
//	DrawModeFile.close();
//}

void ScrambleFind::Load()
{
	pManager->DeleteFigures();
	pManager->GetOutput()->ClearDrawArea();
	ifstream DrawModeFile;
	DrawModeFile.open("DrawMode.txt", ios::in);
	pManager->LoadAll(DrawModeFile);
	DrawModeFile.close();
}

ScrambleFind::~ScrambleFind()
{
	// call load
	/*Load();
	pManager->setInScrambleFind(false);*/
}
