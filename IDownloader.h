#ifndef _IDOWNLOADER_
#define _IDOWNLOADER_

#include "WebResourceInfo.h"
#include <string>
namespace ua { namespace kiev { namespace ukma { namespace downloader {

/**
This is an interface which retrieves information about URL and downloads URL to specified localpath.
*/
class IDownloader
{
public:
	///////// TEMPORARY //////////////////
	virtual bool makeDir(string dir) = 0;
	//////////////////////////////////////
	
	/**
	This method retrieves information about web resource using the HTTP HEAD method
	@param url which is a string representing any needed web resource
	@return WebResourceInfo object which incapsulates information about web resource
	*/
	virtual WebResourceInfo getWebResourceInfo(const string& url) = 0;

	/**
	Method which downloads web resource to specified localpath using the information from
	object retrieved by getWebResourceInfo()
	@param WebResourceInfo object
	@return true if web resource was successfully downloaded, false in other case
	*/
	virtual bool download(const WebResourceInfo& resource, const string& localpath) = 0;
	
	/**< Destructor */
	virtual ~IDownloader(){}
};

}}}} // namespace ua::kiev::ukma::downloader
#endif