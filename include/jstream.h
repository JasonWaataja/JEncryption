#ifndef JSTREAM_H
#define JSTREAM_H

#include <cstdlib>

class JStream
{
	public:
		JStream* upstream;
		JStream* downstream;

		JStream();
		JStream(JStream* downstream, JStream* upstream);
		virtual ~JStream();

		virtual void read(unsigned char*& p, size_t& l) = 0;
		virtual void readReverse(unsigned char*& p, size_t& l) = 0;

		virtual bool isReadable();
		virtual bool isReadableReverse();

		bool hasValidDownstream();
		bool hasValidUpstream();
};

void linkJStreams(JStream* downstream, JStream* upstream);
void linkJStreams(JStream* downstream, JStream* middle, JStream* upstream);
void unlinkJStreams(JStream* downstream, JStream* upstream);
void unlinkJStreams(JStream* downstream, JStream* middle, JStream* upstream);

#endif
