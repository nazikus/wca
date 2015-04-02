#include "FileNotFoundException.h"
#include <string>
using namespace std;

namespace ua { namespace kiev { namespace ukma { namespace downloader {

	FileNotFoundException::FileNotFoundException(const string message) : _message(message), exception(message.c_str()) {}

	const char * FileNotFoundException::what() const
	{
		return _message.c_str();
	}

}}}} // namespace ua::kiev::ukma::downloader