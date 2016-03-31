#ifndef JSTRINGSTREAM_H
#define JSTRINGSTREAM_H

#include <string>
#include "jstream.h"

using namespace std;

string bytesToString(unsigned char* p, unsigned int l);
void stringToBytes(unsigned char*& p, unsigned int& l, const string& s);

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

		void read(unsigned char*& p, unsigned int& l);
		void readReverse(unsigned char*& p, unsigned int& l);

		bool isReadable();
		bool isReadableReverse();
};

#endif
