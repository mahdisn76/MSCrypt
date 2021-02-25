#include <iostream>
#include <string>
#include "RoundKeyGenerator.h"
using namespace std;

// Array to hold the 16 keys

// Function to do a circular left shift by 1
string shift_left_once(string key_chunk) {
	string shifted = "";
	for (int i = 1; i < 28; i++) {
		shifted += key_chunk[i];
	}
	shifted += key_chunk[0];
	return shifted;
}
// Function to do a circular left shift by 2
string shift_left_twice(string key_chunk) {
	string shifted = "";
	for (int i = 0; i < 2; i++) {
		for (int j = 1; j < 28; j++) {
			shifted += key_chunk[j];
		}
		shifted += key_chunk[0];
		key_chunk = shifted;
		shifted = "";
	}
	return key_chunk;
}

RoundKeyGenerator::RoundKeyGenerator(std::string key)
{
	// 1. Compressing the key using the PC1 table
	string perm_key = "";
	for (int i = 0; i < 56; i++) {
		perm_key += key[pc1[i] - 1];
	}
	// 2. Dividing the result into two equal halves
	string left = perm_key.substr(0, 28);
	string right = perm_key.substr(28, 28);

	// Generating 16 keys
	for (int i = 0; i < 12; i++) {
		// 3.1. For rounds 1, 2, 9, 16 the key_chunks
		// are shifted by one.
		if (i == 0 || i == 1 || i == 8 || i == 15) {
			left = shift_left_once(left);
			right = shift_left_once(right);
		}
		// 3.2. For other rounds, the key_chunks
		// are shifted by two
		else {
			left = shift_left_twice(left);
			right = shift_left_twice(right);
		}
		// 4. The chunks are combined
		string combined_key = left + right;
		string round_key = "";
		// 5. Finally, the PC2 table is used to transpose
		// the key bits
		for (int i = 0; i < 32; i++) {
			round_key += combined_key[pc2[i] - 1];
		}
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
