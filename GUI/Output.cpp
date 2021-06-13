#include "Output.h"


Output::Output()
{
	//Initialize user interface parameters
	UI.InterfaceMode = MODE_DRAW;
	
	UI.width = 1400;
	UI.height = 600;
	UI.wx = 5;
	UI.wy =5;

	ZoomScale = 0;
	
	UI.StatusBarHeight = 50;
	UI.ToolBarHeight = 50;
	UI.MenuItemWidth = 50;
	
	UI.DrawColor = BLUE;	//Drawing color
	UI.FillColor = GREEN;	//Filling color
	UI.MsgColor = RED;		//Messages color
	UI.BkGrndColor = LIGHTGOLDENRODYELLOW;	//Background color
	UI.HighlightColor = MAGENTA;	//This color should NOT be used to draw figures. use if for highlight only
	UI.StatusBarColor = TURQUOISE;
	UI.PenWidth = 3;	//width of the figures frames
	this->count=0;
	
	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	//Change the title
	pWind->ChangeTitle("Paint for Kids - Programming Techniques Project");
	
	CreateDrawToolBar();
	CreateStatusBar();
}


Input* Output::CreateInput() const
{
	Input* pIn = new Input(pWind);
	return pIn;
}

//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int w, int h, int x, int y) const
{ 
	window* pW = new window(w, h, x, y);
	pW->SetBrush(UI.BkGrndColor);
	pW->SetPen(UI.BkGrndColor, 1);
	pW->DrawRectangle(0, UI.ToolBarHeight, w, h);	
	return pW;
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar() const
{
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar() const
{
	//Clear Status bar by drawing a filled white rectangle
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::CreatePaletteBar() const
{
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(WHITE);

	string MenuItemImages[PALETTE_COUNT];
	
	MenuItemImages[PALETTE_WHITE] = "images\\MenuItems\\40 White.jpg";
	MenuItemImages[PALETTE_DEFAULT] = "images\\MenuItems\\40 Default.jpg";
	MenuItemImages[PALETTE_YELLOW] = "images\\MenuItems\\40 Yellow.jpg";
	MenuItemImages[PALETTE_YELLOW_DARK] = "images\\MenuItems\\40 YellowDark.jpg";
	MenuItemImages[PALETTE_ORANGE] = "images\\MenuItems\\40 Orange.jpg";
	MenuItemImages[PALETTE_GREEN_BRIGHT] = "images\\MenuItems\\40 GreenBright.jpg";
	MenuItemImages[PALETTE_GREEN_LIGHT] = "images\\MenuItems\\40 GreenLight.jpg";
	MenuItemImages[PALETTE_DEGREE_GREEN] = "images\\MenuItems\\40 DegreeGreen.jpg";
	MenuItemImages[PALETTE_GREEN] = "images\\MenuItems\\40 Green.jpg";
	MenuItemImages[PALETTE_NILE_LIGHT] = "images\\MenuItems\\40 NileLight.jpg";
	MenuItemImages[PALETTE_NILE] = "images\\MenuItems\\40 Nile.jpg";
	MenuItemImages[PALETTE_NILE_DARK] = "images\\MenuItems\\40 NileDark.jpg";
	MenuItemImages[PALETTE_BLUE] = "images\\MenuItems\\40 Blue.jpg";
	MenuItemImages[PALETTE_BLUE_DARK] = "images\\MenuItems\\40 BlueDark.jpg";
	MenuItemImages[PALETTE_PINK] = "images\\MenuItems\\40 Pink.jpg";
	MenuItemImages[PALETTE_VIOLET_LIGHT] = "images\\MenuItems\\40 VioletLight.jpg";
	MenuItemImages[PALETTE_VIOLET] = "images\\MenuItems\\40 Violet.jpg";
	MenuItemImages[PALETTE_RED] = "images\\MenuItems\\40 Red.jpg";
	MenuItemImages[PALETTE_RED_DARK1] = "images\\MenuItems\\40 RedDark1.jpg";
	MenuItemImages[PALETTE_RED_DARK2] = "images\\MenuItems\\40 RedDark2.jpg";
	MenuItemImages[PALETTE_BROWN] = "images\\MenuItems\\40 Brown.jpg";
	MenuItemImages[PALETTE_GRAY] = "images\\MenuItems\\40 Gray.jpg";
	MenuItemImages[PALETTE_BLACK] = "images\\MenuItems\\40 Black.jpg";
	
	for(int i=0; i<PALETTE_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*40,51,40,40);

}

window* Output::getpwind()
{
	return pWind;
}

void Output::CreateBorderMenu() const
{
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(WHITE);

	string MenuItemImages[7];

	MenuItemImages[0] = "images\\MenuItems\\5025wdth01.jpg";
	MenuItemImages[1] = "images\\MenuItems\\5025wdth03.jpg";
	MenuItemImages[2] = "images\\MenuItems\\5025wdth06.jpg";
	MenuItemImages[3] = "images\\MenuItems\\5025wdth09.jpg";
	MenuItemImages[4] = "images\\MenuItems\\5025wdth12.jpg";
	MenuItemImages[5] = "images\\MenuItems\\5025wdth15.jpg";
	MenuItemImages[6] = "images\\MenuItems\\5025wdth20.jpg";

	for(int i = 0; i < 7; i++){
		pWind->DrawImage(MenuItemImages[i], ITM_BORDER_WIDTH_d*50, 51+(i*25), 50, 25);
		pWind->SetPen(RED, 1);
		pWind->DrawLine(ITM_BORDER_WIDTH_d*50, 51+(i*25), ITM_BACKGROUND_CLR*50, 51+(i*25));
	}
}

void Output::CreateRotateMenu() const
{
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(WHITE);

	string MenuItemImages[3];

	MenuItemImages[0] = "images\\MenuItems\\50 Rotate90.jpg";
	MenuItemImages[1] = "images\\MenuItems\\50 Rotate180.jpg";
	MenuItemImages[2] = "images\\MenuItems\\50 Rotate270.jpg";

	for(int i = 0; i < 3; i++)
		pWind->DrawImage(MenuItemImages[i], ITM_ROTATE*50, 51+(i*50), 50, 50);
}

void Output::CreateResizeMenu() const
{
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(WHITE);

	string MenuItemImages[4];

	MenuItemImages[0] = "images\\MenuItems\\50 Resize2.jpg";
	MenuItemImages[1] = "images\\MenuItems\\50 Resize4.jpg";
	MenuItemImages[2] = "images\\MenuItems\\50 Resize 2.jpg";
	MenuItemImages[3] = "images\\MenuItems\\50 Resize 4.jpg";

	for(int i = 0; i < 4; i++)
		pWind->DrawImage(MenuItemImages[i], ITM_RESIZE*50, 51+(i*50), 50, 50);
}

void Output::CreateFillStatusMenu(bool isInZoom) const
{
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(WHITE);

	string MenuItemImages[2];

	MenuItemImages[0] = "images\\MenuItems\\Fill.jpg";
	MenuItemImages[1] = "images\\MenuItems\\NotFill.jpg";

	for(int i = 0; i < 2; i++){
		if(!isInZoom) pWind->DrawImage(MenuItemImages[i], ITM_FILL_CLR_d*50, 51+(i*50), 50, 50);
		else pWind->DrawImage(MenuItemImages[i], 50, 51+(i*50), 50, 50);
	}
}

void Output::CreateDrawToolBar() const
{
	UI.InterfaceMode = MODE_DRAW;
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(WHITE);

	//You can draw the tool bar icons in any way you want.
	//Below is one possible way
	
	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in UI_Info.h ==> enum DrawMenuItem

	string MenuItemImages[DRAW_ITM_COUNT];
	MenuItemImages[ITM_RECT] = "images\\MenuItems\\50 rect.jpg";
	MenuItemImages[ITM_CIRC] = "images\\MenuItems\\50 circ.jpg";
	MenuItemImages[ITM_LINE] = "images\\MenuItems\\50 line.jpg";
	MenuItemImages[ITM_TRI] = "images\\MenuItems\\50 tri.jpg";
	MenuItemImages[ITM_DRAW_CLR_d] = "images\\MenuItems\\50 change drawing color.jpg";
	MenuItemImages[ITM_FILL_CLR_d] = "images\\MenuItems\\50 change filling color.jpg";
	MenuItemImages[ITM_BORDER_WIDTH_d] = "images\\MenuItems\\50 border width.jpg";
	MenuItemImages[ITM_BACKGROUND_CLR] = "images\\MenuItems\\50 change background color.jpg";
	MenuItemImages[ITM_SELECT] = "images\\MenuItems\\50 select.jpg";
	MenuItemImages[ITM_CUT] = "images\\MenuItems\\50 cut.jpg";
	MenuItemImages[ITM_COPY] = "images\\MenuItems\\50 copy.jpg";
	MenuItemImages[ITM_PASTE] = "images\\MenuItems\\50 paste.jpg";
	MenuItemImages[ITM_DEL] = "images\\MenuItems\\50 delete.jpg";
	MenuItemImages[ITM_MOVE] = "images\\MenuItems\\50 move.jpg";
	MenuItemImages[ITM_RESIZE] = "images\\MenuItems\\50 resize.jpg";
	MenuItemImages[ITM_ROTATE] = "images\\MenuItems\\50 rotate.jpg";
	MenuItemImages[ITM_ZOOM_IN] = "images\\MenuItems\\50 IN.jpg";
	MenuItemImages[ITM_ZOOM_OUT] = "images\\MenuItems\\50 Out.jpg";
	MenuItemImages[ITM_FRONT] = "images\\MenuItems\\50 bring to front.jpg";
	MenuItemImages[ITM_BACK] = "images\\MenuItems\\50 send to back.jpg";
	/*MenuItemImages[ITM_UNDO] = "images\\MenuItems\\50 undo.jpg";
	MenuItemImages[ITM_REDO] = "images\\MenuItems\\50 redo.jpg";*/
	MenuItemImages[ITM_SAVE] = "images\\MenuItems\\50 save.jpg";
	MenuItemImages[ITM_LOAD] = "images\\MenuItems\\50 load.jpg";
	MenuItemImages[ITM_TO_PLAY] = "images\\MenuItems\\50 to play.jpg";
	MenuItemImages[ITM_EXIT_DRAW] = "images\\MenuItems\\50 exit.jpg";

	//Draw menu item one image at a time
	for(int i=0; i<DRAW_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth,0,UI.MenuItemWidth, UI.ToolBarHeight);

	//Draw a line under the toolbar
	pWind->SetPen(UI.BkGrndColor, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);	

}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::CreatePlayToolBar() const
{
	UI.InterfaceMode = MODE_PLAY;

	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, 0, UI.width, 50);

	string MenuItemImages[PLAY_ITM_COUNT];

	MenuItemImages[ITM_PICK_HIDE] = "images\\MenuItems\\50 pick hide.jpg";
	MenuItemImages[ITM_SCRAMBLE_FIND] = "images\\MenuItems\\50 scramble find.jpg";
	MenuItemImages[ITM_TO_DRAW] = "images\\MenuItems\\50 to draw.jpg";
	MenuItemImages[ITM_EXIT_PLAY] = "images\\MenuItems\\50 exit.jpg";

	for(int i=0; i<PLAY_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth,0,UI.MenuItemWidth, UI.ToolBarHeight);

	pWind->SetPen(UI.BkGrndColor, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::CreateToolBar_Zoom() const
{
	UI.InterfaceMode = MODE_DRAW;
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, 0, UI.width, 50);

	string MenuItemImages[10];

	MenuItemImages[0] = "images\\MenuItems\\50 change drawing color.jpg";
	MenuItemImages[1] = "images\\MenuItems\\50 change filling color.jpg";
	MenuItemImages[2] = "images\\MenuItems\\50 change background color.jpg";
	MenuItemImages[3] = "images\\MenuItems\\50 select.jpg";
	MenuItemImages[4] = "images\\MenuItems\\50 delete.jpg";
	MenuItemImages[5] = "images\\MenuItems\\50 IN.jpg";
	MenuItemImages[6] = "images\\MenuItems\\50 Out.jpg";
	/*MenuItemImages[7] = "images\\MenuItems\\50 undo.jpg";
	MenuItemImages[8] = "images\\MenuItems\\50 redo.jpg";*/
	MenuItemImages[7] = "images\\MenuItems\\50 save.jpg";
	MenuItemImages[8] = "images\\MenuItems\\50 load.jpg";
	MenuItemImages[9] = "images\\MenuItems\\50 exit.jpg";

	//Draw menu item one image at a time
	for(int i=0; i<10; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth,0,UI.MenuItemWidth, UI.ToolBarHeight);

	//Draw a line under the toolbar
	pWind->SetPen(UI.BkGrndColor, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);	
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::CreatePickHideBar() const
{
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(WHITE);

	string MenuItemImages[4];

	MenuItemImages[PICK_TYPE] = "images\\MenuItems\\75 Figure Type.jpg";
	MenuItemImages[PICK_COLOR] = "images\\MenuItems\\75 Fill Color.jpg";
	MenuItemImages[PICK_TYPE_COLOR] = "images\\MenuItems\\75 Type Color.jpg";
	MenuItemImages[PICK_AREA] = "images\\MenuItems\\75 Figure Area.jpg";

	for (int i = 0; i<4; i++)
		pWind->DrawImage(MenuItemImages[i], i * 75, 51, 75, 75);
}
///////////////////////////////////////////////////////////////////////////////////////////

void Output::ClearDrawArea() const
{
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);

	string BGN;

	switch (count)
	{
	case 0: BGN="0"; break;
	case 1:  BGN="images\\MenuItems\\BGD\\01.jpg";break;
	case 2:  BGN="images\\MenuItems\\BGD\\02.jpg";break;
	case 3:  BGN="images\\MenuItems\\BGD\\03.jpg";break;
	case 4:  BGN="images\\MenuItems\\BGD\\04.jpg";break;
	case 5:  BGN="images\\MenuItems\\BGD\\05.jpg";break;
	case 6:  BGN="images\\MenuItems\\BGD\\06.jpg";break;
	case 7:  BGN="images\\MenuItems\\BGD\\07.jpg";break;
	case 8:  BGN="images\\MenuItems\\BGD\\08.jpg";break;
	case 9:  BGN="images\\MenuItems\\BGD\\09.jpg";break;
	case 10: BGN="images\\MenuItems\\BGD\\10.jpg";break;
	case 11: BGN="images\\MenuItems\\BGD\\11.jpg";break;
	case 12: BGN="images\\MenuItems\\BGD\\12.jpg";break;
	case 13: BGN="images\\MenuItems\\BGD\\13.jpg";break;
	case 14: BGN="images\\MenuItems\\BGD\\14.jpg";break;
	case 15: BGN="images\\MenuItems\\BGD\\15.jpg";break;
	case 16: BGN="images\\MenuItems\\BGD\\16.jpg";break;
	case 17: BGN="images\\MenuItems\\BGD\\17.jpg";break;
	case 18: BGN="images\\MenuItems\\BGD\\18.jpg";break;
	default:if ( count ==0 ) BGN="0"; break;
	}
	if ( BGN != "0")
		pWind->DrawImage(BGN, 0,UI.ToolBarHeight,UI.width,500);
	else
		pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);

	
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar
	
	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(20, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(10, UI.height - (int)(UI.StatusBarHeight/1.5), msg);
}
//////////////////////////////////////////////////////////////////////////////////////////

color Output::getCrntDrawColor() const	//get current drawing color
{	return UI.DrawColor;	}
//////////////////////////////////////////////////////////////////////////////////////////

color Output::getCrntBkGrndColor() const	//get current background color
{	return UI.BkGrndColor;	}
//////////////////////////////////////////////////////////////////////////////////////////

color Output::getCrntFillColor() const	//get current filling color
{	return UI.FillColor;	}
//////////////////////////////////////////////////////////////////////////////////////////
	
int Output::getCrntPenWidth() const		//get current pen width
{	return UI.PenWidth;	}

int Output::getZoomScale() const
{
	return ZoomScale;
}

Point Output::getZoomPoint() const
{
	return ZoomPoint;
}

Point Output::PointAfterZooming(const Point P)
{
	Point temp;
	temp.x = (int)(pow(2, ZoomScale) * (P.x - ZoomPoint.x)) + ZoomPoint.x;
	temp.y = (int)(pow(2, ZoomScale) * (P.y - ZoomPoint.y)) + ZoomPoint.y;
	return temp;
}

int Output::BorderAfterZooming(const int BW)
{
	switch (BW)
	{
	case 1:
		if (ZoomScale <= 8 && ZoomScale >= 2)
			switch (ZoomScale)
		{
			case 2:
				return 3;
			case 3:
				return 6;
			case 4:
				return 6;
			case 5:
				return 9;
			case 6:
				return 9;
			case 7:
				return 12;
			case 8:
				return 15;
		}
		else if (ZoomScale > 8) return 20;
		else if (ZoomScale < 0) return 1;
		else return BW;

	case 3:
		if (ZoomScale <= 8 && ZoomScale >= -2)
			switch (ZoomScale)
		{
			case 0: return BW;
			case 1: return BW;
			case 2: return 6;
			case 3: return 6;
			case 4: return 9;
			case 5: return 12;
			case 6: return 12;
			case 7: return 15;
			case 8: return 15;
			case -1: return 2;
			case -2: return 1;
		}
		else if (ZoomScale > 8) return 20;
		else if (ZoomScale < -2) return 1;
		else return BW;

	case 6:
		if (ZoomScale <= 7 && ZoomScale >= -5)
			switch (ZoomScale)
		{
			case 0: return BW;
			case 1: return BW;
			case 2: return 9;
			case 3: return 9;
			case 4: return 12;
			case 5: return 12;
			case 6: return 15;
			case 7: return 15;
			case -1: return 5;
			case -2: return 4;
			case -3: return 3;
			case -4: return 2;
			case -5: return 1;
		}
		else if (ZoomScale > 7) return 20;
		else if (ZoomScale < -5) return 1;
		else return BW;

	case 9:
		if (ZoomScale <= 5 && ZoomScale >= -6)
			switch (ZoomScale)
		{
			case 0: return BW;
			case 1: return BW;
			case 2: return 12;
			case 3: return 12;
			case 4: return 15;
			case 5: return 20;
			case -1: return 8;
			case -2: return 6;
			case -3: return 4;
			case -4: return 3;
			case -5: return 2;
			case -6: return 1;
		}
		else if (ZoomScale > 5) return 20;
		else if (ZoomScale < -6) return 1;
		else return BW;

	case 12:
		if (ZoomScale <= 3 && ZoomScale >= -6)
			switch (ZoomScale)
		{
			case 0: return BW;
			case 1: return 15;
			case 2: return 15;
			case 3: return 20;
			case -1: return 11;
			case -2: return 9;
			case -3: return 6;
			case -4: return 3;
			case -5: return 2;
			case -6: return 1;
		}
		else if (ZoomScale > 3) return 20;
		else if (ZoomScale < -6) return 1;
		else return BW;

	case 15:
		if (ZoomScale <= 2 && ZoomScale >= -8)
			switch (ZoomScale)
		{
			case 0: return BW;
			case 1: return BW;
			case 2: return 20;
			case -1: return 13;
			case -2: return 12;
			case -3: return 9;
			case -4: return 6;
			case -5: return 4;
			case -6: return 3;
			case -7: return 2;
			case -8: return 1;
		}
		else if (ZoomScale > 2) return 20;
		else if (ZoomScale < -8) return 1;
		else return BW;


	case 20:
		if (ZoomScale < 0)
			switch (ZoomScale)
		{
			case -1: return 18;
			case -2: return 15;
			case -3: return 12;
			case -4: return 10;
			case -5: return 9;
			case -6: return 6;
			case -7: return 4;
			case -8: return 3;
			case -9: return 2;
			case -10: return 1;
		}
		else if (ZoomScale > 0) return 20;
		else return BW;
	}
}

//======================================================================================//
//								Figures Drawing Functions								//
//======================================================================================//

void Output::DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected)
{
	color DrawingClr;
	if(selected)	
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else			
		DrawingClr = RectGfxInfo.DrawClr;
	
	pWind->SetPen(DrawingClr, BorderAfterZooming(RectGfxInfo.BorderWdth));	//Set Drawing color & width

	drawstyle style;
	if (RectGfxInfo.isFilled)	
	{
		style = FILLED;		
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else	
		style = FRAME;

	
	pWind->DrawRectangle(PointAfterZooming(P1).x, PointAfterZooming(P1).y, PointAfterZooming(P2).x, PointAfterZooming(P2).y, style);
	
}

void Output::DrawLine(Point P1, Point P2, GfxInfo LineGfxInfo, bool selected)
{
	color DrawingClr;
	if(selected)	
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else			
		DrawingClr = LineGfxInfo.DrawClr;
	
	pWind->SetPen(DrawingClr, BorderAfterZooming(LineGfxInfo.BorderWdth));	//Set Drawing color & width

	drawstyle style;
	style = FRAME;

	
	pWind->DrawLine(PointAfterZooming(P1).x, PointAfterZooming(P1).y, PointAfterZooming(P2).x, PointAfterZooming(P2).y, style);
	
}

void Output::DrawCirc(Point P1, const int Radius, GfxInfo CircGfxInfo, bool selected)
{
	color DrawingClr;
	if(selected)	
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else			
		DrawingClr = CircGfxInfo.DrawClr;
	
	pWind->SetPen(DrawingClr, BorderAfterZooming(CircGfxInfo.BorderWdth));	//Set Drawing color & width

	drawstyle style;
	if (CircGfxInfo.isFilled)	
	{
		style = FILLED;		
		pWind->SetBrush(CircGfxInfo.FillClr);
	}
	else	
		style = FRAME;

	int tempRadius = Radius*pow(2, ZoomScale);
	int tempX = PointAfterZooming(P1).x, tempY = PointAfterZooming(P1).y;

	pWind->DrawCircle(tempX, tempY, tempRadius, style);
}

void Output::DrawTri(Point P1, Point P2, Point P3, GfxInfo TriaGfxInfo, bool selected)
{
	color DrawingClr;
	if(selected)	
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else			
		DrawingClr = TriaGfxInfo.DrawClr;
	
	pWind->SetPen(DrawingClr, BorderAfterZooming(TriaGfxInfo.BorderWdth));	//Set Drawing color & width

	drawstyle style;
	if (TriaGfxInfo.isFilled)	
	{
		style = FILLED;		
		pWind->SetBrush(TriaGfxInfo.FillClr);
	}
	else	
		style = FRAME;

	
	pWind->DrawTriangle(PointAfterZooming(P1).x, PointAfterZooming(P1).y, PointAfterZooming(P2).x, PointAfterZooming(P2).y, PointAfterZooming(P3).x, PointAfterZooming(P3).y, style);
}

void Output::changeCrntBkGrndColor(color Clr) 
{
	UI.BkGrndColor=Clr;
}

void Output::changeCrntDrawColor(color Clr) 
{
	UI.DrawColor=Clr;
}

void Output::changeCrntFillColor(color Clr) 
{
	UI.FillColor = Clr;
}

void Output::changeCrntPenWidth(int penWidth)
{
	UI.PenWidth=penWidth;
}

void Output::setZoomScale(int ZC)
{
	ZoomScale = ZC;
}

void Output::setZoomPoint(Point ZP)
{
	ZoomPoint = ZP;
}

//////////////////////////////////////////////////////////////////////////////////////////
Output::~Output()
{
	delete pWind;
}

