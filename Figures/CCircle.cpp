#include "CCircle.h"

CCircle::CCircle()
{}

CCircle::CCircle(Point P1, const int rad, GfxInfo CircGfxInfo):CFigure(CircGfxInfo)
{
	Center = P1;
	Radius = rad;
	P2 = getAnotherPoint();
	this->setType(CIRCLE);
}

void CCircle::Draw(Output* pOut) const
{
	//Call Output::DrawCirc to draw a Circle on the screen	
	pOut->DrawCirc(Center, Radius, FigGfxInfo, Selected);
}

bool CCircle::isInside(Point P) const
{
	P.x = Center.x - P.x;
	P.y = Center.y - P.y;
	P.x *= P.x;
	P.y *= P.y;
	if(sqrt(P.x + P.y) <= (Radius+FigGfxInfo.BorderWdth))
		return true;
	return false;
}

Point CCircle::getAnotherPoint()
{
	Point P;
	P.x = Center.x;
	P.y = Center.y + Radius;
	return P;
}

bool CCircle::checkLimits() const
{
	return (Radius > 5 && (Center.x + Radius) < UI.width && (Center.x - Radius) > 0 && (Center.y + Radius) < (UI.height - UI.StatusBarHeight) && (Center.y - Radius) > UI.ToolBarHeight);
}

void CCircle::PrintInfo(Output* pOut) const
{
	string msg = "Circle: ID= ";
	msg += to_string(ID)+"  ";
	msg += "Center= (";
	msg += to_string(Center.x)+"  ";
	msg += ", ";
	msg += to_string(Center.y);
	msg += ")  Radius= ";
	msg += to_string(Radius);
	pOut->PrintMessage(msg);
}

bool CCircle::Resize(float ResizeFactor)
{
	int tempRadius = Radius;
	Radius *= ResizeFactor;

	if(!checkLimits()){
		Radius = tempRadius;
		return false;
	}
	return true;
}

Point CCircle::center() const
{
	return Center;
}

float CCircle::area() const
{
	return (3.14 * Radius * Radius);
}

bool CCircle::Move(Point dist)
{
	Center.x += dist.x;
	Center.y += dist.y;
	if(!checkLimits()){
		Center.x -= dist.x;
		Center.y -= dist.y;
		return false;
	}
	return true;
}

bool CCircle::Rotate(int angle)
{
	return true;
}

bool CCircle::IsSame( CFigure * target)
{
	return true;
}

CFigure* CCircle::copy()
{
	CFigure* mine = new CCircle(*this);
	return mine;
}

void CCircle::Save(ofstream &OutFile)
{
	OutFile << "CIRCLE   " << ID << "   " << Center.x << ' ' << Center.y << "   " << Radius << "   ";
	OutFile << FigGfxInfo.DrawClr.ucRed << ' ' << FigGfxInfo.DrawClr.ucGreen << ' ' << FigGfxInfo.DrawClr.ucBlue << "   ";
	if(FigGfxInfo.isFilled) OutFile << "1  " << FigGfxInfo.FillClr.ucRed << ' ' << FigGfxInfo.FillClr.ucGreen << ' ' << FigGfxInfo.FillClr.ucBlue << "   ";
	else OutFile << "0   ";
	OutFile << FigGfxInfo.BorderWdth << endl;
}

void CCircle::Load(ifstream &Infile)
{
	Infile >> ID >> Center.x >> Center.y >> Radius >> FigGfxInfo.DrawClr.ucRed >> FigGfxInfo.DrawClr.ucGreen >> FigGfxInfo.DrawClr.ucBlue;
	Infile >> FigGfxInfo.isFilled;
	if(FigGfxInfo.isFilled) Infile >> FigGfxInfo.FillClr.ucRed >> FigGfxInfo.FillClr.ucGreen >> FigGfxInfo.FillClr.ucBlue;
	Infile >> FigGfxInfo.BorderWdth;
	P2 = getAnotherPoint();
	Type = CIRCLE;
}

bool CCircle::ScrambleMove(Point dist)
{
	Center.x += dist.x;
	Center.y += dist.y;
	if (!ScrambleCheckLimits()) {
		Center.x -= dist.x;
		Center.y -= dist.y;
		return false;
	}
	return true;
}

void CCircle::ScrambleHalf()
{
	Center.x /= 2; 	Radius /= 2;
}

bool CCircle::ScrambleCheckLimits() const
{
	return (Radius > 5 && (Center.x + Radius) < UI.width && (Center.x - Radius) > 0 && (Center.y + Radius) < (UI.height - UI.StatusBarHeight) && (Center.y - Radius) > UI.ToolBarHeight && (Center.x + Radius) > UI.width/2);
}