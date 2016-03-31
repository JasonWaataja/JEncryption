#ifndef JSTREAM_H
#define JSTREAM_H

class JStream
{
	public:
		JStream* upstream;
		JStream* downstream;

		JStream();
		JStream(JStream* downstream, JStream* upstream);

		virtual void read(unsigned char*& p, unsigned int& l) = 0;
		virtual void readReverse(unsigned char*& p, unsigned int& l) = 0;

		virtual bool isReadable();
		virtual bool isReadableReverse();

		bool hasValidDownstream();
		bool hasValidUpstream();
};

#endif
