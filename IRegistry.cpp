#include "ILocalResourceKey.h"
#include "LocalResourceInfo.h"
#include "IRegistry.h"

namespace ua { namespace kiev { namespace ukma { namespace downloader {

bool IRegistry::addRecord(ILocalResourceKey * keygen, LocalResourceInfo& resource)
{
	if (keygen==NULL)  throw exception("KeyGen is not instantiated");
	string key=keygen->getKey(resource);
	addRecord(key, resource);
}

}}}}