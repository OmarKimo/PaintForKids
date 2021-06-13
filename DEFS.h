#ifndef DEFS_H
#define DEFS_H

#include "CMUgraphicsLib\CMUgraphics.h"

//This file contais some global constants and definitions to be used in the project.
enum ActionType //The actions supported (you can add more if needed)
{
	//draw mode
	DRAW_LINE,		//Draw Line
	DRAW_RECT,		//Draw Rectangle
	DRAW_TRI,		//Draw Triangle
	DRAW_CIRC,		//Draw Circle

	DRAW_CLR_d,	//Change the drawing color -defult
	FILL_CLR_d,	//Change the filling color -defult
	BACKGROUND_CLR,	//Change background color 
	BORDER_WIDTH_d, //change border drawing width
	SELECT,			//for select fig
	CUT,
	COPY,
	PASTE,
	DEL,			//Delete a figure(s)
	MOVE,			//Move a figure(s)
	MOVE_DRAG,
	RESIZE,			//Resize a figure(s)
	RESIZE_DRAG,
	ROTATE,			//Rotate a figure(s)
	ZOOM_IN,
	ZOOM_OUT,
	FRONT,
	BACK,
	UNDO,			//for return
	REDO,			//redo
	SAVE,			//Save the whole graph to a file
	LOAD,			//Load a graph from a file
	TO_PLAY,		//Switch interface to Play mode
	EXIT,			//Exit the application


	//play mode
	SCRAMBLE_FIND,		//the another game	
	PICK_HIDE,		 // Pick & Hide game	
	TO_DRAW,		//Switch interface to Draw mode


	DRAWING_AREA,	//A click on the drawing area
	STATUS,			//A click on the status bar
	EMPTY,			//A click on empty place in the toolbar

};

struct Point	//To be used for figures points
{
	int x, y;
	/*Point(int a, int b) : x(a), y(b) {}
	Point() : x(0), y(0) {}
	Point operator+(const Point& p)
	{
	return Point(this->x + p.x, this->y + p.y);
	}
	Point operator-(const Point& p)
	{
	return Point(this->x - p.x, this->y - p.y);
	}
	Point operator+(const int& num)
	{
	return Point(this->x + num, this->y + num);
	}
	Point operator-(const int& num)
	{
	return Point(this->x - num, this->y - num);
	}
	bool operator>(const Point& p) const
	{
	return ((this->x > p.x) && (this->y > p.y)) ? true : false;
	}

	bool operator<(const Point& p) const
	{
	return ((this->x > p.x) && (this->y > p.y)) ? false : true;
	}
	bool operator==(const Point& p)
	{
	return (this->x == p.x) && (this->y == p.y);
	}
	bool operator!=(const Point& p)
	{
	return !((this->x == p.x) && (this->y == p.y));
	}*/
};

struct GfxInfo	//Graphical info of each figure (you may add more members)
{
	color DrawClr;	//Draw color of the figure
	color FillClr;	//Fill color of the figure
	bool isFilled;	//Figure Filled or not
	int BorderWdth;	//Width of figure borders

};


#endif