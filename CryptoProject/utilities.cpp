#include "utilities.h"
#include<sstream>
#include<iomanip>

using namespace std;

string num_hex(uint8_t n)
{
	if (n < 10)
		return to_string(n);

	switch (n)
	{
	case 10:
		return "A";
	case 11:
		return "B";
	case 12:
		return "C";
	case 13:
		return "D";
	case 14:
		return "E";
	case 15:
		return "F";
	}
	return "";
}

std::string int_to_hex(uint32_t n)
{
	stringstream stream;
	stream << setfill('0') << setw(8)
		<< std::hex << n;
	std::string result(stream.str());
	return result;
}

/*
	in: 96bit hex string(32 hex char)
	p1, p2, p3: 32bit int
	Note: p1 is least significiant
*/
void divide(string in, uint32_t& p1, uint32_t& p2, uint32_t& p3)
{
	string s1 = in.substr(0, 8);
	string s2 = in.substr(8, 8);
	string s3 = in.substr(16, 8);

	p1 = stoul(s1, nullptr, 16);
	p2 = stoul(s2, nullptr, 16);
	p3 = stoul(s3, nullptr, 16);
}

/*
	ret: 96bit hex string
*/
string merge(uint32_t p1, uint32_t p2, uint32_t p3)
{
	return int_to_hex(p1) + int_to_hex(p2) + int_to_hex(p3);
}


/*
	in: 32bit int
	ret: first is least significiant
*/
vector<uint8_t> divide(uint32_t in)
{
	vector<uint8_t> parts{
		static_cast<uint8_t>(in & 0xFF),
		static_cast<uint8_t>((in >> 8) & 0xFF),
		static_cast<uint8_t>((in >> 16) & 0xFF),
		static_cast<uint8_t>((in >> 24) & 0xFF)
	};

	return parts;
}

uint32_t merge(const vector<uint8_t>& parts)
{
	uint32_t ret;

	ret = parts[0];
	ret += parts[1] << 8;
	ret += parts[2] << 16;
	ret += parts[3] << 24;

	return ret;
}

size_t countOneBits(uint32_t a)
{
	size_t count = 0;
	for (int i = 0; i < 32; i++)
		if ((a & (1 << i)) > 0)
			count++;

	return count;
}

size_t countDifferentBits(string h1, string h2)
{
	uint32_t a1, a2, a3, b1, b2, b3;
	divide(h1, a1, a2, a3);
	divide(h2, b1, b2, b3);

	return countOneBits(~(a1 ^ b1)) + countOneBits(~(a2 ^ b2)) + countOneBits(~(a3 ^ b3));
}
