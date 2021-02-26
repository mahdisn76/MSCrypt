#include <iostream>
#include <string>
#include "utilities.h"
#include "MSCrypt.h"
using namespace std;

int maina()
{
	MSCrypt mscrpyt("1010101010111011111010010001100000100111001101101100110011000101");
	
	string plainText = "123456FF1234123456123456"; //24 Hex char
	cout << "plain:  " << plainText << endl;

	auto cipher1 = mscrpyt.enc(plainText);
	cout << "cipher: " << cipher1 << endl;
	   	
	plainText = "133456FF1234123456123456"; //24 Hex char
	cout << "plain:  " << plainText << endl;

	auto cipher2 = mscrpyt.enc(plainText);
	cout << "cipher: " << cipher2 << endl;

	cout << countDifferentBits(cipher1, cipher2) << "bits" << endl;
	   
	return 0;
}

int main()
{
	MSCrypt mscrypt("1010101010111011111010010001100000100111001101101100110011000101",
					"98765432102136457098AB23FF", Mode::OFB);

	auto c = mscrypt.enc("AAAAAAFF1111123456123456123456FF1234123412345656123456FF1234123456123456");
	cout << "cipher: " << c << endl;
	cout << "plain:  " << mscrypt.dec(c) << endl;
	return 0;
}