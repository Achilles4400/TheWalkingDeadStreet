#pragma once

#include <string>

using namespace std;

class City
{
public:
	City(int node, float xCoord, float yCoord);
	~City();
	float getXCoord() { return xCoord; }
	float getYCoord() { return yCoord; }
	int getNode() { return node; }

	string toString();

private:
	int node;
	float xCoord;
	float yCoord;
};

