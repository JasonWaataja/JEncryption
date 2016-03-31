#include "caesarcipher.h"

CaesarCipher::CaesarCipher(JStream* downstream, JStream* upstream, int shift) :
	JStream(downstream, upstream), shift(shift)
{
}

CaesarCipher::CaesarCipher(JStream* downstream, JStream* upstream) :
	CaesarCipher(downstream, upstream, 0)
{
}

CaesarCipher::CaesarCipher(int shift) :
	CaesarCipher(nullptr, nullptr, shift)
{
}

CaesarCipher::CaesarCipher() : CaesarCipher(nullptr, nullptr, 0)
{
}

int CaesarCipher::getShift()
{
	return this->shift;
}

void CaesarCipher::setShift(int shift)
{
	this->shift = shift;
}

void CaesarCipher::read(unsigned char*& p, size_t& l)
{
	if (hasValidDownstream()) {
		downstream->read(p, l);
		if (p != nullptr) {
			for (int i = 0; i < l; i++) {
				p[i] += this->shift;
			}
		} else {
			l = 0;
		}
	} else {
		p = nullptr;
		l = 0;
	}
}

void CaesarCipher::readReverse(unsigned char*& p, size_t& l)
{
	if (hasValidUpstream()) {
		upstream->readReverse(p, l);
		if (p != nullptr) {
			for (int i = 0; i < l; i++) {
				p[i] -= this->shift;
			}
		} else {
			l = 0;
		}
	} else {
		p = nullptr;
		l = 0;
	}
}

bool CaesarCipher::isReadable()
{
	return this->hasValidDownstream();
}

bool CaesarCipher::isReadableReverse()
{
	return this->hasValidUpstream();
}
