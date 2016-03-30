#include "jstream.h"

JStream::JStream(JStream* downstream, JStream* upstream) : downstream(downstream), upstream(upstream)
{
}

JStream::JStream() : JStream(nullptr, nullptr)
{
}

bool JStream::canRead()
{
	return false;
}

bool canReadReverse()
{
	return false;
}
