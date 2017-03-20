#include "classes.h"
/* TODO (#1#): menu includes a working UP/DOWN(W/S) key control,
				moving visible selection pointer, and choices */
int main(int argc, char*args[])
{
	SDL_Surface *image = NULL;
	
	screen = StartSDL(image);
	
	Menus MenuController;
	
	Intro Introduction;
		
	int NextStep = MenuController.StartMenu(image);
	
	switch (NextStep)
	{
		case 1://START GAME
		Introduction.IntroScreen();
//			MenuController.StartGame();
			break;
		case 2://LOAD SAVE(VERY LAST)
			
			break;
		case 3://SETTINGS SECOND TO LAST
			
			break;
		case 4://EXIT
			return 0;
	}
	
	return 0;//TEMP TO END PROCESS PROPERLY
}
