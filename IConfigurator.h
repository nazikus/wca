#ifndef _ICONFIGURATOR_
#define _ICONFIGURATOR_

namespace ua { namespace kiev { namespace ukma { namespace downloader {

	/**
	This is an interface which defines a contract for all classes, which get values from configuration files. By this time, we do not provide a possibility to set values to configuration file programatically (there are no setValue() methods). The user should change config file manually, in his own Text editor.
	*/
	class IConfigurator
	{
	public:
		/**
		This method will be used to obtain a value from config file for the given key
		@param key The key, value for which we have to look in the config file
		@return Value for the given key from the config file or null, if no value for the given key exists in the config file
		*/
		virtual string getValue(const string key) const = 0;
		/** 
		Destructor
		*/
		virtual ~IConfigurator() {};
	};

}}}} // namespace ua::kiev::ukma::downloader
#endif