#ifndef VIGENERE_H
#define VIGENERE_H

#include <cstdlib>

#include "jstream.h"

class Vigenere : public JStream
{
	private:
		unsigned char* key;
		size_t keyLength;

	public:
		//makes copy of key
		Vigenere(JStream* downstram, JStream* upstream, const unsigned char* key, size_t keyLength);
		Vigenere(JStream* downstream, JStream* upstream);
		Vigenere(const unsigned char* key, size_t keyLength);
		//expects to be terminated
		Vigenere(const char* key);
		Vigenere();
		//~Vigenere();

		const unsigned char* getKey();
		//makes copy
		void setKey(const unsigned char* key, size_t keyLength);
		//makes copy, expected to be terminated
		void setKey(const char* key);

		void read(unsigned char*& p, size_t& l);
		void readReverse(unsigned char*& p, size_t& l);

		bool isReadable();
		bool isReadableReverse();
};


#endif
