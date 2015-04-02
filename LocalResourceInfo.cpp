#include "LocalResourceInfo.h"

namespace ua { namespace kiev { namespace ukma { namespace downloader {

	LocalResourceInfo::LocalResourceInfo() : _url(""), _date(""), _localPath("") {}

	LocalResourceInfo::LocalResourceInfo(const string& url,const  string& date,const string& localPath) : _url(url), _date(date), _localPath(localPath) {}

	LocalResourceInfo::LocalResourceInfo(const LocalResourceInfo& right) : _url(right._url), _date(right._date), _localPath(right._localPath) {}

	LocalResourceInfo& LocalResourceInfo::operator =(const LocalResourceInfo& right)
	{
		if (&right == this) return *(this);
		_url = right._url;
		_date = right._date;
		_localPath = right._localPath;
		return *(this);
	}

	string LocalResourceInfo::getDate() const
	{
		return _date;
	}

	string LocalResourceInfo::getUrl() const
	{
		return _url;
	}

	string LocalResourceInfo::getLocalPath() const
	{
		return _localPath;
	}

	

}}}}