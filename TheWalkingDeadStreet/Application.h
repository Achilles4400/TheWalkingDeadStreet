#pragma once

#include "Tourelle.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class Application
{
public:
	Application(string file);
	~Application();

	static void setupData(string file);

private:
	FILE applicationFile;
	int nombreDeTtireur;
	int nombreDeTours;
	vector<Tourelle> tourelles;
	
};

