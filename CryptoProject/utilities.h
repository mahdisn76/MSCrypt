#pragma once
#include <string>
#include <vector>

std::string num_hex(uint8_t n);

std::string int_to_hex(uint32_t n);

void divide(std::string in, uint32_t& p1, uint32_t& p2, uint32_t& p3);

std::string merge(uint32_t p1, uint32_t p2, uint32_t p3);

std::vector<uint8_t> divide(uint32_t in);

uint32_t merge(const std::vector<uint8_t>& parts);

size_t countOneBits(uint32_t a);

size_t countDifferentBits(std::string h1, std::string h2);

std::vector<std::string> split(std::string text, size_t seq_capacity);

std::string XOR(std::string a, std::string b);