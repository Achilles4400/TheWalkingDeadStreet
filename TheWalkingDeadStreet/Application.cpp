#include "stdafx.h"
#include "Application.h"

using namespace std;


Application::Application(string file)
{
	string line;
	ifstream streetFile(file);
	this->delimiter = "\t";
	if (streetFile.is_open())
	{
		int emplacement = 1;

		getShootersAndTourelleNumber(streetFile);

		getTourelles(streetFile);
	}
	else {
		cout << "file not open";
	}
}


void Application::getShootersAndTourelleNumber(ifstream &file) {
	string line;
	getline(file, line);
	nombreDeTtireur = stoi(line, nullptr, 10);

	getline(file, line);
	nombreDeTours = stoi(line, nullptr, 10);
}


void Application::getTourelles(ifstream &file) {
	string line;
	int emplacement = 1;
	while (getline(file, line))
	{
		size_t pos = 0;
		string token;

		pos = line.find(delimiter);
		token = line.substr(0, pos);
		line.erase(0, pos + delimiter.length());

		Tourelle tourelle(stoi(token, nullptr, 10), stoi(line, nullptr, 10), emplacement);

		this->tourelles.push_back(tourelle);

		emplacement++;
	}
	file.close();
}


Application::~Application()
{
}


void Application::showTourelles()
{
	for (vector<Tourelle>::iterator it = this->tourelles.begin(); it != this->tourelles.end(); ++it)
		cout << it->toString() << endl;
}


void Application::sortTourellesByEst()
{
	sort(this->tourelles.rbegin(), this->tourelles.rend(), utils::Sort_by_est);
}


void Application::sortTourellesByDist()
{
	sort(this->tourelles.begin(), this->tourelles.end(), utils::Sort_by_dist);
}


void Application::maximiseWalkerKilled()
{
	sortTourellesByEst();
	for (vector<Tourelle>::iterator it = this->tourelles.begin(); it != this->tourelles.begin() + this->nombreDeTtireur; ++it)
		cout << it->toString() << endl;
}


vector<Tourelle> Application::maximiseWalkerKilledDistConstraint(unsigned dist)
{
	vector<Tourelle> shooterPosition;
	int shooterPlaced = 0;
	map<int, vector<int>> incompatibilities = computeIncompatibilities(dist);

	sortTourellesByEst();

	for (vector<Tourelle>::iterator it = this->tourelles.begin(); it != this->tourelles.end(); ++it) {
		if (utils::isCompatible(shooterPosition, incompatibilities.at(it->getPosition())) && shooterPlaced < this->nombreDeTtireur) {
				shooterPosition.push_back(*it);
				shooterPlaced++;
		}
	}
	return shooterPosition;
}


int initWeather() {
	srand(time(NULL));
	return (rand() % 31) - 15;
}


vector<Tourelle> getAdjacentTower(vector<Tourelle> tourelles, int position) {
	vector<Tourelle> adjacent;
	for (vector<Tourelle>::iterator it = tourelles.begin(); it != tourelles.end(); ++it) {
		if (it->getPosition() == position + 1 || it->getPosition() == position - 1) {
			adjacent.push_back(*it);
		}
	}
	return adjacent;
}


Tourelle Application::findBestEstimationTourelle(vector<Tourelle> tourelleVector, int *tourelleIndex) {
	Tourelle highestTourelle;
	int i = 0;
	for (vector<Tourelle>::iterator it = tourelleVector.begin(); it != tourelleVector.end(); ++it) {
		if (it->getEstimation() > highestTourelle.getEstimation()){
			highestTourelle = *it;
			*tourelleIndex = i;
		}
		i++;
	}
	return highestTourelle;
}


vector<Tourelle> Application::maximiseWalkerKilledWeatherConstraint(unsigned dist)
{

	int weather = initWeather();

	sortTourellesByDist();
	vector<Tourelle> tmpTourelles = this->tourelles;

	int shooterPlaced = 0;
	int tourelleIndex = 0;
	vector<Tourelle> result;

	while (shooterPlaced < this->nombreDeTtireur) {
		Tourelle tourelle = findBestEstimationTourelle(tmpTourelles, &tourelleIndex);
		if (isDistRespected(tourelle, result, dist)) {
			tmpTourelles[tourelleIndex].setEstimationAfterWeather(tmpTourelles[tourelleIndex].getEstimation() * (100 - abs(initWeather())) / 100);
			tourelle.setEstimationAfterWeather(tourelle.getEstimation() * (100 - abs(initWeather())) / 100);
			if (weather >= 0) {
				if (tourelleIndex + 1 == tmpTourelles[tourelleIndex + 1].getPosition()) {
					tmpTourelles[tourelleIndex + 1].setEstimationAfterWeather(tmpTourelles[tourelleIndex + 1].getEstimation());
				}
				if (tourelleIndex - 1 == tmpTourelles[tourelleIndex - 1].getPosition())
					tmpTourelles[tourelleIndex - 1].setEstimationAfterWeather(tmpTourelles[tourelleIndex - 1].getEstimation() * (100 - abs(initWeather())) / 100);
					
			}
			else {
				if (tourelleIndex + 1 == tmpTourelles[tourelleIndex + 1].getPosition())
					tmpTourelles[tourelle.getPosition() + 1].setEstimationAfterWeather(tmpTourelles[tourelle.getPosition() + 1].getEstimation() * (100 + abs(initWeather())) / 100);
				if (tourelleIndex - 1 == tmpTourelles[tourelleIndex - 1].getPosition())
					tmpTourelles[tourelleIndex - 1].setEstimationAfterWeather(tmpTourelles[tourelleIndex - 1].getEstimation() * (100 + abs(initWeather())) / 100);
			}
			result.push_back(tourelle);
			shooterPlaced++;
		}
		tmpTourelles.erase(tmpTourelles.begin() + tourelleIndex);
	}

	return result;
}

void Application::shooterSimulationPerHour(unsigned dist) {
	vector<Tourelle> shooterPlace = maximiseWalkerKilledWeatherConstraint(dist);
	vector<Tourelle> tmpTourelles = this->tourelles;
	sortTourellesByDist();
	for(int i = 0; i < 10; i++){
		
		for (int j = 0; j < shooterPlace.size(); j++) {
			int newWeather = initWeather();
			if (newWeather < 0) {
				int newEstimation = (((shooterPlace[j].getEstimation()) * (100 - abs(newWeather))) / 100);
				int estimationAfterWeather = shooterPlace[j].getEstimationAfterWeather();
				int estimation = shooterPlace[j].getEstimation();
				if ((shooterPlace[j].getEstimationAfterWeather()) < (((shooterPlace[j].getEstimation()) * (100 - abs(newWeather))) / 100)) {
					cout << "heure " << i + 1 << " : le tireur qui est sur la tour " << j + 1 << " change de place " << endl;
				}
			}
			else {
				Tourelle tourelle = tmpTourelles[shooterPlace[j].getPosition() - 1];
				int newEstimation = ((shooterPlace[j].getEstimation()) * ((100 + abs(newWeather))) / 100);
				int estimationAfterWeather = shooterPlace[j].getEstimationAfterWeather();
				int estimation = shooterPlace[j].getEstimation();
				if ((shooterPlace[j].getEstimationAfterWeather()) < ((shooterPlace[j].getEstimation()) * ((100 + abs(newWeather))) / 100)) {
					cout << "heure " << i + 1 << " : le tireur qui est sur la tour " << j + 1 << " change de place " << endl;
				}
			}
		}
	}
}

void printTourelles(vector<Tourelle> tourelles) {
	for (vector<Tourelle>::iterator it = tourelles.begin(); it != tourelles.end(); ++it)
		cout << it->toString() << endl;
}

bool Application::isDistRespected(Tourelle tourelle, vector<Tourelle> tourelles, unsigned dist) {
	for (vector<Tourelle>::iterator it = tourelles.begin(); it != tourelles.end(); ++it) {
		if (abs(it->getDistance() - tourelle.getDistance()) < dist)
			return false;
	}
	return true;
}


map<int, vector<int>> Application::computeIncompatibilities(unsigned dist)
{
	int position;
	map<int, vector<int>> incompatibilities;

	sortTourellesByDist();

	for (vector<Tourelle>::iterator value = this->tourelles.begin(); value != this->tourelles.end(); ++value) {
		position = value->getPosition();
		incompatibilities.insert(pair<int, vector<int>>(position, lookForIncompatibility(value, position, dist)));
	}
	return incompatibilities;
}


vector<int> Application::lookForIncompatibility(vector<Tourelle>::iterator &value, int position, unsigned dist) {
	vector<int> incompatible;
	for (vector<Tourelle>::iterator it = this->tourelles.begin(); it != this->tourelles.end(); ++it) {
		if (it->getPosition() != position && abs(value->getDistance() - it->getDistance()) <= dist) {
			incompatible.push_back(it->getPosition());
		}
	}
	return incompatible;
}