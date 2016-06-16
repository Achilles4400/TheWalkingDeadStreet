#include "stdafx.h"
#include "RSA.h"


RSA::RSA()
{
}


RSA::~RSA()
{
}

Key RSA::generateKeys()
{
	long firstPirme = generatePrime();
	long secondPrime = generatePrime();
	while (firstPirme == secondPrime) {
		secondPrime = generatePrime();
	}

	Key key;

	long phi = generatePhi(firstPirme, secondPrime);
	key.primeKey = generatePrimeKey(firstPirme, secondPrime);
	key.eKey = generateeKey(phi);
	key.modKey = generateRevertModKey(key.eKey, phi);
	return key;
}

long RSA::encrypt(const long msg, const long key, const long publicKey)
{
	long msg_des = 1;
	long root = msg;
	long index = key;
	while (index)
	{
		if (index & 1)
			msg_des = (msg_des * root) % publicKey;
		index >>= 1;
		root = (root * root) % publicKey;
	}
	return msg_des;
}

long RSA::generatePrimeKey(const long firstPrime, const long secondPrime)
{
	return firstPrime * secondPrime;
}

long RSA::generateeKey(const long phi)
{
	long ekey;
	while (true)
	{
		ekey = rand() % phi;
		if (ekey >= 2 && computeGCD(ekey, phi) == 1)
			break;
	}
	return ekey;
}

long RSA::generateRevertModKey(const long ekey, const long phi)
{
	long dkey = phi / ekey;
	while (true)
	{
		if (((dkey * ekey) % phi) == 1)
			break;
		else
			++dkey;
	}
	return dkey;
}

long RSA::generatePhi(const long firstPrime, const long secondPrime)
{
	return (firstPrime - 1) * (secondPrime - 1);
}

long RSA::generatePrime()
{
	long prime = 0;
	srand(time(0));
	while (true)
	{
		prime = rand() % 100 + 100;
		if (isPrime(prime))
			break;
	}
	return prime;
}

long RSA::computeGCD(const long a, const long b)
{
	long dividend = a;
	long divisor = b;
	long residual = dividend % divisor;
	while (residual)
	{
		dividend = divisor;
		divisor = residual;
		residual = dividend % divisor;
	}
	return divisor;
}

bool RSA::isPrime(const long prime)
{
	int tmp = 2;
	while (tmp < prime)
		if (!(prime % tmp++))
			break;

	if (tmp == prime)
		return true;
	return false;
}
