#include "caesarcipher.h"

#include <cstring>

CaesarCipher::CaesarCipher(const unsigned char* key, unsigned int keyLength) :
	CaesarCipher(nullptr, nullptr, key, keyLength)
{
	this->key = new unsigned char[keyLength];
	memcpy(this->key, key, keyLength);
}

CaesarCipher::CaesarCipher(JStream* downstream, JStream* upstream, const unsigned char* key, unsigned int keyLength) :
	JStream(downstream, upstream), keyLength(keyLength)
{
	this->key = new unsigned char[keyLength];
	memcpy(this->key, key, keyLength);
}

CaesarCipher::CaesarCipher(JStream* downstream, JStream* upstream) :
	JStream(downstream, upstream)
{
	key = new unsigned char[0];
	keyLength = 0;
}

CaesarCipher::CaesarCipher() :
	CaesarCipher(nullptr, nullptr)
{
}

CaesarCipher::~CaesarCipher()
{
	delete[] key;
}

const unsigned char* CaesarCipher::getKey()
{
	return this->key;
}

void CaesarCipher::setKey(const unsigned char* key, unsigned int length)
{
	delete[] key;
	this->key = new unsigned char[length];
	memcpy(this->key, key, length);
}

unsigned int CaesarCipher::getKeyLength()
{
	return this->keyLength;
}

void CaesarCipher::read(unsigned char*& p, unsigned int& l)
{
	if (hasValidDownstream())
	{
		downstream->read(p, l);
		for (int i = 0; i < l; i++) {
			if (i < keyLength) {
				p[i] += key[i];
			}
		}
	} else {
		p = nullptr;
		l = 0;
	}
}

void CaesarCipher::readReverse(unsigned char*& p, unsigned int& l)
{
	if (hasValidUpstream())
	{
		upstream->read(p, l);
		for (int i = 0; i < l; i++) {
			if (i < keyLength) {
				p[i] -= key[i];
			}
		}
	} else {
		p = nullptr;
		l = 0;
	}
}

bool CaesarCipher::hasValidKey()
{
	return key;
}

bool CaesarCipher::isReadable()
{
	return hasValidDownstream() && hasValidKey();
}

bool CaesarCipher::isReadableReverse()
{
	return hasValidUpstream() && hasValidKey();
}
