//Name:		Brandon Shaw
//File:		GameEvents.cpp
//Scope:	Defines the GameEvents class
//			controls all rendering and user inputs.


#include <sstream>
#include <iostream>
#include "GameEvents.h"
#include "BarList.h"
#include "Bar.h"

//Default calss constructor:
GameEvents::GameEvents()
{
	Background = NULL;
	Screen = NULL;
	StartTitle = true;
	GameRunning = true;
	Message = NULL;
	MessageEnter = NULL;
	RectAmountMessage = NULL;
	NumofRects = "";
	UserInputCheck = true;
}

//Default Deconstructor:
GameEvents::~GameEvents()
{};


//Checks for users input during the tiltle screen
//Either records input value for rectangles or
//sets the title display and game running bools to false to exit program.
//Recognises number inputs from the keyboard.
//When the return key is plessed the validateInput function is call, this accepts a string.
void GameEvents::gameStart()
{
	SDL_Event event;

	if(SDL_PollEvent(&event))
	{
		if(event.type == SDL_KEYDOWN)
		{
			switch(event.key.keysym.sym)
			{
				case SDLK_RETURN: validateInput(NumofRects);
					break;

				case SDLK_0: NumofRects += "0";
					break;

				case SDLK_1: NumofRects += "1";
					break;

				case SDLK_2: NumofRects += "2";
					break;

				case SDLK_3: NumofRects += "3";
					break;

				case SDLK_4: NumofRects += "4";
					break;

				case SDLK_5: NumofRects += "5";
					break;

				case SDLK_6: NumofRects += "6";
					break;

				case SDLK_7: NumofRects += "7";
					break;

				case SDLK_8: NumofRects += "8";
					break;

				case SDLK_9: NumofRects += "9";
					break;	
			}
		}
		else if (event.type == SDL_QUIT)
		{
			StartTitle = false;
			GameRunning = false;
		}
	}
}

//This functions controls the exiting of the program:
void GameEvents::gameExit()
{
	SDL_Event event;

	while(SDL_PollEvent(&event))
	{
		if(event.type == SDL_QUIT)
		{
			GameRunning = false;
		}
	}
}

//Function to control the creation of the window.
//Initialization of the screen surface as well as the font controller.
//If either of those fail to load false is returned to the main function andthe program is closed.
bool GameEvents::gameInit()
{
	//Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

	//Set up the screen
    Screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

	//If there was an error in setting up the screen:
    if( Screen == NULL )
    {
        return false;
    }

	//If there was an error setting up the font:
	if(TTF_Init() == -1)
	{
		return false;
	}

	//Set the window caption
    SDL_WM_SetCaption( "Rotating Rectangle Problem", NULL );

    //If everything initialized fine
    return true;
}

//Specifies the images and the actual font to use:
//The image path is sent to the load_image function which is use to optimize the image.
//The font path is sent to a library function to load.
//If either fails program will end.
bool GameEvents::gameLoad()
{
	Background = load_Image("Images\\background.png");

	//Open the font:
	Font = TTF_OpenFont("Fonts\\AgentOrange.ttf", 20);

	//If there was an error setting up the background:
	if(Background == NULL)
	{
		return false;
	}

	//If there was an error setting up the font:
	if(Font == NULL)
	{
		return false;
	}

	//If everything loaded fine:
	return true;
}

//Creating the optimized image
//What this function does is load the image, then returns a pointer to the optimized version of the loaded image.
//The argument "filename" is the path of the image to be loaded. 
//"loadedImage" is the surface we get when the image is loaded. 
//"optimizedImage" is the surface that is going to be used.
SDL_Surface* GameEvents::load_Image(std::string filename)
{
	//The image that's loaded:
	SDL_Surface* loadedImage = NULL;

	//The optimized surface that will be used:
	SDL_Surface* optimizedImage = NULL;

	//Load the image
    loadedImage = IMG_Load( filename.c_str() );

	//If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimized surface
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old surface
        SDL_FreeSurface( loadedImage );

        //If the surface was optimized
        if( optimizedImage != NULL )
        {
            //Color key surface
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
        }
    }

    //Return the optimized surface
    return optimizedImage;
}

//Here we have our surface blitting function.
//It takes in the coordinates of where you want to blit the surface, 
//the surface you're going to blit and the surface you're going to blit it to.
//First we take the offsets and put them inside an SDL_Rect. 
//We do this because SDL_BlitSurface() only accepts the offsets inside of an SDL_Rect.
//An SDL_Rect is a data type that represents a rectangle. 
//It has four members representinghe X and Y offsets, the width and the height of a rectangle. Here we're only concerned about x and y data members.
void GameEvents::gameDraw(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{
	//Holds offsets:
	SDL_Rect offset;

	//Get offsets:
	offset.x = x;
	offset.y = y;

	//Blit:
	SDL_BlitSurface(source, clip, destination, &offset);
}

//Render text to the screen
//Accepts the screen to be used. Value stored in Constants.h
unsigned short int GameEvents::gameDrawText(std::string text)
{
	//Clear screen
	SDL_FillRect(Screen, NULL, 0x000000);

	//The color of the font:
	SDL_Color textColor = { 255,255,255};
	int w1, h1;
	int w2, h2;
	int w3, h3;

	//Taking the input strings and converting it to be used with SDL:
	std::stringstream userinput;
	std::stringstream textstream;
	userinput << NumofRects;
	textstream << text;
	std::string rectNumber = userinput.str();
	std::string displayText = textstream.str();

	//Render the text:
	Message = TTF_RenderText_Solid(Font, displayText.c_str() , textColor); 
	TTF_SizeText(Font, displayText.c_str(), &w1,&h1);
	MessageEnter = TTF_RenderText_Solid( Font, "Press Enter to start", textColor );
	TTF_SizeText(Font, "Press Enter to start", &w2, &h2);
	RectAmountMessage = TTF_RenderText_Solid(Font, rectNumber.c_str(), textColor);
	TTF_SizeText(Font, rectNumber.c_str(), &w3, &h3);

	//if there is an error in rendering the text:
	if(Message  == NULL)
	{
		return 1;
	}

	if(MessageEnter == NULL)
	{
		return 1;
	}

	//Apply the text to the screen:
	gameDraw((SCREEN_WIDTH - w1) / 2, (SCREEN_HEIGHT - h1) / 2, Message, Screen, NULL);
	gameDraw((SCREEN_WIDTH - w2) / 2, ((SCREEN_HEIGHT - h1) / 2) + h2, MessageEnter, Screen, NULL);
	gameDraw((SCREEN_WIDTH - w2) / 2, ((SCREEN_HEIGHT - h1) / 2) + h1 + h2 + h3, RectAmountMessage, Screen, NULL);
}

//Render Columns to screen
//Accepts a pointer to the list and a bool value to alternate bar colours.
void GameEvents::gameDrawCol(BarList* BList, bool colorSwop)
{
	
	Bar *tp = BList->Head;
	Uint32 Color = SDL_MapRGB(Screen->format, 0xff, 0xff, 0xff);
	Uint32 Color2 = SDL_MapRGB(Screen->format, 0xff, 0xcc, 0xcc);
	//bool colorSwop = true;
	
	//Steps through the list frawing the colums
	//using SDL Fillrect function.
	//Atlernates colours using the boolean
	while(tp != nullptr)
	{
		if(colorSwop)
		{
			SDL_FillRect(Screen,&tp->Column,Color);
			tp = tp->Next;
			colorSwop = false;
		}else
		{
			SDL_FillRect(Screen,&tp->Column,Color2);
			tp = tp->Next;
			colorSwop = true;
		}
	}
}

//This function controls the transformation of the bars.
//Reads through the origianl list.
//finds the smallest column.
//Sets the smallest column's x co-ord to the x co-rds of the first element in the list
//and its width to the total width of th list.
//adds this element to the new list that will be drawn.
//Then removes the smallest's height from all columns in the list.
//Then adds all the colums to the left of it to a list called left and
//and all the colums to the right in a list called right.
//Function is called recursively untill there are no more elements in all lists including the original.
void GameEvents::gameTransform(BarList* list, BarList* drawList)
{
	BarList* left = new BarList();
	BarList* right = new BarList();
	Bar* tp = list->Head;
	Bar *smallest = list->Head;
	unsigned short int totalWidth = 0;
	bool smallestDeleted = false;

	while(list->Count != 0)
	{
		//Find the smallest column
		//Accumulate the total width.
		while(tp != nullptr)
		{
			totalWidth += tp->Column.w;
			if(tp->Column.h <= smallest->Column.h)
			{
				smallest = tp;
			}
			tp = tp->Next;
		}

		//Set width and x co-ord, width values and add to draw list:
		smallest->Column.x = list->Head->Column.x;
		smallest->Column.w = totalWidth;
		drawList->addToTail(smallest, BASELINECOUNT);

		//reset tp back to head
		tp = list->Head;

		//remove smallest height from all rects expect smallest:
			while(tp != nullptr)
			{
			if(tp != smallest)
			{
				tp->Column.h -= smallest->Column.h;
			}
			tp = tp->Next;
		}

		//reset tp back to head
		tp = list->Head;

		//adding all colums to either left or right of smallest.
		//Remove smallest from the original list.
		while(tp != nullptr)
		{
			if(tp != smallest && smallestDeleted == false)
			{
				left->addToTail(tp);
				list->deleteNoid(tp);
				tp = list->Head;
			}
			else if(tp == smallest && smallestDeleted == false)
			{	
				list->deleteNoid(tp);
				tp = list->Head;
				smallestDeleted = true;
			}
			else if(smallestDeleted)
			{
				right->addToTail(tp);
				list->deleteNoid(tp);
				tp = list->Head;
			}
		}
		//Recall function with new lists:
		gameTransform(left, drawList);
		gameTransform(right, drawList);
	}

	delete left;
	delete right;
}

//Returns the state of the StartTitle bool.
//Used to keep the title screen open or not.
bool GameEvents::get_TitleState()
{
	return StartTitle;
}

//Refreshes the screen. To display the images
bool GameEvents::gameFlip()
{
	//Update the screen:
	if(SDL_Flip(Screen) == -1)
	{
		return 1;
	}
}

//Validates the user input from the title screen.
void GameEvents::validateInput(std::string numofrects)
{
	//Convert stored string value for the number of rectangles to integer
	//To validate the number is between the correct range.
	int rectvalue = std::atoi(numofrects.c_str());

	if(rectvalue >= 3 && rectvalue <= 30)
	{
		StartTitle = false;
	}
	else
	{
		UserInputCheck = false;
		NumofRects = "";
	}
}

//Returns a boolean use to confirm if the user entired the a valid value.
//Determines the Message displayed on the tilte screen.
bool GameEvents::get_UserIputCheck()
{
	return UserInputCheck;
}

//Boolean used to keep the game running.
//When you user chooses to close the program, this will be set to false.
//The main game loop in the main.cpp will exit.
bool GameEvents::get_runningState()
{
	return GameRunning;
}

//Converts and returns the number of colums inputed by the user into a int.
unsigned short int GameEvents::get_RectNum()
{
	int rectvalue = std::atoi(NumofRects.c_str());
	return rectvalue;
}

//Returns the Screen pointer to the main function to be used to clear the screen.
SDL_Surface* GameEvents::get_Screen()
{
	return Screen;
}

//This Functuion is responsible for writting the new transformed list to the output file.
//Accepts in the new transformed list
//steps through the list and writes in values to the file.
void GameEvents::writeFile(BarList* drawList)
{
	Bar* tp = drawList->Head;
	std::ofstream transformFile ("TransformedRectangles.txt");

	if(transformFile.is_open())
	{
		while(tp != nullptr)
		{
			transformFile << tp->Name << " " << "h:" << tp->Column.h << " " << "w:" << tp->Column.w << std::endl;
			tp = tp->Next;
		}
	}
	else
	{
		std::cerr << "Error opening TransformedRectangles.txt";
	}
	transformFile.close();
}

//Cleans up the SDL objects when the program is closed.
void GameEvents::gameClean()
{
	SDL_FreeSurface(Screen);
	SDL_FreeSurface(Background);
	SDL_FreeSurface(Message);
	SDL_FreeSurface(MessageEnter);
	SDL_FreeSurface(RectAmountMessage);
	TTF_CloseFont(Font);
	SDL_Quit();
	TTF_Quit();
}

