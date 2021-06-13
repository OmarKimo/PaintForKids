#ifndef INPUT_H
#define INPUT_H

#include "..\DEFS.h"
#include "UI_Info.h" 
#include "..\CMUgraphicsLib\CMUgraphics.h"

class Output;
class Input		//The application manager should have a pointer to this class
{
private:
	window *pWind;	//Pointer to the Graphics Window
public:
	Input(window *pW);		//Consturctor
	void GetPointClicked(int &x, int &y) const;//Get coordinate where user clicks
	string GetSrting(Output* pO) const ;	 //Returns a string entered by the user

	ActionType GetUserAction(bool isInZoom = false) const; //Read the user click and map to an action
	ActionType GetUserAction(Point, bool isInZoom = false) const; 

	color GetChosenColor(int) const;	
	int GetChosenPenWidth() const;	
	int GetChosenAngle() const;	//For Rotate Parameters 
	float GetChosenFactor() const;	//For Resize Parameters 
	bool GetChosenStatus(bool& status, bool isInZoom = false) const; //For Fill 
	int GetChosenGameMode() const;

	~Input();
};

#endif