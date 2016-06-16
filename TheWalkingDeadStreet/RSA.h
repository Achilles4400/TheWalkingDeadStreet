#pragma once

typedef struct key
{
	long primeKey;
	long eKey;
	long modKey;
} Key;

class RSA
{
public:
	RSA();
	~RSA();

public:
	static Key generateKeys();
	static long encrypt(const long msg, const long key, const long primeKey);

private:
	static long generatePrimeKey(const long firstPrime, const long secondPrime);
	static long generateeKey(const long phi);
	static long generateRevertModKey(const long ekey, const long phi);
	static long generatePhi(const long firstPrime, const long secondPrime);
	static long generatePrime();
	static long computeGCD(const long a, const long b);
	static bool isPrime(const long prime);
};

