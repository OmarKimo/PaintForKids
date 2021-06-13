#include "CLine.h"
#include <cmath>

CLine::CLine()
{}

CLine::CLine(Point P1, Point P2, GfxInfo LineGfxInfo):CFigure(LineGfxInfo)
{
	End1 = P1;
	End2 = P2;
	this->setType(LINE);
}
	
void CLine::Draw(Output* pOut) const
{
	//Call Output::DrawLine to draw a line on the screen	
	pOut->DrawLine(End1, End2, FigGfxInfo, Selected);
}

bool CLine::IsSame(CFigure * target)
{
	return true;
}

bool CLine::isInside(Point P) const
{
	int dx = End2.x - End1.x;
	int dy = End2.y - End1.y;
	int currx1 = (End1.x > End2.x)?End2.x:End1.x;
	int currx2 = (End1.x > End2.x)?End1.x:End2.x;
	int curry1 = (End1.y > End2.y)?End2.y:End1.y;
	int curry2 = (End1.y > End2.y)?End1.y:End2.y;
	int BW = FigGfxInfo.BorderWdth;
	
	if (dy == 0){
		if ((End1.y - BW) > P.y || (End1.y + BW) < P.y || P.x < currx1 || P.x > currx2) return false;
		return true;
	}
	if(dx == 0){
		if ((End1.x + BW) < P.x && (End1.x - BW) > P.x || P.y < curry1 || P.y > curry2) return false;
		return true;
	}

	if (P.x >= currx1 - BW && P.x <= currx2 + BW && P.y >= curry1 - BW && P.y <= curry2 + BW){
		float l1 = sqrt(dy*dy + dx*dx)/2.0;
		l1 = 2*sqrt(l1*l1 + (BW*BW/4));
		dx = End1.x - P.x;
		dy = End1.y - P.y;

		float l2 = sqrt(dy*dy + dx*dx);
		dx = End2.x - P.x;
		dy = End2.y - P.y;

		float l3 = sqrt(dy*dy + dx*dx);
		
		if(l1 >= l2+l3 || l2 <= BW/2 || l3 <= BW/2) return true;
	}
	return false;
}

bool CLine::checkLimits() const
{
	return ((abs(End2.x-End1.x) > 10 || abs(End2.y-End1.y) > 10) && End1.y > UI.ToolBarHeight && End2.y > UI.ToolBarHeight && End1.y < (UI.height - UI.StatusBarHeight) && End2.y < (UI.height - UI.StatusBarHeight) && End1.x > 0 && End1.x < UI.width && End2.x > 0 && End2.x < UI.width);
}

void CLine::PrintInfo(Output* pOut) const
{
	string msg = "Line: ID= ";
	msg += to_string(this->ID) + "   ";
	msg += "End1= (";
	msg += to_string(End1.x);
	msg += ", ";
	msg += to_string(End1.y);
	msg += ")  End2= (";
	msg += to_string(End2.x);
	msg += ", ";
	msg += to_string(End2.y);
	msg += ")";
	pOut->PrintMessage(msg);
}

bool CLine::Resize(float ResizeFactor)
{
	int tempEnd1x = End1.x, tempEnd2x = End2.x, tempEnd1y = End1.y, tempEnd2y = End2.y;
	int dist1x = End1.x - center().x, dist2x = center().x - End2.x;
	int dist1y = center().y - End1.y, dist2y = End2.y - center().y;

	End1.x += (ResizeFactor-1)*dist1x;
	End2.x -= (ResizeFactor-1)*dist2x;
	End1.y -= (ResizeFactor-1)*dist1y;
	End2.y += (ResizeFactor-1)*dist2y;

	if(!checkLimits()){
		End1.x = tempEnd1x;
		End2.x = tempEnd2x;
		End1.y = tempEnd1y;
		End2.y = tempEnd2y;
		return false;
	}
	return true;
}

Point CLine::center() const
{
	Point C;
	C.x = (End1.x + End2.x)/2;
	C.y = (End1.y + End2.y)/2;

	return C;
}

float CLine::area() const
{
	return sqrt(abs(End1.y - End2.y)*abs(End1.y - End2.y)+abs(End1.x - End2.x)*abs(End1.x - End2.x));
}

bool CLine::Move(Point dist)
{
	End1.x += dist.x;
	End1.y += dist.y;
	End2.x += dist.x;
	End2.y += dist.y;

	if(!checkLimits()){
		End1.x -= dist.x;
		End1.y -= dist.y;
		End2.x -= dist.x;
		End2.y -= dist.y;
		return false;
	}
	return true;
}

bool CLine::Rotate(int angle)
{
	int tempEnd1x = End1.x, tempEnd2x = End2.x, tempEnd1y = End1.y, tempEnd2y = End2.y;
	int End1x = End1.x, End2x = End2.x, End1y = End1.y, End2y = End2.y;
	Point c = center();

	while(angle){

		End1.x = c.y - tempEnd1y + c.x;
		End1.y = tempEnd1x - c.x + c.y;
		End2.x = c.y - tempEnd2y + c.x;
		End2.y = tempEnd2x - c.x + c.y;

		angle-=90;
		tempEnd1x = End1.x, tempEnd2x = End2.x, tempEnd1y = End1.y, tempEnd2y = End2.y;
	}

	if(!checkLimits()){
		End1.x = End1x;
		End2.x = End2x;
		End1.y = End1y;
		End2.y = End2y;
		return false;
	}
	return true;
}

CFigure* CLine::copy()
{
	CFigure* mine = new CLine(*this);
	return mine;
}

void CLine::Save(ofstream &OutFile)
{
	OutFile << "LINE   " << ID << "   " << End1.x << ' ' << End1.y << "  " << End2.x << ' ' << End2.y << "   ";
	OutFile << FigGfxInfo.DrawClr.ucRed << ' ' << FigGfxInfo.DrawClr.ucGreen << ' ' << FigGfxInfo.DrawClr.ucBlue << "   " << FigGfxInfo.BorderWdth << endl;
}

void CLine::Load(ifstream &Infile)
{
	Infile >> ID >> End1.x >> End1.y >> End2.x >> End2.y >> FigGfxInfo.DrawClr.ucRed >> FigGfxInfo.DrawClr.ucGreen >> FigGfxInfo.DrawClr.ucBlue >> FigGfxInfo.BorderWdth;
	Type = LINE;
}

void CLine::ScrambleHalf()
{
	End1.x /= 2; 
	End2.x /= 2;
};

bool CLine::ScrambleCheckLimits() const
{
	return ((abs(End2.x - End1.x) > 10 || abs(End2.y - End1.y) > 10) && End1.y > UI.ToolBarHeight && End2.y > UI.ToolBarHeight && End1.y < (UI.height - UI.StatusBarHeight) && End2.y < (UI.height - UI.StatusBarHeight) && End1.x > 0 && End2.x > 0
		&& End1.x < UI.width  && End2.x < UI.width && End1.x > UI.width/2  && End2.x > UI.width/2);
}

bool CLine::ScrambleMove(Point dist)
{
	End1.x += dist.x;
	End1.y += dist.y;
	End2.x += dist.x;
	End2.y += dist.y;

	if (!ScrambleCheckLimits()) {
		End1.x -= dist.x;
		End1.y -= dist.y;
		End2.x -= dist.x;
		End2.y -= dist.y;
		return false;
	}
	return true;
}