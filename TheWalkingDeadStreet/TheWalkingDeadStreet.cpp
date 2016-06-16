// TheWalkingDeadStreet.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"

using namespace std;

string config_vincent = "C:\\Users\\vince\\Documents\\Algo\\Devoir_ 2\\Fichiers_test\\T_4_20.txt";
string config_kevin = "C:\\Users\\Kevin\\Downloads\\devoir2\\devoir\\test\\T_4_20.txt";

int main()
{
	int distConstraint = 5;
	std::string test = config_kevin;
	cout << test << endl;

	Application myTest(test);

	//myTest.maximiseWalkerKilled();
	//myTest.maximiseWalkerKilledDistConstraint(distConstraint);
	//myTest.maximiseWalkerKilledWeatherConstraint(distConstraint);

	/*RSA rsa;
	Key key = rsa.generateKeys();
	long msg;
	cout << "entrez le message ：" << endl;
	cin >> msg;
	long msg_des = rsa.encrypt(msg, key.eKey, key.primeKey);
	cout << "message crypté ：" << msg_des << endl;
	msg_des = rsa.encrypt(msg_des, key.modKey, key.primeKey);
	cout << "message original ：" << msg_des << endl;*/
	return 0;
}
