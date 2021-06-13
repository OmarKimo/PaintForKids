#include "CTriangle.h"

CTriangle::CTriangle()
{}

CTriangle::CTriangle(Point P1, Point P2, Point P3, GfxInfo TriGfxInfo):CFigure(TriGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2;
	Corner3 = P3;
	this->setType(TRIANGLE);
}
	
void CTriangle::Draw(Output* pOut) const
{
	//Call Output::DrawTri to draw a triangle on the screen	
	pOut->DrawTri(Corner1, Corner2, Corner3, FigGfxInfo, Selected);
}

bool CTriangle::isInside(Point P) const
{
	float A1 = abs((P.x*(Corner2.y - Corner3.y) + Corner2.x*(Corner3.y - P.y) + Corner3.x*(P.y - Corner2.y))/2.0);
	float A2 = abs((Corner1.x*(P.y - Corner3.y) + P.x*(Corner3.y - Corner1.y) + Corner3.x*(Corner1.y - P.y))/2.0);
	float A3 = abs((Corner1.x*(Corner2.y - P.y) + Corner2.x*(P.y - Corner1.y) + P.x*(Corner1.y - Corner2.y))/2.0);
	float A = area();

	int BW = FigGfxInfo.BorderWdth;
	int dx = Corner1.x - Corner2.x;
	int dy = Corner1.y - Corner2.y;
	float l1 = sqrt(dy*dy + dx*dx)/2.0;
	l1 = 2*sqrt(l1*l1 + (BW*BW)/4);
	dx = Corner1.x - P.x;
	dy = Corner1.y - P.y;
	float l2 = sqrt(dy*dy + dx*dx);
	dx = Corner2.x - P.x;
	dy = Corner2.y - P.y;
	float l3 = sqrt(dy*dy + dx*dx);
	if(l1 >= l2+l3 || l2 <= BW/2 || l3 <= BW/2) return true;

	dx = Corner1.x - Corner3.x;
	dy = Corner1.y - Corner3.y;
	l1 = sqrt(dy*dy + dx*dx)/2.0;
	l1 = 2*sqrt(l1*l1 + (BW*BW)/4);
	dx = Corner1.x - P.x;
	dy = Corner1.y - P.y;
	l2 = sqrt(dy*dy + dx*dx);
	dx = Corner3.x - P.x;
	dy = Corner3.y - P.y;
	l3 = sqrt(dy*dy + dx*dx);
	if(l1 >= l2+l3 || l2 <= BW/2 || l3 <= BW/2) return true;

	dx = Corner3.x - Corner2.x;
	dy = Corner3.y - Corner2.y;
	l1 = sqrt(dy*dy + dx*dx)/2.0;
	l1 = 2*sqrt(l1*l1 + (BW*BW)/4);
	dx = Corner3.x - P.x;
	dy = Corner3.y - P.y;
	l2 = sqrt(dy*dy + dx*dx);
	dx = Corner2.x - P.x;
	dy = Corner2.y - P.y;
	l3 = sqrt(dy*dy + dx*dx);
	if(l1 >= l2+l3 || l2 <= BW/2 || l3 <= BW/2) return true;

	return ((A == (A1 + A2 + A3)) && P.y > UI.ToolBarHeight && P.y < (UI.height - UI.StatusBarHeight));
}

bool CTriangle::checkLimits() const
{
	return ((abs(Corner1.x - center().x) > 10 || abs(Corner2.x - center().x) > 10 || abs(Corner3.x - center().x) > 10) && Corner1.y > UI.ToolBarHeight && Corner2.y > UI.ToolBarHeight && Corner3.y > UI.ToolBarHeight && Corner1.y < (UI.height - UI.StatusBarHeight) && Corner2.y < (UI.height - UI.StatusBarHeight) && Corner3.y < (UI.height - UI.StatusBarHeight) && Corner1.x > 0 && Corner2.x > 0 && Corner3.x > 0 && Corner1.x < UI.width && Corner2.x < UI.width && Corner3.x < UI.width);
}

bool CTriangle::IsSame(CFigure* target)
{
	return true;
}

void CTriangle::PrintInfo(Output* pOut) const
{
	string msg;
	msg += "Triangle: ID= ";
	msg += to_string(ID) + "  ";
	msg += "Corner1= (";
	msg += to_string(Corner1.x);
	msg += ", ";
	msg += to_string(Corner1.y);
	msg += ")   Corner2= (";
	msg += to_string(Corner2.x);
	msg += ", ";
	msg += to_string(Corner2.y);
	msg += ")   Corner3= (";
	msg += to_string(Corner3.x);
	msg += ", ";
	msg += to_string(Corner3.y);
	msg += ")";
	pOut->PrintMessage(msg);
}

bool CTriangle::Resize(float ResizeFactor)
{
	int tempCorner1x = Corner1.x, tempCorner2x = Corner2.x, tempCorner1y = Corner1.y, tempCorner2y = Corner2.y, tempCorner3x = Corner3.x, tempCorner3y = Corner3.y;
	int dist1x = Corner1.x - center().x, dist2x = center().x - Corner2.x, dist3x = center().x - Corner3.x;
	int dist1y = center().y - Corner1.y, dist2y = Corner2.y - center().y, dist3y = center().y - Corner3.y;

	Corner1.x += (ResizeFactor-1)*dist1x;
	Corner1.y -= (ResizeFactor-1)*dist1y;
	Corner2.x -= (ResizeFactor-1)*dist2x;
	Corner2.y += (ResizeFactor-1)*dist2y;
	Corner3.x -= (ResizeFactor-1)*dist3x;
	Corner3.y -= (ResizeFactor-1)*dist3y;

	if(!checkLimits()){
		Corner1.x = tempCorner1x;
		Corner1.y = tempCorner1y;
		Corner2.x = tempCorner2x;
		Corner2.y = tempCorner2y;
		Corner3.x = tempCorner3x;
		Corner3.y = tempCorner3y;
		return false;
	}
	return true;
}

Point CTriangle::center() const
{
	Point C;
	C.x = (Corner1.x + Corner2.x + Corner3.x)/3;
	C.y = (Corner1.y + Corner2.y + Corner3.y)/3;

	return C;
}

float CTriangle::area() const
{
	return abs((Corner1.x*(Corner2.y - Corner3.y) + Corner2.x*(Corner3.y - Corner1.y) + Corner3.x*(Corner1.y - Corner2.y))/2.0);
}

bool CTriangle::Move(Point dist)
{
	Corner1.x += dist.x;
	Corner1.y += dist.y;
	Corner2.x += dist.x;
	Corner2.y += dist.y;
	Corner3.x += dist.x;
	Corner3.y += dist.y;

	if(!checkLimits()){
		Corner1.x -= dist.x;
		Corner1.y -= dist.y;
		Corner2.x -= dist.x;
		Corner2.y -= dist.y;
		Corner3.x -= dist.x;
		Corner3.y -= dist.y;
		return false;
	}
	return true;
}

bool CTriangle::Rotate(int angle)
{
	int tempCorner1x = Corner1.x, tempCorner2x = Corner2.x, tempCorner1y = Corner1.y, tempCorner2y = Corner2.y, tempCorner3x = Corner3.x, tempCorner3y = Corner3.y;
	int Corner1x = Corner1.x, Corner2x = Corner2.x, Corner1y = Corner1.y, Corner2y = Corner2.y, Corner3x = Corner3.x, Corner3y = Corner3.y;
	Point c = center();
	
	while(angle){
		Corner1.x = c.y - tempCorner1y + c.x;
		Corner1.y = tempCorner1x - c.x + c.y;
		Corner2.x = c.y - tempCorner2y + c.x;
		Corner2.y = tempCorner2x - c.x + c.y;
		Corner3.x = c.y - tempCorner3y + c.x;
		Corner3.y = tempCorner3x - c.x + c.y;

		tempCorner1x = Corner1.x, tempCorner2x = Corner2.x, tempCorner1y = Corner1.y, tempCorner2y = Corner2.y, tempCorner3x = Corner3.x, tempCorner3y = Corner3.y;
		angle -= 90;
	}

	if(!checkLimits()){
		Corner1.x = Corner1x;
		Corner2.x = Corner2x;
		Corner1.y = Corner1y;
		Corner2.y = Corner2y;
		Corner3.x = Corner1x;
		Corner3.y = Corner2y;
		return false;
	}
	return true;
}

CFigure* CTriangle::copy()
{
	CFigure* mine = new CTriangle(*this);
	return mine;
}

void CTriangle::Save(ofstream &OutFile)
{
	/*const char* s = 0;
#define PROCESS_VAL(p) case(p): s = #p; break;
	switch (Type) {
		PROCESS_VAL(LINE);
		PROCESS_VAL(RECTANGLE);
		PROCESS_VAL(TRIANGLE);
	}
#undef PROCESS_VAL*/
	OutFile << "TRIANGLE   " << ID << "   " << Corner1.x << ' ' << Corner1.y << "  " << Corner2.x << ' ' << Corner2.y << "  " << Corner3.x << ' ' << Corner3.y << "   ";
	OutFile << FigGfxInfo.DrawClr.ucRed << ' ' << FigGfxInfo.DrawClr.ucGreen << ' ' << FigGfxInfo.DrawClr.ucBlue << "   ";
	if(FigGfxInfo.isFilled) OutFile << "1  " << FigGfxInfo.FillClr.ucRed << ' ' << FigGfxInfo.FillClr.ucGreen << ' ' << FigGfxInfo.FillClr.ucBlue << "   ";
	else OutFile << "0   ";
	OutFile << FigGfxInfo.BorderWdth << endl;
}

void CTriangle::Load(ifstream &Infile)
{
	Infile >> ID >> Corner1.x >> Corner1.y >> Corner2.x >> Corner2.y >> Corner3.x >> Corner3.y;
	Infile >> FigGfxInfo.DrawClr.ucRed >> FigGfxInfo.DrawClr.ucGreen >> FigGfxInfo.DrawClr.ucBlue;
	Infile >> FigGfxInfo.isFilled;
	if(FigGfxInfo.isFilled) Infile >> FigGfxInfo.FillClr.ucRed >> FigGfxInfo.FillClr.ucGreen >> FigGfxInfo.FillClr.ucBlue;
	Infile >> FigGfxInfo.BorderWdth;
	Type = TRIANGLE;
}

void CTriangle::ScrambleHalf()
{
	Corner1.x /= 2; 
	Corner2.x /= 2; 
	Corner3.x /= 2;
}

bool CTriangle::ScrambleCheckLimits() const
{
	return ((abs(Corner1.x - center().x) > 10 || abs(Corner2.x - center().x) > 10 || abs(Corner3.x - center().x) > 10) && Corner1.y > UI.ToolBarHeight && Corner2.y > UI.ToolBarHeight && Corner3.y > UI.ToolBarHeight && Corner1.y < (UI.height - UI.StatusBarHeight) && Corner2.y < (UI.height - UI.StatusBarHeight) && Corner3.y < (UI.height - UI.StatusBarHeight) && Corner1.x > 0 && Corner2.x > 0 && Corner3.x > 0 &&
	Corner1.x < UI.width && Corner2.x < UI.width && Corner3.x < UI.width && Corner1.x > UI.width/2 && Corner2.x  > UI.width / 2 && Corner3.x  > UI.width / 2);
}

bool CTriangle::ScrambleMove(Point dist)
{
	Corner1.x += dist.x;
	Corner1.y += dist.y;
	Corner2.x += dist.x;
	Corner2.y += dist.y;
	Corner3.x += dist.x;
	Corner3.y += dist.y;

	if (!ScrambleCheckLimits()) {
		Corner1.x -= dist.x;
		Corner1.y -= dist.y;
		Corner2.x -= dist.x;
		Corner2.y -= dist.y;
		Corner3.x -= dist.x;
		Corner3.y -= dist.y;
		return false;
	}
	return true;
}