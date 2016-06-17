#pragma once

#include <string>

using namespace std;

class Vigenere
{
public:
	Vigenere();
	~Vigenere();

	static string encryption(string msg, string key);
	static string decryption(string msg, string key);

private:
	static const int alphabet_length = 26;
	
};

