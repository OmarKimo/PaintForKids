#include "PickHide.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include <string>
#include <iostream>
#include <fstream>

PickHide::PickHide(ApplicationManager * pApp) : Action(pApp)
{
	// call save
	//Save();
}

CFigure* PickHide::SelectOneFigure()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	Point P;
	string str;

	if (CorrectCount == 0 && IncorrectCount == 0)
	{
		if (GameMode == 3 ) str = "Select the Biggest or Smallest Figure to start the game.";
		else if (GameMode == 0 || GameMode == 1 || GameMode == 2) str = "Select a Figure to start the game";
		else { TheGameIsOn = 0; return NULL; }
		pOut->PrintMessage(str);

	}
	else {
		str = " Correct Answers = ";
		str += to_string(CorrectCount);
		str += " Incorrect Answers = ";
		str += to_string(IncorrectCount);
		str += ". Select another Figure";
		pOut->PrintMessage(str);

	}

	CFigure* OFig = NULL;
	while (!(OFig))
	{
		pIn->GetPointClicked(P.x, P.y);
		OFig = pManager->GetFigure(P);
		if (P.y >= 0 && P.y <= UI.ToolBarHeight && P.x <= 200) { if (P.x <= 100) Load(); else if (P.x <= 150) pManager->ExecuteAction(TO_DRAW); else pManager->ExecuteAction(EXIT); TheGameIsOn = 0; return NULL; }
	}

	pManager->AddSelectedFigure(OFig);
	pOut->ClearStatusBar();
	return OFig;
}

void PickHide::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("Pick & Hide: Choose the game mode");
	pOut->CreatePickHideBar();
	GameMode = pIn->GetChosenGameMode();
	pOut->ClearStatusBar();
	pManager->UpdateInterface();
}

void PickHide::Execute()
{
	ReadActionParameters();

	Output* pOut = pManager->GetOutput();
	CorrectCount = 0; IncorrectCount = 0; FullCorrectCount = 0;
	CFigure* Fig = SelectOneFigure();

	CFigure** FigListPlay = pManager->getFigList();
	int nFigList = pManager->getFigCount();

	TheGameIsOn = 1;

	if (Fig)
	{
		int FigType = Fig->getType();
		int FigBlue = Fig->getFillClr().ucBlue;
		int FigRed = Fig->getFillClr().ucRed;
		int FigGreen = Fig->getFillClr().ucGreen;

		if (GameMode == 0)//Figure Type
		{
			pManager->deleteselect();
			//To Update after deleting
			nFigList = pManager->getFigCount();
			FigListPlay = pManager->getFigList();

			pManager->UpdateInterface();
			for (int i = 0; i < nFigList; i++)
				if (FigType == FigListPlay[i]->getType())  FullCorrectCount++;

			if (nFigList == 0) { pOut->PrintMessage("Not Enough Figures!"); TheGameIsOn = 0; }
			if (FullCorrectCount == 0) TheGameIsOn = 0;

			while (TheGameIsOn == 1)
			{
				CFigure* TFig = SelectOneFigure();
				if (TFig && FigType == TFig->getType())
				{
					if (++CorrectCount == FullCorrectCount) TheGameIsOn = 0;
					pManager->deleteselect();

					FigListPlay = pManager->getFigList();
					nFigList = pManager->getFigCount();

					pOut->ClearStatusBar();
					pManager->UpdateInterface();
				}
				else if (TFig)
				{
					IncorrectCount++;
					pManager->UpdateInterface();
					pManager->DeleteSelectedFigure(TFig);
				}
			}
		}

		else if (GameMode == 1)
		{
			pManager->deleteselect();

			FigListPlay = pManager->getFigList();
			nFigList = pManager->getFigCount();

			pManager->UpdateInterface();
			for (int i = 0; i < nFigList; i++)
				if (FigBlue == FigListPlay[i]->getFillClr().ucBlue &&
					FigRed == FigListPlay[i]->getFillClr().ucRed &&
					FigGreen == FigListPlay[i]->getFillClr().ucGreen) {
					FullCorrectCount++;
				}

			if (nFigList == 0) { pOut->PrintMessage("Not Enough Figures!"); TheGameIsOn = 0; }
			if (FullCorrectCount == 0) TheGameIsOn = 0;

			while (TheGameIsOn == 1)
			{

				CFigure* TFig = SelectOneFigure();
				if (TFig &&FigBlue == TFig->getFillClr().ucBlue &&
					FigRed == TFig->getFillClr().ucRed &&
					FigGreen == TFig->getFillClr().ucGreen)
				{
					if (++CorrectCount == FullCorrectCount) { TheGameIsOn = 0; }
					pManager->deleteselect();

					FigListPlay = pManager->getFigList();
					nFigList = pManager->getFigCount();

					pOut->ClearStatusBar();
					pManager->UpdateInterface();

				}
				else if (TFig)
				{
					IncorrectCount++;
					pManager->UpdateInterface();
					pManager->DeleteSelectedFigure(TFig);
				}
			}
		} // Fill Color

		else if (GameMode == 2)
		{
			pManager->deleteselect();

			FigListPlay = pManager->getFigList();
			nFigList = pManager->getFigCount();

			pManager->UpdateInterface();
			for (int i = 0; i < nFigList; i++)
				if (FigType == FigListPlay[i]->getType() &&
					FigBlue == FigListPlay[i]->getFillClr().ucBlue &&
					FigRed == FigListPlay[i]->getFillClr().ucRed &&
					FigGreen == FigListPlay[i]->getFillClr().ucGreen) {
					FullCorrectCount++;
				}

			if (nFigList == 0) { pOut->PrintMessage("Not Enough Figures!"); TheGameIsOn = 0; }
			if (FullCorrectCount == 0) TheGameIsOn = 0;

			while (TheGameIsOn == 1)
			{

				CFigure* TFig = SelectOneFigure();
				if (TFig&&FigType == TFig->getType() &&
					FigBlue == TFig->getFillClr().ucBlue &&
					FigRed == TFig->getFillClr().ucRed &&
					FigGreen == TFig->getFillClr().ucGreen)
				{
					if (++CorrectCount == FullCorrectCount) { TheGameIsOn = 0; }
					pManager->deleteselect();

					FigListPlay = pManager->getFigList();
					nFigList = pManager->getFigCount();

					pOut->ClearStatusBar();
					pManager->UpdateInterface();
				}
				else if (TFig)
				{
					IncorrectCount++;
					pManager->UpdateInterface();
					pManager->DeleteSelectedFigure(TFig);
				}
			}
		} // Type & Color   

		else if (GameMode == 3 )// Area 
		{
			CFigure* Biggest; CFigure* Smallest;
			Biggest = FigListPlay[0]; 	Smallest = FigListPlay[0];
			while (TheGameIsOn == 1)
			{
				if (!(CorrectCount == 0 && IncorrectCount == 0)) Fig = SelectOneFigure();

				Biggest = FigListPlay[0]; 	Smallest = FigListPlay[0];

				for (int i = 0; i < nFigList; i++)
				{
					if (FigListPlay[i]->area() > Biggest->area()) Biggest = FigListPlay[i];
					if (FigListPlay[i]->area() < Smallest->area() && FigListPlay[i]) Smallest = FigListPlay[i];

				}

				if (Fig && Fig->area() == Smallest->area()) {
					if (CorrectCount == 0 && IncorrectCount == 0) { GameMode = 3; CorrectCount++; pManager->deleteselect(); FigListPlay = pManager->getFigList();  nFigList = pManager->getFigCount(); pOut->ClearStatusBar(); pManager->UpdateInterface(); }
					else if (GameMode == 3) { CorrectCount++; pManager->deleteselect(); FigListPlay = pManager->getFigList();  nFigList = pManager->getFigCount();  pOut->ClearStatusBar();	   pManager->UpdateInterface(); }
				}

				else if (Fig && Fig->area() == Biggest->area()) {
					if (CorrectCount == 0 && IncorrectCount == 0) { GameMode = 3; CorrectCount++;  pManager->deleteselect();  FigListPlay = pManager->getFigList();  nFigList = pManager->getFigCount();  pOut->ClearStatusBar();  pManager->UpdateInterface(); }
					else if (GameMode == 3) { CorrectCount++; pManager->deleteselect();  FigListPlay = pManager->getFigList();  nFigList = pManager->getFigCount();  pOut->ClearStatusBar();	   pManager->UpdateInterface(); }
				}

				else if (Fig) { IncorrectCount++; pManager->DeleteSelectedFigure(Fig); pManager->UpdateInterface(); }

				if (nFigList == 0) TheGameIsOn = 0;
			}
		}
		string str = "Game Over! ";
		str += " Correct Answers = ";
		str += to_string(CorrectCount);
		str += " Incorrect Answers = ";
		str += to_string(IncorrectCount);
		pOut->PrintMessage(str);
	}
	Load();
}

//void PickHide::Save()
//{
//	ofstream DrawModeFile;
//	DrawModeFile.open("DrawMode.txt", ios::out);
//	pManager->SaveAll(DrawModeFile);
//	DrawModeFile.close();
//}

void PickHide::Load()
{
	pManager->DeleteFigures();
	ifstream DrawModeFile;
	DrawModeFile.open("DrawMode.txt", ios::in);
	pManager->LoadAll(DrawModeFile);
	DrawModeFile.close();
}

PickHide::~PickHide()
{
	// call load
	/*pManager->DeleteFigures();
	ifstream DrawModeFile;
	DrawModeFile.open("DrawMode.txt", ios::in);
	pManager->LoadAll(DrawModeFile);
	DrawModeFile.close();*/

}
