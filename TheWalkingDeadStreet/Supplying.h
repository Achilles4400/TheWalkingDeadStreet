#pragma once

#include "City.h"

#include <string>

using namespace std;

typedef struct
{
	int lenght;
	int * path;
}Path;

typedef struct
{
	int path;
	float dist;
} Distance;

class Supplying
{
public:
	Supplying(string file);
	~Supplying();

	void getCities(ifstream &file);
	void printCities();
	void printPath();
	void printDistance();

	void calculDistance();
	void sortDistance();

	Path findNeighbour(int city);
	void findBestPath();

private:
	vector<vector<Distance>> distance;

	vector<City> cities;
	string delimiter;
};

