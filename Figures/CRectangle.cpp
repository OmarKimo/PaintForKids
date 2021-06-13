#include "CRectangle.h"

CRectangle::CRectangle()
{}

CRectangle::CRectangle(Point P1, Point P2, GfxInfo RectGfxInfo):CFigure(RectGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2;
	this->setType(RECTANGLE);
}
	
void CRectangle::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pOut->DrawRect(Corner1, Corner2, FigGfxInfo, Selected);
}

bool CRectangle::IsSame( CFigure * target)
{
	return true;
}

bool CRectangle::isInside(Point P) const
{
	int curx1 = Corner1.x + FigGfxInfo.BorderWdth;
	int curx2 = Corner2.x - FigGfxInfo.BorderWdth;
	if (curx1 > curx2){
		curx1 = Corner2.x + FigGfxInfo.BorderWdth;
		curx2 = Corner1.x - FigGfxInfo.BorderWdth;
	}
	int cury1 = Corner1.y + FigGfxInfo.BorderWdth;
	int cury2 = Corner2.y - FigGfxInfo.BorderWdth;
	if (cury1 > cury2){
		cury1 = Corner2.y + FigGfxInfo.BorderWdth;
		cury2 = Corner1.y - FigGfxInfo.BorderWdth;
	}
	if (P.x >= curx1 && P.x <= curx2 && P.y >= cury1 && P.y <= cury2)
		return true;
	return false;
}

bool CRectangle::checkLimits() const
{
	return (abs(Corner2.x-Corner1.x) > 10 && abs(Corner2.y-Corner1.y) > 10 && Corner1.y > UI.ToolBarHeight && Corner2.y > UI.ToolBarHeight && Corner1.y < (UI.height - UI.StatusBarHeight) && Corner2.y < (UI.height - UI.StatusBarHeight) && Corner1.x > 0 && Corner2.x > 0 && Corner1.x < UI.width && Corner2.x < UI.width);
}

void CRectangle::PrintInfo(Output* pOut) const
{
	int w = abs(Corner1.x - Corner2.x);
	int h = abs(Corner1.y - Corner2.y);

	string msg = "Rectangle: ID= ";
	msg += to_string(this->ID) + "   ";
	msg += "Top Left Corner= (";
	msg += to_string(Corner1.x);
	msg += ", ";
	msg += to_string(Corner1.y);
	msg += ")   Bottom Right Corner= (";
	msg += to_string(Corner2.x);
	msg += ", ";
	msg += to_string(Corner2.y);
	msg += ")   Width= ";
	msg += to_string(w);
	msg += "   Height= ";
	msg += to_string(h);
	pOut->PrintMessage(msg);
}

bool CRectangle::Resize(float ResizeFactor)
{
	int tempCorner1x = Corner1.x, tempCorner2x = Corner2.x, tempCorner1y = Corner1.y, tempCorner2y = Corner2.y;
	int dist1x = Corner1.x - center().x, dist2x = center().x - Corner2.x;
	int dist1y = center().y - Corner1.y, dist2y = Corner2.y - center().y;

	Corner1.x += (ResizeFactor-1)*dist1x;
	Corner2.x -= (ResizeFactor-1)*dist2x;
	Corner1.y -= (ResizeFactor-1)*dist1y;
	Corner2.y += (ResizeFactor-1)*dist2y;

	if(!checkLimits()){
		Corner1.x = tempCorner1x;
		Corner2.x = tempCorner2x;
		Corner1.y = tempCorner1y;
		Corner2.y = tempCorner2y;
		return false;
	}
	return true;
}

Point CRectangle::center() const
{
	Point P;
	P.x = (Corner1.x + Corner2.x)/2;
	P.y = (Corner1.y + Corner2.y)/2;

	return P;
}

float CRectangle::area() const
{
	return (abs(Corner1.x - Corner2.x) * abs(Corner1.y - Corner2.y));
}

bool CRectangle::Move(Point dist)
{
	Corner1.x += dist.x;
	Corner1.y += dist.y;
	Corner2.x += dist.x;
	Corner2.y += dist.y;

	if(!checkLimits()){
		Corner1.x -= dist.x;
		Corner1.y -= dist.y;
		Corner2.x -= dist.x;
		Corner2.y -= dist.y;
		return false;
	}
	return true;
}

bool CRectangle::Rotate(int angle)
{
	int tempCorner1x = Corner1.x, tempCorner2x = Corner2.x, tempCorner1y = Corner1.y, tempCorner2y = Corner2.y;
	int Corner1x = Corner1.x, Corner2x = Corner2.x, Corner1y = Corner1.y, Corner2y = Corner2.y;
	Point c = center();

	while(angle){
		if(angle == 180) return true;
		Corner1.x = c.y - tempCorner1y + c.x;
		Corner1.y = tempCorner1x - c.x + c.y;
		Corner2.x = c.y - tempCorner2y + c.x;
		Corner2.y = tempCorner2x - c.x + c.y;

		angle -= 90;
		tempCorner1x = Corner1.x, tempCorner2x = Corner2.x, tempCorner1y = Corner1.y, tempCorner2y = Corner2.y;
	}
	if(!checkLimits()){
		Corner1.x = Corner1x;
		Corner2.x = Corner2x;
		Corner1.y = Corner1y;
		Corner2.y = Corner2y;
		return false;
	}
	return true;
}

CFigure* CRectangle::copy()
{
	CFigure* mine = new CRectangle(*this);
	return mine;
}

void CRectangle::Save(ofstream &OutFile)
{
	OutFile << "RECTANGLE   " << ID << "   " << Corner1.x << ' ' << Corner1.y << "   " << Corner2.x << ' ' << Corner2.y << "   ";
	OutFile << FigGfxInfo.DrawClr.ucRed << ' ' << FigGfxInfo.DrawClr.ucGreen << ' ' << FigGfxInfo.DrawClr.ucBlue << "   ";
	if(FigGfxInfo.isFilled) OutFile << "1  " << FigGfxInfo.FillClr.ucRed << ' ' << FigGfxInfo.FillClr.ucGreen << ' ' << FigGfxInfo.FillClr.ucBlue << "   ";
	else OutFile << "0   ";
	OutFile << FigGfxInfo.BorderWdth << endl;
}

void CRectangle::Load(ifstream &Infile)
{
	Infile >> ID >> Corner1.x >> Corner1.y >> Corner2.x >> Corner2.y;
	Infile >> FigGfxInfo.DrawClr.ucRed >> FigGfxInfo.DrawClr.ucGreen >> FigGfxInfo.DrawClr.ucBlue;
	Infile >> FigGfxInfo.isFilled;
	if(FigGfxInfo.isFilled) Infile >> FigGfxInfo.FillClr.ucRed >> FigGfxInfo.FillClr.ucGreen >> FigGfxInfo.FillClr.ucBlue;
	Infile >> FigGfxInfo.BorderWdth;
	Type = RECTANGLE;
}

void CRectangle::ScrambleHalf()
{
	Corner1.x /= 2; 
	Corner2.x /= 2; 
};

bool CRectangle::ScrambleCheckLimits() const
{
	return (abs(Corner2.x - Corner1.x) > 10 && abs(Corner2.y - Corner1.y) > 10 && Corner1.y > UI.ToolBarHeight && Corner2.y > UI.ToolBarHeight && Corner1.y < (UI.height - UI.StatusBarHeight) && Corner2.y < (UI.height - UI.StatusBarHeight) && Corner1.x > 0 && Corner2.x > 0
		&& Corner1.x < UI.width && Corner2.x < UI.width && Corner1.x > UI.width/2 && Corner2.x > UI.width / 2);
}

bool CRectangle::ScrambleMove(Point dist)
{
	Corner1.x += dist.x;
	Corner1.y += dist.y;
	Corner2.x += dist.x;
	Corner2.y += dist.y;

	if (!ScrambleCheckLimits()) {
		Corner1.x -= dist.x;
		Corner1.y -= dist.y;
		Corner2.x -= dist.x;
		Corner2.y -= dist.y;
		return false;
	}
	return true;
}