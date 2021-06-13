#include "Input.h"
#include "Output.h"

Input::Input(window* pW) 
{
	pWind = pW; //point to the passed window
}

void Input::GetPointClicked(int &x, int &y) const
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string Input::GetSrting(Output *pO) const 
{
	string Label;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if(Key == 13 )	//ENTER key is pressed
			return Label;
		if(Key == 8 && Label.size()!= 0)	//BackSpace is pressed
			Label.resize(Label.size() -1 );			
		else if(Key != 8)
			Label+= Key;
		pO->PrintMessage(Label);
	}
}

color Input::GetChosenColor(int i) const
{
	int x,y;
	pWind->WaitMouseClick(x, y);
	if ( (PALETTE_COUNT * 40) <= x && x <= (PALETTE_COUNT * 40) + 300 && y>50 && y<350)
		return color(0, 0, 0);
	if (y >= 51 && y < 91){
		int ClickedItemOrder = (x / 40);

		switch(ClickedItemOrder){

		case PALETTE_WHITE: return color(255,255,255);
		case PALETTE_DEFAULT: return color(250, 250, 210);
		case PALETTE_YELLOW: return color(255, 200, 46);
		case PALETTE_YELLOW_DARK: return color(255, 162, 1);
		case PALETTE_ORANGE: return color(252, 81, 29);
		case PALETTE_GREEN_BRIGHT: return color(217, 231, 100);
		case PALETTE_GREEN_LIGHT: return color(98, 255, 124);
		case PALETTE_DEGREE_GREEN: return color(83, 199, 159);
		case PALETTE_GREEN: return color(32, 117, 59);
		case PALETTE_NILE_LIGHT: return color(165, 206, 255);
		case PALETTE_NILE: return color(56, 166, 255);
		case PALETTE_NILE_DARK: return color(0, 102, 102);
		case PALETTE_BLUE: return color(50, 66, 166);
		case PALETTE_BLUE_DARK: return color(55, 46, 111);
		case PALETTE_PINK: return color(254, 196, 228);
		case PALETTE_VIOLET_LIGHT: return color(212, 32, 234);
		case PALETTE_VIOLET: return color(102, 39, 112);
		case PALETTE_RED: return color(255, 0, 0);
		case PALETTE_RED_DARK1: return color(183, 60, 60);
		case PALETTE_RED_DARK2: return color(102, 0, 0);
		case PALETTE_BROWN: return color(162, 93, 40);
		case PALETTE_GRAY: return color(153, 153, 153);
		case PALETTE_BLACK: return color(5, 5, 5);
		default: if(i == 0) return UI.DrawColor;
				 else if(i == 1) return UI.FillColor;
				 else return UI.BkGrndColor;
		}
	}

	if(i == 0) return UI.DrawColor;
	else if(i == 1) return UI.FillColor;
	else return UI.BkGrndColor;
}

int Input::GetChosenPenWidth() const
{
	int x,y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if(x >= ITM_BORDER_WIDTH_d*50 && x < ITM_BACKGROUND_CLR*50){
		if(y < 50) return UI.PenWidth;
		int ClickedItemOrder = ((y-50) / 25); //wanted to edit

		switch (ClickedItemOrder)
		{
		case 0: return 1;
		case 1: return 3;
		case 2: return 6;
		case 3: return 9;
		case 4: return 12;
		case 5: return 15;
		case 6: return 20;
		default: return UI.PenWidth;
		}
	}
	return UI.PenWidth;
}

int Input::GetChosenAngle() const
{
	int x,y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if(x >= ITM_ROTATE*50 && x < ITM_FRONT*50)
	{
		if(y<50) return 0;
		int ClickedItemOrder = ((y-50)/50); //wanted to edit

		switch (ClickedItemOrder)
		{
		case 0: return 90;
		case 1: return 180;
		case 2: return 270;
		default: return 0;
		}
	}
	return 0;
}

float Input::GetChosenFactor() const
{
	int x,y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if(x >= ITM_RESIZE*50 && x < ITM_ZOOM_IN*50){
		if(y<50) return 1;
		int ClickedItemOrder = ((y-50)/50); //wanted to edit

		switch (ClickedItemOrder)
		{
		case 0: return 2;
		case 1: return 4;
		case 2: return 0.5;
		case 3: return 0.25;
		default: return 1;
		}
	}
	return 1;
}

bool Input::GetChosenStatus(bool& status, bool isInZoom) const
{
	int x,y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if(!isInZoom && x >= ITM_FILL_CLR_d*50 && x < ITM_BORDER_WIDTH_d*50){
		if(y < 50) return false;
		int ClickedItemOrder = ((y-50)/50);

		switch (ClickedItemOrder)
		{
		case 0: status = true;
				return true;
		case 1: status=false;
				return true;
		default: return false;
		}
		return false;
	}
	else if(isInZoom && x >= 50 && x < 100){
		int ClickedItemOrder = ((y-50)/50);

		switch (ClickedItemOrder)
		{
		case 0: status = true;
				return true;
		case 1: status=false;
				return true;
		default: return false;
		}
		return false;

	}
	return false;
}

int Input::GetChosenGameMode() const
{
	int x, y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if(y >= 51 && y < 126){
		int ClickedItemOrder = (x / 75);

		switch (ClickedItemOrder)
		{
		case 0: return 0;
		case 1: return 1;
		case 2: return 2;
		case 3: return 3;
		default: return -1;
		}
	}
	return -1;
}

//This function reads the position where the user clicks to determine the desired action
ActionType Input::GetUserAction(bool isInZoom) const
{	
	int x,y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if(UI.InterfaceMode == MODE_DRAW)	//GUI in the DRAW mode
	{
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight && !isInZoom)
		{	
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_RECT: return DRAW_RECT;
			case ITM_CIRC: return DRAW_CIRC;
			case ITM_LINE: return DRAW_LINE;
			case ITM_TRI: return DRAW_TRI;

			case ITM_DRAW_CLR_d: return DRAW_CLR_d;
			case ITM_FILL_CLR_d: return FILL_CLR_d;

			case ITM_BORDER_WIDTH_d: return BORDER_WIDTH_d;
			case ITM_BACKGROUND_CLR: return BACKGROUND_CLR;

			case ITM_SELECT: return SELECT;
			case ITM_CUT: return CUT;
			case ITM_COPY: return COPY;
			case ITM_PASTE: return PASTE;
			case ITM_DEL: return DEL;
			case ITM_MOVE: return MOVE;

			case ITM_RESIZE: return RESIZE;
			case ITM_ROTATE: return ROTATE;
			case ITM_ZOOM_IN : return ZOOM_IN;
			case ITM_ZOOM_OUT: return ZOOM_OUT;
			case ITM_FRONT: return FRONT;
			case ITM_BACK: return BACK;

			/*case ITM_UNDO: return UNDO;
			case ITM_REDO: return REDO;*/
			case ITM_SAVE: return SAVE;
			case ITM_LOAD: return LOAD;
			case ITM_TO_PLAY: return TO_PLAY;
			case ITM_EXIT_DRAW: return EXIT;	
			
			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}

		else if (y >= 0 && y < UI.ToolBarHeight && isInZoom) //for ToolBar while zooming
		{	
			int ClickedItemOrder = (x / UI.MenuItemWidth);

			switch (ClickedItemOrder)
			{
			
			case 0: return DRAW_CLR_d;
			case 1: return FILL_CLR_d;
			case 2: return BACKGROUND_CLR;
			case 3: return SELECT;
			case 4: return DEL;
			case 5: return ZOOM_IN;
			case 6: return ZOOM_OUT;
			/*case 7: return UNDO;
			case 8: return REDO;*/
			case 7: return SAVE;
			case 8: return LOAD;
			case 9: return EXIT;
			
			default: return EMPTY;
			}
		}

		//[2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;	
		}
		
		//[3] User clicks on the status bar
		return STATUS;
	}
	else if(!isInZoom)	//GUI is in PLAY mode
	{
		int click = (x / UI.MenuItemWidth);
		switch (click)
		{
		case ITM_PICK_HIDE :return PICK_HIDE;
		case ITM_SCRAMBLE_FIND: return SCRAMBLE_FIND;
		case ITM_TO_DRAW: return TO_DRAW ;
		case ITM_EXIT_PLAY: return EXIT;
		default: return EMPTY;
		}
		return TO_PLAY;	//just for now. This should be updated
	}	
	return EMPTY;
}

ActionType Input::GetUserAction(Point P, bool isInZoom) const
{	
	if(UI.InterfaceMode == MODE_DRAW)	//GUI in the DRAW mode
	{
		//[1] If user clicks on the Toolbar
		if (P.y >= 0 && P.y < UI.ToolBarHeight && !isInZoom)
		{	
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (P.x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_RECT: return DRAW_RECT;
			case ITM_CIRC: return DRAW_CIRC;
			case ITM_LINE: return DRAW_LINE;
			case ITM_TRI: return DRAW_TRI;

			case ITM_DRAW_CLR_d: return DRAW_CLR_d;
			case ITM_FILL_CLR_d: return FILL_CLR_d;

			case ITM_BORDER_WIDTH_d: return BORDER_WIDTH_d;
			case ITM_BACKGROUND_CLR: return BACKGROUND_CLR;

			case ITM_SELECT: return SELECT;
			case ITM_CUT: return CUT;
			case ITM_COPY: return COPY;
			case ITM_PASTE: return PASTE;
			case ITM_DEL: return DEL;
			case ITM_MOVE: return MOVE;

			case ITM_RESIZE: return RESIZE;
			case ITM_ROTATE: return ROTATE;
			case ITM_ZOOM_IN : return ZOOM_IN;
			case ITM_ZOOM_OUT: return ZOOM_OUT;
			case ITM_FRONT: return FRONT;
			case ITM_BACK: return BACK;

			/*case ITM_UNDO: return UNDO;
			case ITM_REDO: return REDO;*/
			case ITM_SAVE: return SAVE;
			case ITM_LOAD: return LOAD;
			case ITM_TO_PLAY: return TO_PLAY;
			case ITM_EXIT_DRAW: return EXIT;	
			
			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}

		else if (P.y >= 0 && P.y < UI.ToolBarHeight && isInZoom) //for ToolBar while zooming
		{	
			int ClickedItemOrder = (P.x / UI.MenuItemWidth);

			switch (ClickedItemOrder)
			{
			
			case 0: return DRAW_CLR_d;
			case 1: return FILL_CLR_d;
			case 2: return BACKGROUND_CLR;
			case 3: return SELECT;
			case 4: return DEL;
			case 5: return ZOOM_IN;
			case 6: return ZOOM_OUT;
			/*case 7: return UNDO;
			case 8: return REDO;*/
			case 7: return SAVE;
			case 8: return LOAD;
			case 9: return EXIT;
			
			default: return EMPTY;
			}
		}
		return EMPTY;
	}
	else if(!isInZoom)	//GUI is in PLAY mode
	{
		int Clicked = (P.x / UI.MenuItemWidth);
		switch (Clicked)
		{
		case ITM_PICK_HIDE :return PICK_HIDE;
		case ITM_SCRAMBLE_FIND: return SCRAMBLE_FIND;
		case ITM_TO_DRAW: return TO_DRAW ;
		case ITM_EXIT_PLAY: return EXIT;
		default: return EMPTY;
		}
		return TO_PLAY;	//just for now. This should be updated
	}	
	return EMPTY;
}
/////////////////////////////////

Input::~Input()
{
}
