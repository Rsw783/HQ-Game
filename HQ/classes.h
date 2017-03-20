#ifndef HAREMQUEST_H
#define HAREMQUEST_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
//#include <SDL/SDL_mixer.h>
#include <windows.h>
#include <cstring>
#include <string>

SDL_Surface *screen = NULL;
SDL_Event event;

class Menus
{
	private:
		int pointerPos, quit;
		SDL_Rect pointerArea;
	public:
		friend class Intro;
		int StartMenu(SDL_Surface*);//the games start menu
		int StartGame();//start the game after Intro
};

class Intro
{
	protected:	
		std::string str;
		SDL_Surface *text;
		TTF_Font *font;
		SDL_Color textColor;
	public:
		Intro();
		void Handle_Input();
		void IntroScreen(); //ask the user Intro to get their first harem member
};


int Menus::StartMenu(SDL_Surface *pointer)
{
	pointerPos=1;
	quit=0;
	
	SDL_Event event;
	
	SDL_Rect pointerArea;
	pointerArea.x = 17;
	pointerArea.y = 24;
	pointerArea.w = 25;
	pointerArea.h = 20;
	
	pointer = SDL_LoadBMP("Images/Basic Pointer.bmp");
	SDL_BlitSurface(pointer,NULL,screen,&pointerArea);
	SDL_Flip(screen);
	

	
	while (quit==0)
	{
		while (SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT://the user closes the program
					quit=4;
					break;
				case SDL_KEYDOWN://the user presses a key
					switch(event.key.keysym.sym)
					{
						case SDLK_DOWN://down is pressed
							SDL_FillRect(screen, &pointerArea, 0xFFFFFF);
							if (pointerPos <4 )
							{
								pointerPos++;//move the pointer down one position
								pointerArea.y+=36;//actually move the pointers visible position
							}
							else
							{
								pointerPos=1;//move the pointer back to the first choice
								pointerArea.y=24;
							}
							SDL_BlitSurface(pointer,NULL,screen,&pointerArea);
							SDL_Flip(screen);
							break;						
						case SDLK_UP://up is pressed
							SDL_FillRect(screen, &pointerArea, 0xFFFFFF);
							if (pointerPos >1)
							{
								pointerPos--;//move the pointer up visibly on position
								pointerArea.y-=36;
							}
							else 
							{
								pointerPos=4;//move the pointer back to the first choice
								pointerArea.y=132;
							}
							SDL_BlitSurface(pointer,NULL,screen,&pointerArea);
							SDL_Flip(screen);
							break;					
						case SDLK_z://Z is pressed						
							switch(pointerPos)
							{
								case 1://its in position 1, New Game
									quit=1;
									break;
								case 2://Position 2, Load
									quit=2;
									break;
								case 3://Position 3, Settings
									quit=3;
									break;
								case 4://Position 4, Exit
									quit=4;
									break;
							}	
							break;											
						case SDLK_ESCAPE://escape is pressed
							quit=4;
							break;
					}
					break;
			}	
		}
	}
	
	if(quit==1)
		return 1;
	else if(quit==2)
		return 2;
	else if(quit==3)
		return 3;
	else if (quit==4)
		return 4;
}

int Menus::StartGame()
{
/* TODO (#1#): display menu screen, pointer, playername, 
               gold  */
	SDL_Surface *menu = NULL, *pointer = NULL;
	SDL_Rect menuArea, playerStats, wholeScreen;
	
	wholeScreen.x = wholeScreen.y = 0;
	wholeScreen.h = 640;
	wholeScreen.w = 400;
	
	menuArea.x = menuArea.y = 0;
	
	pointerArea.x = 15;
	pointerArea.y = 17;//move 36 to get to next spot
	
	menu = SDL_LoadBMP("Images/Ingame Menu.bmp");
	pointer = SDL_LoadBMP("Images/Basic Pointer.bmp");
	

	SDL_FillRect(screen,&wholeScreen,0xFFFAF0);
	SDL_BlitSurface(menu,NULL,screen,&menuArea);
	SDL_BlitSurface(pointer,NULL,screen,&pointerArea);
	SDL_Flip(screen);
	
	quit = 0; 
	pointerPos=1;
		
	while (quit==0)
	{
		while (SDL_PollEvent(&event))
		{
			switch(event.type)
			{	
				case SDL_QUIT://the user closes the program
					quit=1;
					break;
				case SDL_KEYDOWN://the user presses a key
					switch(event.key.keysym.sym)
					{
						case SDLK_ESCAPE://escape is pressed
							quit=1;
							break;
						case SDLK_DOWN:
							SDL_FillRect(screen, &pointerArea, 0xFFFFFF);
							if (pointerPos <6 )
							{
								pointerPos++;//move the pointer down visibly one position
								pointerArea.y+=37;
							}
							else
							{
								pointerPos=1;//move the pointer back to the first choice
								pointerArea.y=17;
							}
							SDL_BlitSurface(pointer,NULL,screen,&pointerArea);
							SDL_Flip(screen);//display the pointer
							break;
						case SDLK_UP:
							SDL_FillRect(screen, &pointerArea, 0xFFFFFF);
							if (pointerPos >1)
							{
								pointerPos--;//move the pointer up visibly on position
								pointerArea.y-=37;
							}
							else 
							{
								pointerPos=4;//move the pointer back to the first choice
								pointerArea.y=203;
							}
							SDL_BlitSurface(pointer,NULL,screen,&pointerArea);
							SDL_Flip(screen);//display the pointer
							break;
						case SDLK_z:
							switch(pointerPos)
							{
								case 1://its in position 1, Inventory
									quit=1;
									break;
								case 2://Position 2, Fight
									quit=2;
									break;
								case 3://Position 3, Shop
									quit=3;
									break;
								case 4://Position 4, Save
									quit=4;
									break;
								case 5://position 5, options
									quit=5;
									break;
								case 6://exit
									quit=6;
									break;
							}	
							break;				
					}
			}
		}
	}

	return quit;
}



SDL_Surface* StartSDL(SDL_Surface *imageSurface)
{		
	const int Width = 640, Height = 400;
	SDL_Rect wholeScreen, menuArea;
	wholeScreen.x = wholeScreen.y = menuArea.x = menuArea.y = 0;
	wholeScreen.h = Height;
	wholeScreen.w = Width;
	imageSurface = SDL_LoadBMP("Images/Basic Menu.bmp");
	
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	
	atexit(SDL_Quit);//when the program ends, end SDL
	atexit(TTF_Quit);//^same but TTF
	
	SDL_WM_SetCaption("HaremQuest", "HQ");

	screen = SDL_SetVideoMode(Width, Height, 32, SDL_HWSURFACE);

	SDL_FillRect(screen, &wholeScreen, 0xFFFAF0 );
	SDL_BlitSurface(imageSurface,NULL,screen,&menuArea);
	SDL_Flip(screen);
	SDL_FreeSurface(imageSurface);	
	
	return screen;
}

void Intro::IntroScreen()
{//get the users name ask who they want
	SDL_Surface *questions = NULL, *nameText = NULL;
	SDL_Rect textWindow;
	
	textWindow.x = textWindow.y = 0;
	SDL_Rect name;
	name.x=184;
	name.y=244;
	bool quit=false;
	int storyScreen = 1;
	
	questions = SDL_LoadBMP("Images/Story Screen 1.bmp");
	SDL_BlitSurface(questions,NULL,screen,&textWindow);
	SDL_Flip(screen);
	
	while (quit==false)
	{
		while (SDL_PollEvent(&event))
		{
			switch(event.type)
			{	
				case SDL_QUIT://the user closes the program
					quit = true;
					break;
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_z)
					{
						storyScreen++;
						switch(storyScreen)
						{
							case 2:
								questions=SDL_LoadBMP("Images/Story Screen 2.bmp");
								break;
							case 3:
								questions=SDL_LoadBMP("Images/Story Screen 3.bmp");
								break;
							case 4:
								questions=SDL_LoadBMP("Images/Story Screen 4.bmp");
								//make a menu for the fucking name entering shit
								break;
							case 5:
								quit=true;
								break;
						}
						SDL_BlitSurface(questions,NULL,screen,&textWindow);
						SDL_Flip(screen);
						
					}
					else if (event.key.keysym.sym == SDLK_RETURN)
					{
						Menus Next;
						Next.StartGame();			
					}
					break;
				}
			}
		}
	
}

Intro::Intro()
{
    //Initialize the string
    str = "";

    //Initialize the surface
    text = NULL;

    //Enable Unicode
    SDL_EnableUNICODE( SDL_ENABLE );
    
    font = NULL;
	SDL_Color textColor = {100, 0, 0};
	font = TTF_OpenFont("calibri.ttf", 28);
}

void Intro::Handle_Input()
{
	
	
	bool quit=false;
	
    //If a key was pressed
    while(quit==false)
    {
	   	if( event.type == SDL_KEYDOWN )
	    {
	        //Keep a copy of the current version of the string
	        
	
	        //If the string less than maximum size
	        
	
	        //If backspace was pressed and the string isn't blank
	        
	        
	        
	        
	    }
    }
    
    
    
}		
#endif
