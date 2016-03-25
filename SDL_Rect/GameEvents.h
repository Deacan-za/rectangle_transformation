

#ifndef GAMEEVENTS_H
#define GAMEEVENTS_H

#include "SDL\SDL.h"
#include "SDL\SDL_ttf.h"
#include "Constants.h"
#include "SDL\SDL_image.h"
#include <string>

class BarList;

class GameEvents
{
public:
	GameEvents();
	~GameEvents();

	bool gameInit();
	bool gameLoad();
	bool get_TitleState();
	bool gameFlip();
	bool get_UserIputCheck();
	bool get_runningState();
	
	void validateInput(std::string numofrects);
	void gameStart();
	void gameExit();
	void gameDraw(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);
	void gameDrawCol(BarList* BList, bool colorSwop);
	void gameTransform(BarList* BList, BarList* drawList);
	void writeFile(BarList* drawList);
	void gameClean();

	
	unsigned short int gameDrawText(std::string text);
	unsigned short int get_RectNum();

	SDL_Surface* load_Image(std::string filename);
	SDL_Surface* get_Screen();

private:
	SDL_Surface* Background;
	SDL_Surface* Screen;
	SDL_Surface* Message;
	SDL_Surface* MessageEnter;
	SDL_Surface* RectAmountMessage;
	TTF_Font* Font;
	bool StartTitle;
	bool UserInputCheck;
	bool GameRunning;
	std::string NumofRects;
};

#endif