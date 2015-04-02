#include "WebResourceInfo.h"
/**
This is the interface which ...
*/
namespace ua { namespace kiev { namespace ukma { namespace downloader {
class IValidator
{
public:
	virtual bool isValid(WebResourceInfo resource) = 0;
};
}}}}