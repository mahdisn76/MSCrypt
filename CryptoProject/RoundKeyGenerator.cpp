#include <iostream>
#include <string>
#include "RoundKeyGenerator.h"
using namespace std;

constexpr auto LB64_MASK = 0x0000000000000001;

RoundKeyGenerator::RoundKeyGenerator(uint64_t key)
{
	uint64_t permuted_choice_1 = 0;
	for (auto i = 0; i < 56; i++)
	{
		permuted_choice_1 <<= 1;
		permuted_choice_1 |= (key >> (64 - pc1[i]))& LB64_MASK;
	}

	uint32_t C = (uint32_t)((permuted_choice_1 >> 28) & 0x000000000fffffff);
	uint32_t D = (uint32_t)(permuted_choice_1 & 0x000000000fffffff);

	for (auto i = 0; i < 12; i++)
	{
		for (auto j = 0; j < iteration_shifts[i]; j++)
		{
			C = (0x0fffffff & (C << 1)) | (0x00000001 & (C >> 27));
			D = (0x0fffffff & (D << 1)) | (0x00000001 & (D >> 27));
		}

		uint64_t permuted_choice_2 = (((uint64_t)C) << 28) | (uint64_t)D;

		round_keys[i] = 0;
		for (auto j = 0; j < 32; j++)
		{
			round_keys[i] <<= 1;
			round_keys[i] |= (permuted_choice_2 >> (56 - pc2[j]))& LB64_MASK;
		}
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
