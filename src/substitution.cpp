#include "substitution.h"

#include <random>
#include <iostream>
#include <vector>

using namespace std;

map<unsigned char, unsigned char> createRandomSubstituionKey()
{
	map<unsigned char, unsigned char> key;
	vector<unsigned char> availableValues(256);
	//put in the numbers 0-255.
	for (int i = 0; i < 256; i++) {
		availableValues[i] = i;
	}
	for (int i = 255; i >= 0; i--) {
		random_device device;
		uniform_int_distribution<> dist(0,i);
		int index = dist(device);
		key[255 - i] = availableValues[index];
		availableValues.erase(availableValues.begin() + index);
	}
	return key;
}

Substitution::Substitution(JStream* downstream, JStream* upstream, const map<unsigned char, unsigned char>& key) :
	JStream(downstream, upstream), key(key)
{
}

Substitution::Substitution(JStream* downstream, JStream* upstream) :
	JStream(downstream, upstream)
{
}

Substitution::Substitution(const map<unsigned char, unsigned char>& key) :
	Substitution(nullptr, nullptr, key)
{
}

Substitution::Substitution() : JStream(nullptr, nullptr)
{
}

map<unsigned char, unsigned char> Substitution::getKey()
{
	return this->key;
}

void Substitution::setKey(const map<unsigned char, unsigned char> key)
{
	this->key = key;
}

void Substitution::read(unsigned char*& p, size_t& l)
{
	if (hasValidDownstream()) {
		downstream->read(p, l);
		if (p != nullptr) {
			for (int i = 0; i < l; i++) {
				unsigned char unencrypted = p[i];
				auto encrypted = key.find(unencrypted);
				if (encrypted != key.end()) {
					p[i] = encrypted->second;
				}
			}
		} else {
			p = nullptr;
		}
	} else {
		p = nullptr;
		l = 0;
	}
}

void Substitution::readReverse(unsigned char*& p, size_t& l)
{
	if (hasValidUpstream()) {
		upstream->readReverse(p, l);
		if (p != nullptr) {
			for (int i = 0; i < l; i++) {
				unsigned char encrypted = p[i];
				bool valueFound = false;
				for (auto it = key.begin(); it != key.end() && !valueFound; it++) {
					if (it->second == encrypted) {
						p[i] = it->first;
						valueFound = true;
					}
				}
			}
		} else {
			p = nullptr;
		}
	} else {
		p = nullptr;
		l = 0;
	}
}

bool Substitution::isReadable()
{
	return hasValidDownstream();
}

bool Substitution::isReadableReverse()
{
	return hasValidUpstream();
}
