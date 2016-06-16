#include "stdafx.h"
#include "Application.h"

using namespace std;

Application::Application(string file)
{
	string line;
	ifstream streetFile(file);
	if (streetFile.is_open())
	{
		int emplacement = 1;

		getline(streetFile, line);
		nombreDeTtireur = stoi(line, nullptr, 10);

		getline(streetFile, line);
		nombreDeTours = stoi(line, nullptr, 10);

		string delimiter = "\t";

		while (getline(streetFile, line))
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
		streetFile.close();
	}
	else {
		cout << "file not open";
	}
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
	sort(this->tourelles.rbegin(), this->tourelles.rend(), utils::Sort_by_dist);
}

void Application::maximiseWalkerKilled()
{
	sortTourellesByEst();
	for (vector<Tourelle>::iterator it = this->tourelles.begin(); it != this->tourelles.begin() + this->nombreDeTtireur; ++it)
		cout << it->toString() << endl;
}

void Application::maximiseWalkerKilledDistConstraint(unsigned dist)
{
	vector<Tourelle> shooterPosition;
	int shooterPlaced = 0;
	map<int, vector<int>> incompatibilities = computeIncompatibilities(dist);

	sortTourellesByEst();
	for (vector<Tourelle>::iterator it = this->tourelles.begin(); it != this->tourelles.end(); ++it) {
		if (utils::isCompatible(shooterPosition, incompatibilities.at(it->getPosition()))) {
			if (shooterPlaced < this->nombreDeTtireur) {
				shooterPosition.push_back(*it);
				shooterPlaced++;
			}
		}
	}

	for (vector<Tourelle>::iterator it = shooterPosition.begin(); it != shooterPosition.end(); ++it)
		cout << it->toString() << endl;
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

void Application::maximiseWalkerKilledWeatherConstraint(unsigned dist)
{
	int weather = initWeather();
	vector<Tourelle> adjacent;
	vector<Tourelle> shooterPosition;
	int shooterPlaced = 0;
	map<int, vector<int>> incompatibilities = computeIncompatibilities(dist);

	sortTourellesByEst();
	for (vector<Tourelle>::iterator it = this->tourelles.begin(); it != this->tourelles.end(); ++it) {
		if (utils::isCompatible(shooterPosition, incompatibilities.at(it->getPosition()))) {
			if (shooterPlaced < this->nombreDeTtireur) {
				shooterPosition.push_back(*it);
				shooterPlaced++;
			}
		}
	}
	for (vector<Tourelle>::iterator it = shooterPosition.begin(); it != shooterPosition.end(); ++it) {
		if (it != shooterPosition.begin()) {
			adjacent = getAdjacentTower(this->tourelles, it->getPosition());
			it->setEstimation(it->getEstimation() + it->getEstimation() * weather);
		}
		else {
			if (weather < 0) {
				for (vector<Tourelle>::iterator adja = adjacent.begin(); adja != adjacent.end(); ++adja) {

				}
			}
			adjacent = getAdjacentTower(this->tourelles, it->getPosition());
		}
	}
	for (vector<Tourelle>::iterator it = shooterPosition.begin(); it != shooterPosition.end(); ++it)
		cout << it->toString() << endl;
}

map<int, vector<int>> Application::computeIncompatibilities(unsigned dist)
{
	int position;
	map<int, vector<int>> incompatibilities;

	sortTourellesByDist();
	for (vector<Tourelle>::iterator value = this->tourelles.begin(); value != this->tourelles.end(); ++value) {
		position = value->getPosition();
		vector<int> incompatible;
		for (vector<Tourelle>::iterator it = this->tourelles.begin(); it != this->tourelles.end(); ++it) {
			if (it->getPosition() != position) {
				if (abs(value->getDistance() - it->getDistance()) <= dist) {
					incompatible.push_back(it->getPosition());
				}
			}
		}
		incompatibilities.insert(pair<int, vector<int>>(position, incompatible));
	}
	return incompatibilities;
}