#ifndef UI_INFO_H
#define UI_INFO_H

#include "..\CMUgraphicsLib\CMUgraphics.h"

//User Interface information file.
//This file contains info that is needed by Input and Output classes to
//handle the user interface

enum GUI_MODE	//Graphical user interface mode
{
	MODE_DRAW,	//Drawing mode (startup mode)
	MODE_PLAY	//Playing mode
};

enum DrawMenuItem //The items of the Draw menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	//If you want to change the menu items order, change the order here
	ITM_RECT,		//Recangle item in menu
	ITM_CIRC,		//Circle item in menu
	ITM_LINE,
	ITM_TRI,
	ITM_DRAW_CLR_d,
	ITM_FILL_CLR_d,
	ITM_BORDER_WIDTH_d,
	ITM_BACKGROUND_CLR,
	ITM_SELECT,
	ITM_CUT,
	ITM_COPY,
	ITM_PASTE,
	ITM_DEL,
	ITM_MOVE,
	ITM_RESIZE,
	ITM_ZOOM_IN,
	ITM_ZOOM_OUT,
	ITM_ROTATE,
	ITM_FRONT,
	ITM_BACK,
	/*ITM_UNDO,
	ITM_REDO,*/
	ITM_SAVE,
	ITM_LOAD,
	ITM_TO_PLAY,
	ITM_EXIT_DRAW,		//Exit item
	
	DRAW_ITM_COUNT		//no. of menu items ==> This should be the last line in this enum
	
};


enum PlayMenuItem //The items of the Play menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	//If you want to change the menu items order, change the order here
	
	ITM_PICK_HIDE,
	ITM_SCRAMBLE_FIND,
	ITM_TO_DRAW,
	ITM_EXIT_PLAY,
	PLAY_ITM_COUNT		//no. of menu items ==> This should be the last line in this enum
	
};

enum PaletteColors
{
	PALETTE_WHITE,
	PALETTE_DEFAULT,
	PALETTE_YELLOW,
	PALETTE_YELLOW_DARK,
	PALETTE_ORANGE,
	PALETTE_GREEN_BRIGHT,
	PALETTE_GREEN_LIGHT,
	PALETTE_DEGREE_GREEN,
	PALETTE_GREEN,
	PALETTE_NILE_LIGHT,
	PALETTE_NILE,
	PALETTE_NILE_DARK,
	PALETTE_BLUE,
	PALETTE_BLUE_DARK,
	PALETTE_PINK,
	PALETTE_VIOLET_LIGHT,
	PALETTE_VIOLET,
	PALETTE_RED,
	PALETTE_RED_DARK1,
	PALETTE_RED_DARK2,
	PALETTE_BROWN,
	PALETTE_GRAY,
	PALETTE_BLACK,
	PALETTE_COUNT
	/*PALETTE_WHITE,
	PALETTE_WHITE,*/
};

enum PickFindOptions
{
	PICK_TYPE,
	PICK_COLOR,
	PICK_TYPE_COLOR,
	PICK_AREA
};

__declspec(selectany) //This line to prevent "redefinition error"

struct UI_Info	//User Interface Info.
{
	GUI_MODE InterfaceMode;
	
	int	width, height,	//Window width and height
		wx , wy,			//Window starting coordinates
		StatusBarHeight,	//Status Bar Height
		ToolBarHeight,		//Tool Bar Height (distance from top of window to bottom line of toolbar)
		MenuItemWidth;		//Width of each item in toolbar menu
	

	color DrawColor;		//Drawing color
	color FillColor;		//Filling color
	color HighlightColor;	//Highlighting color
	color MsgColor;			//Messages color
	color BkGrndColor;		//Background color
	color StatusBarColor;	//Status bar color
	int PenWidth;			//width of the pen that draws shapes

	/// Add more members if needed
	
}UI;	//create a global object UI

#endif