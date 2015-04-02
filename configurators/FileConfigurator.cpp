#include <map>
#include <string>
#include <fstream>
#include <exception>
using namespace std;
#include "FileConfigurator.h"
#include "../FileNotFoundException.h"

namespace ua { namespace kiev { namespace ukma { namespace downloader { namespace configurators {
	FileConfigurator::FileConfigurator(string filename)
	{
		// check if filename is not empty string
		if (filename=="") throw exception("Filename should not be empty string");
		ifstream in;
		in.open(filename.c_str());
		if (!in.is_open()) throw FileNotFoundException("The specified file " + filename + " does not exist");
		// read values and add them to the map
		string s = "";
		string key = "";
		string value = "";
		while (getline(in, s))
		{
			// trim string
			trim(s);
			// check if not a comment
			if (s[0]=='#') continue;
			// check if equal sign is present
			string::size_type f = s.find('=');
			if (f==string::npos) continue;
			// check if only one equal sign is present
			//string::size_type l = s.rfind('=');
			//if (f!=l) continue;
			// split string on the equal sign
			key = s.substr(0,f);
			value = s.substr(f+1);
			values[trim(key)]=trim(value);
		}
	}

	FileConfigurator::~FileConfigurator()
	{
	}

	string FileConfigurator::getValue(const string key) const
	{
		map<string,string>::const_iterator it = values.find(key);
		if  (it != values.end()) return it->second;
		else return "";
	}

	string FileConfigurator::trim(const char * message)
	{
		string s(message);
		return trim(s);
	}

	string FileConfigurator::trim(const string& s)
	{
		// find first non space character
		string::size_type f = s.find_first_not_of(' ');
		// no other characters except ' '
		if (f==string::npos) return "";
		// find last non space character
		string::size_type l = s.find_last_not_of(' ');
		return l==string::npos ? s : string(s, f, l-f+1);
	}

}}}}} // namespace ua::kiev::ukma::downloader::configurators
