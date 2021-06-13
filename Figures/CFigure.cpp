#include "CFigure.h"

CFigure::CFigure()
{
	Selected = false;
}

CFigure::CFigure(GfxInfo FigureGfxInfo)
{ 
	FigGfxInfo = FigureGfxInfo;	//Default status is non-filled.
	Selected = false;
}

void CFigure::SetSelected(bool s)
{	Selected = s; }

bool CFigure::IsSelected() const
{	return Selected; }

void CFigure::ChngDrawClr(color Dclr)
{	FigGfxInfo.DrawClr = Dclr; }

void CFigure::ChngFillClr(color Fclr)
{	
	FigGfxInfo.isFilled = true;
	FigGfxInfo.FillClr = Fclr; 
}

void CFigure::ChngBrdWdth(int width)
{
	FigGfxInfo.BorderWdth = width;
}

void CFigure::SetFilled(bool status)
{
	FigGfxInfo.isFilled = status;
}

CFigure* CFigure::copy()
{
	return this;
}

void CFigure::setID(int id)
{
	ID = id;
}

int CFigure::getID() const
{
	return ID;
}

MyType CFigure::getType() const
{
	return this->Type;
}

void CFigure::setType(MyType T)
{
	this->Type = T;
}

color CFigure::getFillClr() const
{
	return FigGfxInfo.FillClr;
}

color CFigure::getDrawClr() const
{
	return FigGfxInfo.DrawClr;
}

int CFigure::getBrdWdth() const
{
	return FigGfxInfo.BorderWdth;
}