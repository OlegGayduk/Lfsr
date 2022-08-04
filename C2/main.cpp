#include <iostream>
#include <string>
using namespace std;

//extern "C" void lfsr(void);
//extern "C" string str;

int lfsr() {

	static unsigned long S = 0x00000001;
	S = ((((S >> 31) ^ (S >> 30) ^ (S >> 29) ^ (S >> 27) ^ (S >> 25) ^ S) & 0x00000001) << 31) | (S >> 1);
	return S & 0x00000001;
}

int getKey() {

	int key = 0;
	for (int i = 0; i < 32; i++) key = (key << 1) | lfsr();
	return key;
}

int deLfsr() {

	static unsigned long S = 0x00000001;
	S = ((((S >> 25) ^ (S >> 27) ^ (S >> 29) ^ (S >> 30) ^ (S >> 31) ^ S) & 0x00000001) << 31) | (S >> 1);
	return S & 0x00000001;
}

int unKey() {

	int key = 0;
	for (int i = 0; i < 32; i++) key = (key << 1) | deLfsr();
	return key;
}

int main() {

	string str;// вывод строки на консоль 
	cout << "Enter the string: " << endl;// считывание строки из консоли в переменную 
	getline(cin, str);

	cout << endl << "cipher: ";

	for (int i = 0; i < str.length(); i++) {
		str[i] ^= getKey();
		cout << str[i];
	}

	cout << endl << "decipher: ";

	for (int i = 0; i < str.length(); i++) {
		str[i] ^= unKey();
		cout << str[i];
	}

	cout << endl;

	system("pause");

	return 0;
}