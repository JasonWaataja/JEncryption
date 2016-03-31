#ifndef CAESARCIPHER_H
#define CAESARCIPHER_H

#include <cstdlib>

#include "jstream.h"

class CaesarCipher : public JStream
{
	private:
		//amount to shift letters
		int shift;
		
	public:
		CaesarCipher(JStream* downstream, JStream* upstream, int shift);
		CaesarCipher(JStream* downstream, JStream* upstream);
		CaesarCipher(int shift);
		CaesarCipher();

		int getShift();
		void setShift(int shift);

		void read(unsigned char*& p, size_t& l);
		void readReverse(unsigned char*& p, size_t& l);

		bool isReadable();
		bool isReadableReverse();

};

#endif
