#ifndef _FILENOTFOUNDEXCEPTION_
#define _FILENOTFOUNDEXCEPTION_

#include <string>
#include <exception>
using namespace std;

namespace ua { namespace kiev { namespace ukma { namespace downloader {

	/**
	This is an exception, which should be thrown is the provided file does not exists
	*/
	class FileNotFoundException : public exception
	{
	public:
		/**
		Constructs instance with the specified error message
		@param message Error message
		*/
		FileNotFoundException(const string message);
		/**
		This method will be used to get the reason of the exception
		*/
		virtual const char* what() const ;
	private:
		string _message;
	};

}}}} // namespace ua::kiev::ukma::downloader
#endif