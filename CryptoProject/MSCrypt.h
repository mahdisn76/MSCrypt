#pragma once
#include <string>
#include <memory>
#include "RoundKeyGenerator.h"

enum class Mode
{
	Block,
	OFB
};

class MSCrypt
{
	uint64_t key_;
	std::string IV_;
	Mode mode_;
	std::unique_ptr<RoundKeyGenerator> rkGen_;

	uint8_t sbox(uint8_t in);
	uint32_t pbox(std::vector<uint8_t> in);
	uint32_t F(uint32_t in, uint32_t roundKey);
	std::string enc_block(std::string plain);
	std::string dec_block(std::string cipher);
	std::string ofb(std::string text);


public:
	MSCrypt(uint64_t key, std::string IV = "", Mode mode = Mode::Block);
	std::string enc(std::string plain);
	std::string dec(std::string cipher);
};

