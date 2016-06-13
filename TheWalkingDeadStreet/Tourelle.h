#pragma once

#include <string>

using namespace std;

class Tourelle
{
public:
	Tourelle(int distance, int estimation, int position);
	~Tourelle();
	int getDistance() { return this->distance; }
	int getEstimation() { return this->estimation; }
	int getPosition() { return this->position; }

	string toString();

private:
	int distance;
	int estimation;
	int position;
};

