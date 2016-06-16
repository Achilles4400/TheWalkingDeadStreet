#pragma once

#include "Tourelle.h"
#include "utils.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm> 
#include <string>
#include <map>
#include <cmath>
#include <time.h>
#include <list>

using namespace std;

class Application
{
public:
	Application(string file);
	~Application();

	void showTourelles();
	void sortTourellesByEst();
	void sortTourellesByDist();
	void maximiseWalkerKilled();
	void maximiseWalkerKilledDistConstraint(unsigned dist);
	void maximiseWalkerKilledWeatherConstraint(unsigned dist);

	map<int, vector<int>> computeIncompatibilities(unsigned dist);

private:
	FILE applicationFile;
	int nombreDeTtireur;
	int nombreDeTours;
	vector<Tourelle> tourelles;
	
};

