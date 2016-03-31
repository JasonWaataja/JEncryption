#ifndef SUBSTITUTION_H
#define SUBSTITUTION_H

#include <map>
#include <cstdlib>

#include "jstream.h"

using namespace std;

class Substitution : public JStream
{
	private:
		map<unsigned char, unsigned char> key;
	public:
		Substitution(JStream* downstream, JStream* upstream, const map<unsigned char, unsigned char>& key);
		Substitution(JStream* downstream, JStream* upstream);
		Substitution(const map<unsigned char,unsigned char>& key);
		Substitution();

		map<unsigned char, unsigned char> getKey();
		void setKey(const map<unsigned char, unsigned char>);

		void read(unsigned char*& p, size_t& l);
		void readReverse(unsigned char*& p, size_t& l);

		bool isReadable();
		bool isReadableReverse();
};

#endif
