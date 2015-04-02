#include <fstream>
using namespace std;

#include "ThreadSafeWriter.h"

namespace ua { namespace kiev { namespace ukma { namespace downloader {

ThreadSafeWriter::ThreadSafeWriter(fstream& file) : _file(file), _lock(false) {}

void ThreadSafeWriter::write(const string s) const 
{
	while (_lock == true) ;
	_lock = true;
	_file << s.c_str();
	_lock = false;
}

void ThreadSafeWriter::writeln(const string& s) const
{
	string ss(s);
	ss += "\n";
	write(ss);
}

}}}}

