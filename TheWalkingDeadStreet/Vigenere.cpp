#include "stdafx.h"
#include "Vigenere.h"

const string alphabet = "abcdefghijklmnopqrstuvwxyz";

Vigenere::Vigenere()
{
}


Vigenere::~Vigenere()
{
}

string Vigenere::encryption(string msg, string key)
{
	std::transform(msg.begin(), msg.end(), msg.begin(), ::toupper);
	std::transform(key.begin(), key.end(), key.begin(), ::toupper);
	unsigned int j = 0;
	for (int i = 0; i < msg.length(); i++)
	{
		if (isalpha(msg[i]))
		{
			msg[i] += key[j] - 'A';
			if (msg[i] > 'Z') msg[i] += -'Z' + 'A' - 1;
		}
		j = j + 1 == key.length() ? 0 : j + 1;
	}
	return msg;
}

string Vigenere::decryption(string msg, string key)
{
	std::transform(msg.begin(), msg.end(), msg.begin(), ::toupper);
	std::transform(key.begin(), key.end(), key.begin(), ::toupper);
	unsigned int j = 0;
	for (int i = 0; i < msg.length(); i++)
	{
		if (isalpha(msg[i]))
		{
			msg[i] = msg[i] >= key[j] ?
				msg[i] - key[j] + 'A' :
				'A' + ('Z' - key[j] + msg[i] - 'A') + 1;
		}
		j = j + 1 == key.length() ? 0 : j + 1;
	}
	return msg;
}
