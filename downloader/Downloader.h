#ifndef _DOWNLOADER_
#define _DOWNLOADER_

#include <string>
#include "../IDownloader.h"
#include "../WebResourceInfo.h"
namespace ua { namespace kiev { namespace ukma { namespace downloader { namespace downloaders {

/**
Class which is the implementation of IDownloader. Downloader uses Client URL Request Library (cURL)
to communicate with web servers. Main purpose of the class is to retrieve various information 
about web resource and to download it.
*/
	
class Downloader: public IDownloader
{
	/**
	Method which is an aiding function for cURL. Its prototype is a MUST of cURL.
	@param pointer to the allocation where downloaded segment is temporary stored
	@param size of a byte
	@param amount of downloaded bytes
	@param stream which will be written with the data where ptr points
	@return amount of succesfully downloaded bytes (has to be equal size*nmemb)
	*/
	static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream);
	
	Downloader(const Downloader&); 	/**< Copy constructor is not allowed */
public:
	///////// TEMPORARY ////////////
	bool makeDir(string dir);
	////////////////////////////////
	Downloader();		/**< Default constructor */
	~Downloader();		/**< Destructor */
	
	/**
	This method retrieves information about web resource using the cURL's HTTP HEAD request
	@param url which is a string representing any needed web resource
	@return WebResourceInfo object which incapsulates information about web resource
	*/
	WebResourceInfo getWebResourceInfo(const string& url);
	
	/**
	Method which downloads web resource to specified localpath using the information from
	object retrieved by getWebResourceInfo(). Downloading is performed by cURL's implementation
	of the HTTP GET method. Download method supports up to 5 redirections in a row.
	@param WebResourceInfo object
	@return true if web resource was successfully downloaded, false in other case
	*/
	bool download(const WebResourceInfo& resource, const string& localpath);
};

}}}}} // namespace ua::kiev::ukma::downloader::downloaders
#endif