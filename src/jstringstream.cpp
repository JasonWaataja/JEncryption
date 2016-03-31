#include "jstringstream.h"

#include <cstring>
#include <iostream>

using namespace std;

string bytesToString(unsigned char* p, size_t l)
{
	char* cString = new char[l];
	memcpy(cString, p, l);
	string s(cString);
	return s;
}

void stringToBytes(unsigned char*& p, size_t& l, const string& s)
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
	if (hasValidDownstream()) {
		unsigned char* p;
		size_t l;
		downstream->read(p, l);
		value = bytesToString(p, l);
		delete[] p;
	} else {
		value = string();
	}
	return value;
}

string JStringStream::readValueReverse()
{
	if (hasValidUpstream()) {
		unsigned char* p;
		size_t l;
		upstream->readReverse(p, l);
		value = bytesToString(p, l);
		delete[] p;
	} else {
		value = string();
	}
	return value;
}

string JStringStream::getValue() const
{
	return value;
}

void JStringStream::setValue(const string& value)
{
	this->value = value;
}

void JStringStream::read(unsigned char*& p, size_t& l)
{
	stringToBytes(p, l, value);
}

void JStringStream::readReverse(unsigned char*& p, size_t& l)
{
	stringToBytes(p, l, value);
}

bool JStringStream::isReadable()
{
	return true;
}

bool JStringStream::isReadableReverse()
{
	return true;
}
