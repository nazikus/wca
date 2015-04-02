#ifndef _LOCALRESOURCEINFO_
#define _LOCALRESOURCEINFO_

#include<string>
using namespace std;

namespace ua { namespace kiev { namespace ukma { namespace downloader {

/**
This is the interface which contains general information about downloaded resource from the web. It must contain information about: <ul>
<li>url</li>
<li>date</li>
<li>localpath</li>
</ul>
*/
class LocalResourceInfo
{
public:
	LocalResourceInfo();
	LocalResourceInfo(const string& url, const string& date, const string& localPath);
	LocalResourceInfo(const LocalResourceInfo&);
	LocalResourceInfo& operator= (const LocalResourceInfo&);
	virtual ~LocalResourceInfo() {};
	string getUrl() const;
	string getDate() const;
	string getLocalPath() const;
private:
	string _url;
	string _date;
	string _localPath;
};

}}}}

#endif