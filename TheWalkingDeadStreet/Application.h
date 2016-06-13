#pragma once

#include "Tourelle.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm> 
#include <string>
#include <map>
#include <cmath>

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

	map<int, vector<int>> computeIncompatibilities(unsigned dist);

private:
	FILE applicationFile;
	int nombreDeTtireur;
	int nombreDeTours;
	vector<Tourelle> tourelles;
	
};

