#include <iostream>
#include <string>
#include "RoundKeyGenerator.h"
using namespace std;

string shift_left_once(string key_chunk) {
	string shifted = "";
	for (int i = 1; i < 28; i++)
		shifted += key_chunk[i];
	
	shifted += key_chunk[0];
	return shifted;
}

string shift_left_twice(string key_chunk) {
	string shifted = "";
	for (int i = 0; i < 2; i++) 
	{
		for (int j = 1; j < 28; j++)
			shifted += key_chunk[j];

		shifted += key_chunk[0];
		key_chunk = shifted;
		shifted = "";
	}
	return key_chunk;
}

RoundKeyGenerator::RoundKeyGenerator(std::string key)
{
	string perm_key = "";
	for (int i = 0; i < 56; i++)
		perm_key += key[pc1[i] - 1];

	string left = perm_key.substr(0, 28);
	string right = perm_key.substr(28, 28);

	for (int i = 0; i < 12; i++) 
	{
		if (i == 0 || i == 1 || i == 8 || i == 15)
		{
			left = shift_left_once(left);
			right = shift_left_once(right);
		}
		else
		{
			left = shift_left_twice(left);
			right = shift_left_twice(right);
		}

		string combined_key = left + right;
		string round_key = "";

		for (int i = 0; i < 32; i++) 
			round_key += combined_key[pc2[i] - 1];
		
		round_keys[i] = stoul(round_key, nullptr, 2);
	}
}

uint32_t RoundKeyGenerator::getEncRoundKey(int index)
{
	return round_keys[index];
}

uint32_t RoundKeyGenerator::getDecRoundKey(int index)
{
	return round_keys[11 - index];
}
