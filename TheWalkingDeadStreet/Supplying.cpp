#include "stdafx.h"
#include "Supplying.h"


Supplying::Supplying(string file)
{
	string line;
	ifstream streetFile(file);
	this->delimiter = " ";
	if (streetFile.is_open())
	{
		int emplacement = 1;

		getCities(streetFile);

		streetFile.close();
	}
	else {
		cout << "file not open";
	}
}

void Supplying::getCities(ifstream &file) {
	string line;
	while (getline(file, line))
	{
		size_t pos = 0;
		string position;
		string token;

		pos = line.find(delimiter);
		position = line.substr(0, pos);
		line.erase(0, pos + delimiter.length());

		pos = line.find(delimiter);
		token = line.substr(0, pos);
		line.erase(0, pos + delimiter.length());

		City city(stoi(position, nullptr, 10), stof(token), stof(line));

		this->cities.push_back(city);
	}
}

void Supplying::printCities()
{
	for (vector<City>::iterator it = this->cities.begin(); it != this->cities.end(); ++it) {
		cout << it->toString() << endl;
	}
}

void Supplying::printPath()
{
	for (vector<vector<Distance>>::iterator it = this->distance.begin(); it != this->distance.end(); ++it) {
		for (vector<Distance>::iterator ite = it->begin(); ite != it->end(); ++ite) {
			cout << ite->path << " ";
		}
		cout << endl;
	}
}

void Supplying::printDistance()
{
	for (vector<vector<Distance>>::iterator it = this->distance.begin(); it != this->distance.end(); ++it) {
		for (vector<Distance>::iterator ite = it->begin(); ite != it->end(); ++ite) {
			cout << ite->dist << " ";
		}
		cout << endl;
	}
}

void Supplying::calculDistance()
{
	this->distance.resize(this->cities.size(), vector<Distance>(this->cities.size()));
	for (int i = 0; i < (int)this->cities.size(); i++)
	{
		for (int j = 0; j < (int)this->cities.size(); j++)
		{
			if (i == j)
			{
				this->distance[i][j].dist = 0;
				this->distance[i][j].path = this->cities[j].getNode();
			}
			else
			{
				double distanceX = (this->cities[i].getXCoord() - this->cities[j].getXCoord());
				double distanceY = (this->cities[i].getYCoord() - this->cities[j].getYCoord());
				this->distance[i][j].dist = sqrt((distanceX*distanceX) + (distanceY*distanceY));
				this->distance[i][j].path = this->cities[j].getNode();
			}
		}
	}
}

void Supplying::sortDistance()
{
	for (vector<vector<Distance>>::iterator it = this->distance.begin(); it != this->distance.end(); ++it) {
		sort(it->begin(), it->end(), [](Distance const &a, Distance const &b) {
			return a.dist < b.dist; });
	}
}

Path Supplying::findNeighbour(int city)
{
	Path bestPath;
	const int cityCount = this->cities.size();
	double length = 0;
	bool *visited = new (nothrow) bool[this->cities.size()]();
	fill_n(visited, cityCount, false);
	int *path = new (nothrow) int[this->cities.size()]();

	int cityInit = city;

	bool finished = false;
	int indexAway = 0;
	path[indexAway] = city;
	while (!finished)
	{
		finished = true;
		for (int i = 1; i < cityCount; i++)
		{
			if (!visited[this->distance[city - 1][i].path])
			{
				finished = false;
				length += this->distance[city - 1][i].dist;
				visited[city] = true;
				city = this->distance[city - 1][i].path;
				indexAway++;
				path[indexAway] = city;
				break;
			}
		}
	}

	bestPath.lenght = length;
	bestPath.path = path;

	delete visited;

	return bestPath;
}

void Supplying::findBestPath()
{
	vector<Path> path;
	calculDistance();
	sortDistance();

	for (int i = 1; i < this->cities.size()-1; i++) {
		path.push_back(findNeighbour(i));
	}

	sort(path.begin(), path.end(), [](Path &a, Path &b) {
		return a.lenght < b.lenght;
	});

	cout << "Best path : " << path.begin()->lenght << endl;
	for (int i = 0; i < this->cities.size(); ++i) {
		if (i != this->cities.size()-1) {
			cout << path.begin()->path[i] << " -> ";
		}
		else {
			cout << path.begin()->path[i] << endl;
		}		
	}
}

Supplying::~Supplying()
{
}
