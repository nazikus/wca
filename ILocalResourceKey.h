#ifndef _ILOCALRESOURCEKEY_
#define _ILOCALRESOURCEKEY_

#include "LocalResourceInfo.h"
#include <string>
using namespace std;

namespace ua { namespace kiev { namespace ukma { namespace downloader {

/**
This is the interface which defines a contract for generators of primary key for LocalResourceInfo
*/
class ILocalResourceKey
{
public:
	/**
	A method to generate key
	@param resource LocalResourceInfo for which we generate its key.
	@return generated key
	*/
	virtual string getKey(LocalResourceInfo& resource) {return "";}
	/**
	Destructor
	*/
	virtual ~ILocalResourceKey() {}
};

}}}}

#endif