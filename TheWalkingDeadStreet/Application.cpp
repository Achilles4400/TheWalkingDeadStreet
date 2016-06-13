#include "stdafx.h"
#include "Application.h"

using namespace std;

//utils, à mettre dans un autre fichier plus tard
bool Sort_by_est(Tourelle& a, Tourelle& b)
{
	return a.getEstimation() < b.getEstimation();
}

bool Sort_by_dist(Tourelle& a, Tourelle& b)
{
	return a.getDistance() < b.getDistance();
}

bool isCompatible(vector<int> shooterPosition, vector<int> tower) {
	if (shooterPosition.size() != NULL) {
		for (vector<int>::iterator shooter = shooterPosition.begin(); shooter != shooterPosition.end(); ++shooter) {
			for (vector<int>::iterator place = tower.begin(); place != tower.end(); ++place) {
				if (*shooter == *place) {
					return false;
				}
			}
		}
	}
	return true;
}

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

		string delimiter = "	";

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
	sort(this->tourelles.rbegin(), this->tourelles.rend(), Sort_by_est);
}

void Application::sortTourellesByDist()
{
	sort(this->tourelles.rbegin(), this->tourelles.rend(), Sort_by_dist);
}

void Application::maximiseWalkerKilled()
{
	sortTourellesByEst();
	for (vector<Tourelle>::iterator it = this->tourelles.begin(); it != this->tourelles.begin() + this->nombreDeTtireur; ++it)
		cout << it->toString() << endl;
}

void Application::maximiseWalkerKilledDistConstraint(unsigned dist)
{
	vector<int> shooterPosition;
	int shooterPlaced = 0;
	map<int, vector<int>> incompatibilities = computeIncompatibilities(dist);

	sortTourellesByEst();
	for (vector<Tourelle>::iterator it = this->tourelles.begin(); it != this->tourelles.end(); ++it) {
		if (isCompatible(shooterPosition, incompatibilities.at(it->getPosition()))) {
			if (shooterPlaced < this->nombreDeTtireur) {
				shooterPosition.push_back(it->getPosition());
				shooterPlaced++;
			}
			
		}
	}

	for (vector<int>::const_iterator it = shooterPosition.begin(); it != shooterPosition.end(); ++it)
		cout << to_string(*it) << endl;
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
		incompatibilities.insert(pair<int,vector<int>>(position, incompatible));
	}
	return incompatibilities;
}
