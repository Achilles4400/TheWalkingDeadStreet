// TheWalkingDeadStreet.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"

using namespace std;

string config_vincent = "C:\\Users\\vince\\Documents\\Algo\\Devoir_ 2\\Fichiers_test\\T_4_20.txt";
string config_vincent_cities = "C:\\Users\\vince\\Documents\\Algo\\Devoir_ 2\\Fichiers_test\\ville.txt";
string config_kevin = "C:\\Users\\Kevin\\Downloads\\devoir2\\devoir\\test\\T_4_20.txt";

int main()
{
	int distConstraint = 5;

	string msg = "ceci est un test de vigenere";
	string key = "boearty";

	string test = config_vincent;
	string citiesTest = config_vincent_cities;
	cout << citiesTest << endl;

	Application myTest(test);

	//myTest.maximiseWalkerKilled();
	//myTest.maximiseWalkerKilledDistConstraint(distConstraint);
	//myTest.maximiseWalkerKilledWeatherConstraint(distConstraint);

	Supplying supplying(citiesTest);
	supplying.calculDistance();
	//supplying.printPath();
	//supplying.sortDistance();
	//supplying.printDistance();
	//supplying.printCities();
	supplying.findBestPath();

	/*
	cout << msg << endl;
	string encrypt = Vigenere::encryption(msg, key);
	cout << encrypt << endl;
	string decrypt = Vigenere::decryption(encrypt, key);
	cout << decrypt << endl;
	*/

	return 0;
}
