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
	vector<Tourelle> maximiseWalkerKilledDistConstraint(unsigned dist);
	void maximiseWalkerKilledWeatherConstraint(unsigned dist);
	void getTourelles(ifstream &file);
	void getShootersAndTourelleNumber(ifstream &file);
	vector<int> lookForIncompatibility(vector<Tourelle>::iterator &it, int position, unsigned dist);
	Tourelle findBestEstimationTourelle(vector<Tourelle> tourelleVector, int *tourelleIndex);
	bool isDistRespected(Tourelle tourelle, vector<Tourelle> tourelles, unsigned dist);

	map<int, vector<int>> computeIncompatibilities(unsigned dist);

private:
	FILE applicationFile;
	int nombreDeTtireur;
	int nombreDeTours;
	vector<Tourelle> tourelles;
	string delimiter;
	
};

void printVector(vector<Tourelle> vector);
