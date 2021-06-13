#ifndef OUPTUT_H
#define OUPTUT_H
#include "Input.h"

class Output	//The application manager should have a pointer to this class
{
private:	
	window* pWind;	//Pointer to the Graphics Window
	int ZoomScale;
	Point ZoomPoint;

public:
	Output();		

	window* CreateWind(int, int, int , int) const; //creates the application window
	void CreateDrawToolBar() const;	//creates Draw mode toolbar & menu
	void CreateToolBar_Zoom() const;	//creates Draw mode toolbar while Zooming
	void CreatePlayToolBar() const;	//creates Play mode toolbar & menu
	void CreateStatusBar() const;	//create the status bar
	void CreatePaletteBar() const;	//create the palette of colors
	void CreateBorderMenu() const;	//create submenu for change border width
	void CreateRotateMenu() const;	//create submenu for rotate
	void CreateResizeMenu() const;	//create submenu for resize
	void CreateFillStatusMenu(bool isInZoom = false) const;	//create submenu for change fill color
	void CreatePickHideBar() const;

	Input* CreateInput() const; //creates a pointer to the Input object	
	void ClearStatusBar() const;	//Clears the status bar
	void ClearDrawArea() const;	//Clears the drawing area
	
	// -- Figures Drawing functions
	void DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected=false);  //Draw a rectangle
	void DrawCirc(Point P1, const int Radius, GfxInfo CircGfxInfo, bool selected=false);  //Draw a circle
	void DrawLine(Point P1, Point P2, GfxInfo LineGfxInfo, bool selected=false);  //Draw a line
	void DrawTri(Point P1, Point P2, Point P3, GfxInfo TriaGfxInfo, bool selected=false);  //Draw a triangle
	
	Point PointAfterZooming(const Point); //to change the coordinates of a point after zooming
	int BorderAfterZooming(const int);

	void PrintMessage(string msg) const;	//Print a message on Status bar

	color getCrntDrawColor() const;		//get current drawing color
	color getCrntFillColor() const;		//get current filling color
	color getCrntBkGrndColor() const;	//get current background color
	int getCrntPenWidth() const;		//get current pen width
	int getZoomScale() const;
	Point getZoomPoint() const;

	void changeCrntBkGrndColor(color);	//change current background color
	void changeCrntDrawColor(color);	//cahnge current drawing color
	void changeCrntFillColor(color);	//change current filling color
	void changeCrntPenWidth(int);	//change current pen width
	void setZoomScale(int ZC);
	void setZoomPoint(Point ZP);

	window* getpwind(); 
	int count; 
	~Output();
};

#endif