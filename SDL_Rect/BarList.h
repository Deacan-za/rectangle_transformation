//Name:		Brandon Shaw
//File:		Barlist/h
//Scope:	Declaration of the list object for the columns

#ifndef RECTLIST_H
#define RECTLIST_H
#include <fstream>
class Bar;


class BarList
{
public:
	BarList();
	void addToTail(std::string name, unsigned short int height, unsigned short int width);
	void addToTail(Bar* item, int baseLineCount);
	void addToTail(Bar* item);
	void deleteNoid(Bar* item);
	unsigned short int get_totalWidth();
	friend class GameEvents;
	

private:
	Bar* Head;
	Bar* Tail;
	unsigned short int TotalWidthinList;
	unsigned short int Count;
};


#endif