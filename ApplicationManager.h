#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "DEFS.h"
#include "Figures\CFigure.h"
#include "GUI\input.h"
#include "GUI\output.h"
#include <algorithm>
#include <set>
#include <fstream>
#include <iostream>
#include "Actions\Action.h"
using namespace std;

//Main class that manages everything in the application.
class ApplicationManager
{
	enum {MaxFigCount = 400};	//Max no of figures
	int FigCount;		//Actual number of figures
	CFigure** FigList;	//List of all figures (Array of pointers)

	set <CFigure*> SelectedFigList; 

	int SelectedFigCount; 
	bool DefaultFillStatus;
	bool lastSave;
	bool isExited;
	bool inZoom;
	bool inScrambleFind;

	CFigure ** mycopy; 
	int copycount; 
	int nextID; 

	//Pointers to Input and Output classes
	Input *pIn;
	Output *pOut;

public:	
	ApplicationManager(); 
	~ApplicationManager();
	
	// -- Action-Related Functions
	//Reads the input command from the user and returns the corresponding action type
	ActionType GetUserAction(bool isInZoom = false) const;
	void ExecuteAction(ActionType) ; //Creates an action and executes it
	
	// -- Figures Management Functions
	bool AddFigure(CFigure* pFig); //Adds a new figure to the FigList
	CFigure *GetFigure(Point) const; //Search for a figure given a point inside the figure
	void DeleteFigureByID(int id);

	void AddSelectedFigure(CFigure* pFig); 
	int getSelectedFigCount() const;
	set<CFigure*>::iterator getFirstFigSelected() const;
	CFigure** getFigList() const;
	void DeleteSelectedFigure(CFigure*);
	void ClearSelectedFigList();

	void DeleteFigures();
	bool getDefaultFillStatus() const; 
	bool getlastSave() const;
	bool IsExited() const;
	void setExited(bool is);

	bool isInZoom() const;
	void setInZoom(bool);

	bool isInScrambleFind() const;
	void setInScrambleFind(bool);

	int getFigCount() const;
	int getNextID(); 

	void UnSelectFigures(); 
	void PrintInfoSelected(Output*);
	bool ResizeSelected(float); 
	bool RotateSelected(int angle); 
	void ChangBrdWdthSelected(int width); 
	void ChangFillClrSelected_Status(bool, color clr = UI.FillColor); 
	void ChangDrawClrSelected(color clr); 
	void ChangeDefaultFillStatus(bool fillStatus); 
	bool MoveSelected(Point dist);
	void deleteselect();
	void copyselect(); 
	bool pasteselect(Point p);
	void SaveAll(ofstream& File); //Save function for each figure
	void LoadAll(ifstream& File);	//Load function for each figure
	void Front(); 
	void Back();
	void clear();

	CFigure ** getmycopy();
	int getcopycount();
	void setfigcount(int n);
	void setcopycount(int n);
	void setmycopy(CFigure ** target);

	// -- Interface Management Functions
	Input *GetInput() const;	//Return pointer to the input
	Output *GetOutput() const;	//Return pointer to the output
	void UpdateInterface(bool s= false);	//Redraws all the drawing window	

};

#endif