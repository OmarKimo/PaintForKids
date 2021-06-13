#ifndef CFIGURE_H
#define CFIGURE_H

#include "..\defs.h"
#include "..\GUI\Output.h"
#include <string>
#include <fstream>
#include <cmath>

enum MyType {
	LINE,
	RECTANGLE,
	TRIANGLE,
	CIRCLE
};

//Base class for all figures
class CFigure
{
protected:
	unsigned int ID;		//Each figure has an ID
	bool Selected;	//true if the figure is selected.
	GfxInfo FigGfxInfo;	//Figure graphis info
	
	MyType Type;

	/// Add more parameters if needed.

public:
	CFigure();
	CFigure(GfxInfo FigureGfxInfo);

	void SetSelected(bool s);	//select/unselect the figure
	bool IsSelected() const;	//check whether fig is selected

	void setID(int id);
	int getID() const;

	MyType getType() const;
	void setType(MyType T);

	void SetFilled(bool status);	//changes the figure's fill status
	void ChngDrawClr(color Dclr);	//changes the figure's drawing color
	void ChngFillClr(color Fclr);	//changes the figure's filling color
	void ChngBrdWdth(int width); 
	color getFillClr() const;
	color getDrawClr() const;
	int getBrdWdth() const;

	virtual Point center() const = 0; 
	virtual bool checkLimits() const = 0; 
	virtual float area() const = 0; 
	virtual bool isInside(Point) const = 0; 

	virtual CFigure* copy()=0;
	virtual void Draw(Output* pOut) const = 0 ;		//Draw the figure
	
	///The following functions should be supported by the figure class
	///It should be overridden by each inherited figure

	///Decide the parameters that you should pass to each function	

	virtual bool Resize(float) = 0;	//Resize the figure
	virtual void PrintInfo(Output* pOut) const = 0;	//print all figure info on the status bar
	virtual bool Move(Point) = 0;		//Move the figure
	virtual bool Rotate(int) = 0;	//Rotate the figure
	virtual bool IsSame(CFigure * target) = 0;
	virtual void Save(ofstream &OutFile) = 0;	//Save the figure parameters to the file
	virtual void Load(ifstream &Infile) = 0;	//Load the figure parameters from the file
	
	virtual bool ScrambleMove(Point) = 0;
	virtual void ScrambleHalf() = 0;
	virtual bool ScrambleCheckLimits() const=0;

};

#endif