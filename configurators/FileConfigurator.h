#ifndef _FILECONFIGURATOR_
#define _FILECONFIGURATOR_

#include <map>
#include <string>
using namespace std;
#include "../IConfigurator.h"
#include "../FileNotFoundException.h"

namespace ua { namespace kiev { namespace ukma { namespace downloader { namespace configurators {

	/**
	This is an implementation of the IConfigurator interface which reads values from the file. Filename is specified in the constructor. If no file was found, FileNotFoundException should be thrown.
	<p>The only possible comment in config file '#'
	<p>Keys must be unique for every value
	<p>Only one value in a row is alowed
	<p>Values in the config file should be delimited with equal sign ('=')
	<p>If no equal sign is present in the line, this line will be ignored
	<p>If more than one equal sign is present in the line, this line will be ignored
	*/
	class FileConfigurator : public IConfigurator
	{
	public:
		/**
		Creates instance. Reading values from the config file will be done at this step.
		@param filename Filename, from which we get configured values
		@throw FileNotFoundException If the specifified file was not found 
		*/
		FileConfigurator(string filename);
		/**
		Destructs instance.
		*/
		virtual ~FileConfigurator();
		/**
		This method will be used to obtain a value from config file for the given key
		@param key The key, value for which we have to look in the config file
		@return Value for the given key from the config file or empty string, if no value for the given key exists in the config file
		*/
		virtual string getValue(const string key) const;
	protected:
		std::map<string,string> values;
		static string trim(const string&);
		static string trim(const char *);
	private:
		FileConfigurator(FileConfigurator&);
		FileConfigurator& operator= (FileConfigurator&);
	};

}}}}} // namespace ua::kiev::ukma::downloader::configurators
#endif