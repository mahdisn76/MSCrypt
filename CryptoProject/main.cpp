#include <iostream>
#include <string>
#include "utilities.h"
#include "MSCrypt.h"

using namespace std;

void enc(string key, string plain)
{
	MSCrypt mscrpyt(key);

	cout << "plain:  " << plain << endl;
	cout << "cipher: " << mscrpyt.enc(plain) << endl;
}

void dec(string key, string cipher)
{
	MSCrypt mscrpyt(key);

	cout << "cipher: " << cipher << endl;
	cout << "plain:  " << mscrpyt.dec(cipher) << endl;
}

void ofb(string key, string IV, string text)
{
	MSCrypt mscrypt(key, IV, Mode::OFB);

	cout << "text: " << text << endl;
	cout << "plain/cipher: " << mscrypt.enc(text) << endl;
}

void completeness_avalanche_test(const int m)
{
	MSCrypt mscrypt(generate_random_96_bit());

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

void print_help()
{
	cout << "Welcome to MSCrypt.\nBy Mahdi Salmanzadeh @2021\nmdsalmanzadeh@gmail.com\n\n"
		"Usage: mscript [enc|dec|ofb|test] [in] [options]\n"
		"\nenc\t Encrypt a 96 bit block:\n"
		"\t mscript enc key 96-bit-block\n"
		"\t .\CryptoProject.exe enc 9182736591827365 123456FF1234123456123456\n"
		"\ndec\t Decrypt a 96 bit block:\n"
		"\t mscript dec key 96-bit-block\n"
		"\t .\CryptoProject.exe dec 9182736591827365 2b7d947662bfc65d45ae3790\n"
		"\nofb\t Encrypt/Decrypt a text in OFB mode:\n"
		"\t mscript ofb key IV block\n"
		"\ntest\t Perform completeness and strict avalanche criteria test:\n"
		"\t mscript test [num_test_block=10000]\n"
		"\n Note: Key is 64bit, IV is 96bit, Enter every value in hex.";
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
	else
		print_help();

	return 0;
}