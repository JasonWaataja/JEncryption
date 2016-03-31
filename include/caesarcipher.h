#ifndef CAESARCIPHER_H
#define CAESARCIPHER_H

#include <string>

#include "jstream.h"

using namespace std;

class CaesarCipher : public JStream
{
	private:
		unsigned char* key;
		unsigned int keyLength;

	public:
		//makes copy
		CaesarCipher(const unsigned char* key, unsigned int keyLength);
		CaesarCipher(JStream* downstream, JStream* upstream, const unsigned char* key, unsigned int keyLength);
		CaesarCipher(JStream* downstream, JStream* upstream);
		CaesarCipher();
		~CaesarCipher();

		const unsigned char* getKey();
		//makes copy
		void setKey(const unsigned char* key, unsigned int length);
		unsigned int getKeyLength();

		void read(unsigned char*& p, unsigned int& l);
		void readReverse(unsigned char*& p, unsigned int& l);

		bool hasValidKey();

		bool isReadable();
		bool isReadableReverse();
};

#endif
