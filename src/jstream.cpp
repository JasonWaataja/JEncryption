#include "jstream.h"

#include <iostream>

using namespace std;

JStream::JStream(JStream* downstream, JStream* upstream) : downstream(downstream), upstream(upstream)
{
}

JStream::JStream() : JStream(nullptr, nullptr)
{
}

JStream::~JStream()
{
}

bool JStream::isReadable()
{
	return false;
}

bool JStream::isReadableReverse()
{
	return false;
}

bool JStream::hasValidDownstream()
{
	if (!downstream)
		return false;
	return downstream->isReadable();
}

bool JStream::hasValidUpstream()
{
	if (!upstream)
		return false;
	return upstream->isReadableReverse();
}

void linkJStreams(JStream* downstream, JStream* upstream)
{
	downstream->upstream = upstream;
	upstream->downstream = downstream;
}

void linkJStreams(JStream* downstream, JStream* middle, JStream* upstream)
{
	linkJStreams(downstream, middle);
	linkJStreams(middle, upstream);
}

void unlinkJStreams(JStream* downstream, JStream* upstream)
{
	downstream->upstream = nullptr;
	upstream->downstream = nullptr;
}

void unlinkJStreams(JStream* downstream, JStream* middle, JStream* upstream)
{
	unlinkJStreams(downstream, middle);
	unlinkJStreams(middle, upstream);
}
