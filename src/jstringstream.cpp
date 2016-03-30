#include "jstringstream.h"

#include <cstring>

string bytesToString(unsigned char* p, int l)
{
	char* cString = new char[l];
	memcpy(cString, p, l);
	string s(cString);
	return s;
}

void stringToBytes(unsigned char*& p, int& l, const string& s)
{
	l = s.size() + 1;
	p = new unsigned char[l];
	memcpy(p, s.c_str(), l);
}



JStringStream::JStringStream(const string& value, JStream* downstream, JStream* upstream)
{
	this->value = value;
	this->downstream = downstream;
	this->upstream = upstream;
}

JStringStream::JStringStream(const string& value) : JStringStream(value, nullptr, nullptr)
{
}

JStringStream::JStringStream(JStream* downstream, JStream* upstream) : JStringStream(string(), downstream, upstream)
{
}

JStringStream::JStringStream() : JStringStream(string(), nullptr, nullptr)
{
}

string JStringStream::readValue()
{
	if (canRead()) {
		unsigned char* p;
		unsigned int l;
		downstream->read(p, l);
		value = bytesToString(p, l);
		delete[] p;
		return value;
	} else {
		return string();
	}
}

string JStringStream::readValueReverse()
{
	if (canReadReverse()) {
		unsigned char* p;
		unsigned int l;
		downstream->readReverse(p, l);
		value = bytesToString(p, l);
		delete[] p;
		return value;
	} else {
		return string();
	}
}

string JStringStream::getValue() const
{
	return value;
}

void JStringStream::setValue(const string& value)
{
	this->value = value;
}

void JStringStream::read(unsigned char*& p, unsigned int& l)
{
	stringToBytes(p, l, value);
}

void JStringStream::readReverse(unsigned char*& p, unsigned int& l)
{
	stringToBytes(p, l, value);
}

bool JStringStream::canRead()
{
	if (!downstream)
		return false;
	return downstream->canRead();
}

bool JStringStream::canReadReverse()
{
	if (!upstream)
		return false;
	return upstream->canRead();
}
