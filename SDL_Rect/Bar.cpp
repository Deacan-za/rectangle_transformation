//Name:		Brandon Shaw
//File:		Bar.h
//Scope:	Declaration of the Bar node class

#include "Bar.h"
#include <sstream>

//Default constructor:
Bar::Bar()
{
	Column.x = 20;
	Column.y = 400;
	Column.h = 0;
	Column.w = 0;
	Velocity = 0;
	Transformed = false;
	Name = " ";
	Next = nullptr;
}

//Overloaded constructor:
Bar::Bar(std::string name, unsigned short int height, unsigned short int width)
{
	Column.x = 20;
	Column.y = 400;
	Column.h = height;
	Column.w = width;
	Velocity = 0;
	Transformed = false;
	Name = name;
	Next = nullptr;
}



