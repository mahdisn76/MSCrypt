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

void ofb()
{
	MSCrypt mscrypt("1010101010111011111010010001100000100111001101101100110011000101",
					"98765432102136457098AB23FF", Mode::OFB);

	auto c = mscrypt.enc("AAAAAAFF1111123456123456123456FF1234123412345656123456FF1234123456123456");
	cout << "cipher: " << c << endl;
	cout << "plain:  " << mscrypt.dec(c) << endl;
}

void completeness_avalanche_test(int m = 10000)
{
	MSCrypt mscrypt(hex_to_bin(generate_random_96_bit()));

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
		"\nenc\t Encrypt a 96 bit block using a key\n"
		"\t mscript enc -[b|h|f] [key] -[b|h|f] [block]\n"
		"\ndec\t Decrypt a 96 bit block using a key\n"
		"\t mscript dec -[b|h|f] [key] -[b|h|f] [block]\n"
		"\nofb\t Encrypt/Decrypt a text in OFB mode using a key\n"
		"\t mscript ofb -[b|h|f] [key] -[b|h|f] [block]\n"
		"\ntest\t Perform completeness and strict avalanche criteria test.\n"
		"\t mscript test [num_block=10000]\n";
}

int main(int argc, char** argv)
{
	if (argc <= 1)
	{
		print_help();
		return 0;
	}

	if (string(argv[1]) == "test")
		completeness_avalanche_test();
	else if (string(argv[1]) == "enc")
		enc("1010101010111011111010010001100000100111001101101100110011000101", "123456FF1234123456123456");
	else if (string(argv[1]) == "dec")
		dec("1010101010111011111010010001100000100111001101101100110011000101", "c0a0cb2571dab5706e01db86");
	else if (string(argv[1]) == "ofb")
		ofb();
	else
		print_help();
	return 0;
}