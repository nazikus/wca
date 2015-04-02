#include "UrlLocalResourceKey.h"

namespace ua { namespace kiev { namespace ukma { namespace downloader { 
	string UrlLocalResourceKey::getKey(LocalResourceInfo& resource)
	{
		return resource.getUrl();
	}



}}}}
