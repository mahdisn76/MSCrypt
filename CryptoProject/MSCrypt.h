#pragma once
#include <string>
#include <memory>
#include "RoundKeyGenerator.h"

class MSCrypt
{
	std::string key_;
	std::unique_ptr<RoundKeyGenerator> rkGen_;

	uint8_t sbox(uint8_t in);
	uint32_t pbox(uint32_t in);
	uint32_t F(uint32_t in, uint32_t roundKey);

public:
	MSCrypt(std::string key);
	std::string enc(std::string plain);
	std::string dec(std::string cipher);
};

