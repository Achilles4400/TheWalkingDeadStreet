// TheWalkingDeadStreet.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"

using namespace std;

int main()
{
	int distConstraint = 5;
	std::string test = "C:\\Users\\vince\\Documents\\Algo\\Devoir_ 2\\Fichiers_test\\T_4_20.txt";
	cout << test << endl;

	Application myTest(test);

	//myTest.maximiseWalkerKilled();
	myTest.maximiseWalkerKilledDistConstraint(distConstraint);
	
    return 0;
}
