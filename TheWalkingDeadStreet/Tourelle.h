#pragma once

#include <string>

using namespace std;

class Tourelle
{
public:
	Tourelle(int distance, int estimation, int position);
	Tourelle();
	~Tourelle();
	int getDistance() { return this->distance; }
	int getEstimation() { return this->estimation; }
	int getPosition() { return this->position; }
	void setEstimation(int estimation) { this->estimation = estimation; }
	void setEstimationAfterWeather(int estimantionAfterWeather) { this->estimationAfterWeather = estimantionAfterWeather;  }
	int getEstimationAfterWeather() { return this->estimationAfterWeather; }

	string toString();

private:
	int distance;
	int estimation;
	int position;
	int estimationAfterWeather;
};