#ifndef _URLLOCALRESOURCEKEY_
#define _URLLOCALRESOURCEKEY_

#include "LocalResourceInfo.h"
#include "ILocalResourceKey.h"
#include <string>
using namespace std;

namespace ua { namespace kiev { namespace ukma { namespace downloader {

/**
This is the implementation, which asumes that URL is the identification key for LocalResourceInfo
*/
	class UrlLocalResourceKey : public ILocalResourceKey
{
public:
	/**
	Constructor
	*/
	UrlLocalResourceKey() {}
	/**
	A method to generate key
	@param resource LocalResourceInfo for which we generate its key.
	@return generated key
	*/
	virtual string getKey(LocalResourceInfo& resource);
	/**
	Destructor
	*/
	virtual ~UrlLocalResourceKey() {}
};

}}}}

#endif