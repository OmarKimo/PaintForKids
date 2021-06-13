#ifndef CRECT_H
#define CRECT_H

#include "CFigure.h"

class CRectangle : public CFigure
{
private:
	Point Corner1;	
	Point Corner2;
public:

	CRectangle(); //Default Constructor
	CRectangle(Point , Point, GfxInfo RectGfxInfo );

	virtual void Draw(Output* pOut) const;
	virtual bool isInside(Point) const;
	virtual bool checkLimits() const;
	virtual float area() const;
	virtual bool Resize(float);	//Resize the figure
	virtual void PrintInfo(Output* pOut) const;	//print all figure info on the status bar
	virtual Point center() const;
	virtual bool Move(Point);		//Move the figure
	virtual bool Rotate(int);	//Rotate the figure
	virtual CFigure* copy();
	virtual bool IsSame( CFigure * target);
	virtual void Save(ofstream &OutFile);	//Save the figure parameters to the file
	virtual void Load(ifstream &Infile);	//Load the figure parameters to the file
	
	virtual bool ScrambleMove(Point);
	virtual void ScrambleHalf();
	virtual bool ScrambleCheckLimits() const;

};

#endif