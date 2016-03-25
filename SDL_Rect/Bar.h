//Name:		Brandon Shaw
//File:		Bar.h
//Scope:	Declaration of the Bar node class


#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <string>
#include "SDL\SDL.h"

class Bar
{
public:
	Bar();
	Bar(std::string name, unsigned short int height, unsigned short int width);

	friend class BarList;
	friend class GameEvents;
	friend std::istream& operator>> (std::istream& is, Bar& rect);

private:
	SDL_Rect Column;
	Bar* Next;
	std::string Name;
	short unsigned int Velocity;
	bool Transformed;

};

#endif

