#ifndef JSTRINGSTREAM_H
#define JSTRINGSTREAM_H

#include <string>
#include <cstdlib>

#include "jstream.h"

using namespace std;

string bytesToString(unsigned char* p, size_t l);
void stringToBytes(unsigned char*& p, size_t& l, const string& s);

class JStringStream : public JStream
{
	private:
		string value;
	public:
		JStringStream();
		JStringStream(const string& value);
		JStringStream(JStream* downstream, JStream* upstream);
		JStringStream(const string& value, JStream* downstream, JStream* upstream);

		string readValue();
		string readValueReverse();
		string getValue() const;
		void setValue(const string& value);

		void read(unsigned char*& p, size_t& l);
		void readReverse(unsigned char*& p, size_t& l);

		bool isReadable();
		bool isReadableReverse();
};

#endif
