#ifndef JFILESTREAM_H
#define JFILESTREAM_H

#include "jstream.h"

#include <string>

using namespace std;

class JFileStream : public JStream
{
	private:
		string path;

	public:
		JFileStream(const string& path);
		JFileStream(JStream* downstream, JStream* upstream, const string& path);
		JFileStream(JStream* downstream, JStream* upstream);
		JFileStream();

		string getPath();
		void setPath(const string& path);

		void readStreamToFile();
		//allocates with new
		void readStreamToFile(unsigned char*& p, size_t& l);
		void readStreamToFileReverse();
		//allocates with new
		void readStreamToFileReverse(unsigned char*& p, size_t& l);

		void read(unsigned char*& p, size_t& l);
		void readReverse(unsigned char*& p, size_t& l);

		bool isReadable();
		bool isReadableReverse();
};

#endif
