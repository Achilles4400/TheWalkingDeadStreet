#include "stdafx.h"
#include "City.h"


City::City(int node, float xCoord, float yCoord)
{
	this->node = node;
	this->xCoord = xCoord;
	this->yCoord = yCoord;
}

City::~City()
{
}

string City::toString()
{
	return  "position: " + to_string(this->node) + " XCoord: " + to_string(this->xCoord) + " YCoord: " + to_string(this->yCoord);
}
