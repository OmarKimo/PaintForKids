#ifndef CCIRC_H
#define CCIRC_H

#include "CFigure.h"

class CCircle : public CFigure
{
private:
	Point Center;
	int Radius;
	Point P2;

public:
	CCircle(Point, const int, GfxInfo);
	CCircle(); //Default Constructor

	virtual void Draw(Output*) const;
	virtual bool isInside(Point) const;
	virtual bool checkLimits() const;
	virtual Point center() const;
	virtual float area() const;
	virtual bool Resize(float);	//Resize the figure

	virtual void PrintInfo(Output* pOut) const;	//print all figure info on the status bar

	virtual bool Move(Point);		//Move the figure
	virtual bool Rotate(int);	//Rotate the figure
	virtual CFigure* copy();
	virtual bool IsSame(CFigure* target);

	virtual void Save(ofstream &OutFile);	//Save the figure parameters to the file
	virtual void Load(ifstream &Infile);	//Load the figure parameters to the file
	
	virtual bool ScrambleMove(Point);
	virtual void ScrambleHalf();
	virtual bool ScrambleCheckLimits() const;

	Point getAnotherPoint(); //to get another point on the circle from radius

};

#endif