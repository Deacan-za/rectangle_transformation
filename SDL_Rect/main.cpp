//Name:		Brandon Shaw
//File:		main.cpp
//Scope:	Entry point for the program
//			Controls the creation/deletion of all ojects
//			Contains main game loops.


#include <sdl.h>
#include <time.h>
#include <Windows.h>
#include <fstream>
#include <cstring>
#include <iostream>
#include <vector>
#include "GameEvents.h"
#include "BarList.h"

//Function Declaration:
unsigned short int randomNum(unsigned short int range, bool isthiswidth);
std::vector<std::string> splitString(std::string input, std::string delimiter);

int main( int argc, char* args[] )
{
	//initialize random seed:
	srand ((unsigned)time(NULL));

	//Create instances of the gameEvents object and output file:
	GameEvents *GE = new GameEvents();
	BarList *BL = new BarList();
	BarList *TransformedList = new BarList();
	std::ofstream outputFile ("InitialRectangles.txt");
	

	//Initialize Game object:
	if(GE->gameInit() == false)
	{
		std::cerr << "Failed to load screen surface or font." << std::endl;
		return 1;
	}

	//Load the files:
	if(GE->gameLoad() == false)
	{
		return 1;
	}

	/*For the Title screen
	checks the the StartTitle bool is true
	While its true the the Title screen shows*/
	while(GE->get_TitleState())
	{
		//Check to ensure user input is between specified range:
		bool inputCorrect = GE->get_UserIputCheck();
		if(inputCorrect)
		{
			//Draw the defualt Text on screen:
			GE->gameDrawText(TILTETEXT);
		}
		else
		{
			//Draw the error Text on screen:
			GE->gameDrawText(ERRORTEXT);
		}
		//Checks for and event. If event = enter games starts.
		GE->gameStart();

		//Refresh the screen:
		GE->gameFlip();
	}

	//Text file written with Bar name (1 - n), bar height and width.
	//This file will be used to read in the rectabgle dimensions 
	//to be displayed on the screen.
	for(int i = 0; i < GE->get_RectNum(); i++)
	{
		if(outputFile.is_open())
		{
			outputFile << "Bar:" << i + 1 << " " << "h:" << randomNum((SCREEN_HEIGHT / 2 ) - 50, false) << " " <<"w:" << randomNum(SCREEN_WIDTH - 100 , true) << std::endl;
		}
		else
		{
			std::cerr << "Error opening InitialRectangles.txt";
			exit(1);
		}
	}
	//Files has been written to. 
	outputFile.close();

	//Open the written file to read in as input to create the list of all columns:
	std::ifstream inputFile;
	inputFile.open("InitialRectangles.txt");
	
	if(inputFile.is_open())
	{
		std::string word = "";
		std::string output = "";

		//Loops through file uptill there is no more input:
		while(std::getline(inputFile,output))
		{
			//Each line received from the input file is sent to the splitString Function.
			//This returns a vector consisting of all parts of the original string.
			//Two of the results are passed back into splitString in order to get the 
			//height and width vlaues which are converted from strings to ints:
			std::vector<std::string> vecString = splitString(output," ");
			std::vector<std::string> vecHeight = splitString(vecString[1],":");
			unsigned short int height = std::atoi(vecHeight[1].c_str());

			std::vector<std::string> vecWidth = splitString(vecString[2],":");
			unsigned short int width = std::atoi(vecWidth[1].c_str());

			//All accumulated info is add to Bar object and to the BarList BL:
			BL->addToTail(vecString[0], height, width);
			vecString.clear();
			vecHeight.clear();
			vecWidth.clear();
		}
	}
	inputFile.close();
	
	//Clearing the screen of the starting text:
	SDL_FillRect(GE->get_Screen(), NULL, 0x000000);

	//Call to the function that draws the columns.
	//This function takes two parameters -  The Barlist object and
	//a boolean value use to alternate the output colors:
	GE->gameDrawCol(BL, true);

	//Function responsible for the transformation of the bars
	//Accepts the original list that will be used to create the new bars.
	//At this point the TransformedList is empty.
	GE->gameTransform(BL, TransformedList);
	
	//Call to the function that draws the transformed columns.
	//This function takes two parameters - the Barlist object,
	//a boolean value use to alternate the output colors:
	GE->gameDrawCol(TransformedList, false);
	
	//Write the Transformed list to an output file:
	GE->writeFile(TransformedList);

	//Refreshing the screen to display columns:
	GE->gameFlip();

	//This look checks for a Quit state from the user to end the program:
	while(GE->get_runningState())
	{
		//check for Exit:
		GE->gameExit();
	}

	//Closing and free memory allocated for SDL, font and all objects created:
	GE->gameClean();
	delete GE;
	delete BL;
	delete TransformedList;
	return 0;
}


//Function Definition:
//Function to create random height and width values.
//This function takes to parameters - an int range and a bool.
//Range - specified on the screen size plus a buffer value to create space at the top and bottom.
//Bool - to check if the requested return is for width, width has a control factor to ensure 
//ridiculous widths are not created.
unsigned short int randomNum(unsigned short int range, bool isthiswidth)
{
	unsigned short int temp;
	if(isthiswidth)
	{
		do
		{
			temp = rand() % range;
		}while(temp > 50 || temp < 10); //Ensure the the column width is not to big or to small.
	}else
	{
		return rand() % range;
	}
}

 std::vector<std::string> splitString(std::string input, std::string delimiter)
  {
     std::vector<std::string> output;
     size_t start = 0;
     size_t end = 0;
  
     while (start != std::string::npos && end != std::string::npos)
     {
        start = input.find_first_not_of(delimiter, end);
  
        if (start != std::string::npos)
        {
           end = input.find_first_of(delimiter, start);
  
           if (end != std::string::npos)
           {
              output.push_back(input.substr(start, end - start));
           }
           else
           {
              output.push_back(input.substr(start));
           }
        }
     }
  
     return output;
  
  }
  
