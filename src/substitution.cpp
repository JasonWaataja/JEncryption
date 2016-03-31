#include "substitution.h"

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
