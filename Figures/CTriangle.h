#ifndef CTRIANGLE_H
#define CTRIANGLE_H

#include "CFigure.h"

class CTriangle : public CFigure
{
private:
	Point Corner1;	
	Point Corner2;
	Point Corner3;
public:

	CTriangle(); //Default Constructor
	CTriangle(Point, Point, Point, GfxInfo);

	virtual void Draw(Output*) const;
	virtual bool isInside(Point) const;
	virtual bool checkLimits() const;
	virtual bool Resize(float);	//Resize the figure
	virtual void PrintInfo(Output* pOut) const;	//print all figure info on the status bar
	virtual Point center() const;
	virtual float area() const;
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