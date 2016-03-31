#include "vigenere.h"

#include <cstring>

Vigenere::Vigenere(JStream* downstream, JStream* upstream, const unsigned char* key, size_t keyLength) :
	JStream(downstream, upstream), keyLength(keyLength)
{
	this->key = new unsigned char[keyLength];
	if (key != nullptr) {
		memcpy(this->key, key, keyLength);
	}
}

Vigenere::Vigenere(JStream* downstream, JStream* upstream) :
	JStream(downstream, upstream), key(nullptr), keyLength(0)
{
}

Vigenere::Vigenere(const unsigned char* key, size_t keyLength) :
	Vigenere(nullptr, nullptr, key, keyLength)
{
}

Vigenere::Vigenere(const char* key) : JStream(nullptr, nullptr)
{
	if (key != nullptr) {
		keyLength = strlen(key) + 1;
		this->key = new unsigned char[keyLength];
		memcpy(this->key, key, keyLength);
	} else {
		keyLength = 0;
		this->key = new unsigned char[keyLength];
	}
}

Vigenere::Vigenere() :
	Vigenere(nullptr, nullptr)
{
}

//Vigenere::~Vigenere()
//{
	//delete[] this->key;
//}

const unsigned char* Vigenere::getKey()
{
	return this->key;
}

void Vigenere::setKey(const unsigned char* key, size_t keyLength)
{
	this->keyLength = keyLength;
	this->key = new unsigned char[keyLength];
	if (key != nullptr) {
		memcpy(this->key, key, keyLength);
	}
}

void Vigenere::setKey(const char* key)
{
	if (key != nullptr) {
		keyLength = strlen(key) + 1;
		this->key = new unsigned char[keyLength];
		memcpy(this->key, key, keyLength);
	} else {
		keyLength = 0;
		this->key = new unsigned char[keyLength];
	}
}


void Vigenere::read(unsigned char*& p, size_t& l)
{
	if (hasValidDownstream()) {
		downstream->read(p, l);
		if (keyLength > 0 && p != nullptr && key != nullptr) {
			for (int i = 0; i < l; i++) {
				p[i] += this->key[i % keyLength];
			}
		} else {
			p = nullptr;
			l = 0;
		}
	} else {
		p = nullptr;
		l = 0;
	}
}

void Vigenere::readReverse(unsigned char*& p, size_t& l)
{
	if (hasValidUpstream()) {
		upstream->readReverse(p, l);
		if (keyLength > 0 && p != nullptr && key != nullptr) {
			for (int i = 0; i < l; i++) {
				p[i] -= this->key[i % keyLength];
			}
		} else {
			p = nullptr;
			l = 0;
		}
	} else {
		p = nullptr;
		l = 0; 
	}
}

bool Vigenere::isReadable()
{
	return hasValidDownstream();
}

bool Vigenere::isReadableReverse()
{
	return hasValidUpstream();
}
