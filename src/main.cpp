#include <iostream>
#include <string>

#include "jstream.h"
#include "jstringstream.h"
#include "caesarcipher.h"
#include "vigenere.h"

using namespace std;

int main(int argc, char** argv)
{
	//JStringStream start("Hello World");
	//JStringStream end(&start, nullptr);
	//string value = end.readValue();
	//cout << value << endl;



	JStringStream start("Hello World");
	JStringStream end;
	//CaesarCipher cipher(3);
	Vigenere cipher("key");
	linkJStreams(&start, &cipher, &end);
	string encrypted = end.readValue();
	cout << encrypted << endl;
	string decrypted = start.readValueReverse();
	cout << decrypted << endl;
}
