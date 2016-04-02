#include "jfilestream.h"

#include <fstream>
#include <iostream>

JFileStream::JFileStream(const string& path) : JFileStream(nullptr, nullptr, path)
{
}

JFileStream::JFileStream(JStream* downstream, JStream* upstream, const string& path) :
	JStream(downstream, upstream), path(path)
{
}

JFileStream::JFileStream(JStream* downstream, JStream* upstream) :
	JFileStream(downstream, upstream, string())
{
}

JFileStream::JFileStream() : JFileStream(nullptr, nullptr, string())
{
}

string JFileStream::getPath()
{
	return this->path;
}

void JFileStream::setPath(const string& path)
{
	this->path = path;
}

void JFileStream::readStreamToFile(unsigned char*& p, size_t& l)
{
	if (hasValidDownstream()) {
		downstream->read(p, l);
		if (p != nullptr) {

			ofstream writer(path, ios::binary);
			if (writer.is_open()) {
				const char* asCharArray = reinterpret_cast<const char*>(p);
				writer.write(asCharArray, l);
				writer.close();
			} else {
				p = nullptr;
				l = 0;
			}

		}
	} else {
		p = nullptr;
		l = 0;
	}
}

void JFileStream::readStreamToFile()
{
	unsigned char* p;
	size_t l;
	readStreamToFile(p, l);
	delete[] p;
}

void JFileStream::readStreamToFileReverse(unsigned char*& p, size_t& l)
{
	if (hasValidUpstream()) {
		upstream->readReverse(p, l);
		if (p != nullptr) {

			ofstream writer(path, ios::binary);
			if (writer.is_open()) {
				const char* asCharArray = reinterpret_cast<const char*>(p);
				writer.write(asCharArray, l);
				writer.close();
			} else {
				p = nullptr;
				l = 0;
			}

		}
	} else {
		p = nullptr;
		l = 0;
	}
}

void JFileStream::readStreamToFileReverse()
{
	unsigned char* p;
	size_t l;
	readStreamToFileReverse(p, l);
	delete[] p;
}

void JFileStream::read(unsigned char*& p, size_t& l)
{
	ifstream reader(path, ios::binary | ios::ate);
	if (reader.is_open()) {
		l = reader.tellg();
		reader.seekg(0, ios::beg);
		char* fileData = new char[l];
		reader.read(fileData, l);
		reader.close();
		p = reinterpret_cast<unsigned char*>(fileData);
	} else {
		p = nullptr;
		l = 0;
	}
}

void JFileStream::readReverse(unsigned char*& p, size_t& l)
{
	ifstream reader(path, ios::binary | ios::ate);
	if (reader.is_open()) {
		l = reader.tellg();
		reader.seekg(0, ios::beg);
		char* fileData = new char[l];
		reader.read(fileData, l);
		reader.close();
		p = reinterpret_cast<unsigned char*>(fileData);
	} else {
		p = nullptr;
		l = 0;
	}
}

bool JFileStream::isReadable() {
	return true;
}

bool JFileStream::isReadableReverse() {
	return true;
}
