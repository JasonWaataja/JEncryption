#include "jstream.h"

#include <iostream>

using namespace std;

JStream::JStream(JStream* downstream, JStream* upstream) : downstream(downstream), upstream(upstream)
{
}

JStream::JStream() : JStream(nullptr, nullptr)
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
