//Name:		Brandon Shaw
//File:		BarList.cpp
//Scope:	Definition of the BarList classs

#include "BarList.h"
#include "Bar.h"

//Default constructor
BarList::BarList()
{
	Head = nullptr;
	Tail = nullptr;
	TotalWidthinList = 0;
	Count = 0;
}

//Adds each new Bar node to the tail of the list
//This method is used when creating the original list. When the input valuses
//are read from the file.
void BarList::addToTail(std::string name, unsigned short int height, unsigned short int width)
{
	Bar* newone = new Bar(name, height, width);

	if(Head == nullptr)
	{
		newone->Column.y = newone->Column.y - newone->Column.h;
		Head = newone;
		Tail = newone;
		Count++;
	}
	else
	{
		newone->Column.x = Tail->Column.x + Tail->Column.w;
		newone->Column.y = newone->Column.y - newone->Column.h;
		Tail->Next = newone;
		Tail = newone;
		Count++;
	}
	TotalWidthinList += newone->Column.w;
}

//Adds each new Bar node to the tail of the list
//This method is used within the gameTransform when adding the smallest column to the transformed list.
//This also accepts an int value used to start the second bar chart below the first.
void BarList::addToTail(Bar* item, int baseLineCount)
{
	Bar* newone = new Bar(item->Name, item->Column.h, item->Column.w);

	if(Head == nullptr)
	{
		newone->Column.y = item->Column.y + baseLineCount;
		newone->Column.x = item->Column.x;
		Head = newone;
		Tail = newone;
		Count++;
	}
	else
	{
		newone->Column.y = item->Column.y + baseLineCount;
		newone->Column.x = item->Column.x;
		Tail->Next = newone;
		Tail = newone;
		Count++;
	}
}

//Adds each new Bar node to the tail of the list
//This method is used within the gameTransform method when adding to the left/right lists
void BarList::addToTail(Bar* item)
{
	Bar* newone = new Bar(item->Name, item->Column.h, item->Column.w);

	if(Head == nullptr)
	{
		newone->Column.y = item->Column.y;
		newone->Column.x = item->Column.x;
		Head = newone;
		Tail = newone;
		Count++;
	}
	else
	{
		newone->Column.y = item->Column.y;
		newone->Column.x = item->Column.x;
		Tail->Next = newone;
		Tail = newone;
		Count++;
	}
}

//This method is responsible for deleting the smallest colum from the original list.
//A pointer to the smallest colum is passed into the method.
//A transversal pointer is created and used to step through the list.
//When the item passed in is equal to the transversal point, that item is deleted.
void BarList::deleteNoid(Bar* item)
{
	Bar* tp = Head;
	Bar* trail = Head;

	while(tp != nullptr)
	{
		if(tp == item)
		{
			//Case 1: Delete from head:
			if (Head == tp)
			{
				tp = Head->Next;
				delete Head;
				Head = tp;;
				Count--;
			}
			//Case 2: Delete within the list:
			else
			{
				trail->Next = tp->Next;
				delete tp;
				tp = trail->Next;
				Count--;
			}
		}
		else
		{
			//Push the pointers along the list:
			trail = tp;
			tp = tp->Next;
		}
	}
}

//Method used to return the total width of all items in the list.
unsigned short int BarList::get_totalWidth()
{
	return TotalWidthinList;
}

