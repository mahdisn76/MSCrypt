#include <iostream>
#include <string>
#include "utilities.h"
#include "MSCrypt.h"

using namespace std;

void enc(string key, string plain)
{
	MSCrypt mscrpyt(stoull(key, nullptr, 16));
	cout << remove_left_zeros(mscrpyt.enc(plain)) << endl;
}

void dec(string key, string cipher)
{
	MSCrypt mscrpyt(stoull(key, nullptr, 16));
	cout << remove_left_zeros(mscrpyt.dec(cipher)) << endl;
}

void ofb(string key, string IV, string text)
{
	MSCrypt mscrypt(stoull(key, nullptr, 16), IV, Mode::OFB);
	cout << remove_left_zeros(mscrypt.enc(text)) << endl;
}

void completeness_avalanche_test(const int m)
{
	MSCrypt mscrypt(generate_random_uint64());

	size_t mat[96][96] = { 0 };

	for (auto i = 0; i < m; i++)
	{
		string a = generate_random_96_bit();
		string a_cipher = mscrypt.enc(a);

		for (auto j = 0; j < 96; j++)
		{
			string b = flip_bit(a, j);
			auto b_cipher = mscrypt.enc(b);

			auto r = hex_to_bin(XOR(a_cipher, b_cipher));
			add(mat, j, r);
		}
	}

	for (auto i = 0; i < 96; i++)
		for (auto j = 0; j < 96; j++)
			cout << mat[i][j] << (j == 95 ? "\n" : " ");
}

void stream(size_t len)
{
	auto key = generate_random_uint64();
	string plain = generate_random_96_bit();

	MSCrypt mscrypt(key);

	for (int i = 0; i < len; i++)
	{
		plain = mscrypt.enc(plain);
		cout << hex_to_bin(plain)[95];
	}

	cout << endl;
}

void print_help()
{
	cout << "Welcome to MSCrypt.\nBy Mahdi Salmanzadeh @2021\nmdsalmanzadeh@gmail.com\n\n"
		"Usage: mscript [enc|dec|ofb|stream|test] [...]\n"
		"\nenc\t Encrypt a 96 bit block:\n"
		"\t mscript enc key 96-bit-block\n"
		"\t .\\MSCrypt.exe enc 9182736591827365 123456FF1234123456123456\n"
		"\ndec\t Decrypt a 96 bit block:\n"
		"\t mscript dec key 96-bit-block\n"
		"\t .\\MSCrypt.exe dec 9182736591827365 c9fe73a6e8a4110294ac1cf2\n"
		"\nofb\t Encrypt/Decrypt a text in OFB mode:\n"
		"\t .\\MSCrypt.exe ofb key IV block\n"
		"\nstream\t Create a random l-bit stream:\n"
		"\t .\\MSCrypt.exe len\n"
		"\ntest\t Perform completeness and strict avalanche criteria test:\n"
		"\t .\\MSCrypt.exe test [num_test_block=10000]\n"
		"\nNote: Key is 64bit, IV is 96bit, Enter every value in hex.\n\n";
}

int main(int argc, char** argv)
{
	if (argc <= 1)
	{
		print_help();
		return 0;
	}

	if (string(argv[1]) == "test")
		completeness_avalanche_test(argc == 3 ? stoi(argv[2]) : 10000);
	else if (string(argv[1]) == "enc" && argc == 4)
		enc(argv[2], argv[3]);
	else if (string(argv[1]) == "dec" && argc == 4)
		dec(argv[2], argv[3]);
	else if (string(argv[1]) == "ofb" && argc == 5)
		ofb(argv[2], argv[3], argv[4]);
	else if (string(argv[1]) == "stream" && argc == 3)
		stream(stoul(argv[2]));
	else
		print_help();

	return 0;
}