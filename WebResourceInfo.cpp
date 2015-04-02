#include "WebResourceInfo.h"

#include <istream>
#include <sstream>
#include <string>
#include <map>
#include <cstdlib>	// long atol(char*);
using namespace std;

namespace ua { namespace kiev { namespace ukma { namespace downloader {

WebResourceInfo::WebResourceInfo(const string& url, const int statusCode, istream* headers)
:_url(url), _statusCode(statusCode)
{
	if (_statusCode<1)
		return ;
	
	string param, value;
	int i=0;
	bool CRflag;
	while(!headers->eof())
	{
		if (MIME.size()==0)
		{	
			getline(*headers, value, ' ');
			MIME.insert( mimepair("HTTP Version", value) );

			getline(*headers, value, '\n');
			CRflag = value[value.length()-1]=='\r' ? true : false;
			if (CRflag) value.erase(value.length()-1);
			size_t pos = value.find(' ');
			string temp = value.substr(0,pos);
			MIME.insert( mimepair("Response Code", temp) );
			_statusCode = atoi(temp.c_str());
			if (pos!=string::npos)
			{
				temp = value.substr(pos+1);
				MIME.insert( mimepair("Response Message", temp) );
			}
		}
		else
		{
			getline(*headers, param, ':');
			headers->ignore();
			getline(*headers, value, '\n');
			if (CRflag) value.erase(value.length()-1);
			MIME.insert( mimepair(param,value) );
			if (headers->peek()== (CRflag ? '\r' : '\n'))
				headers->ignore(5); // 5 just in case, 3 is enough ([CR]+LF+EOF)
		}
	}
}


WebResourceInfo::WebResourceInfo(const WebResourceInfo& copy)
: _url(copy._url), _statusCode(copy._statusCode), MIME(copy.MIME)
{
	return ;
}


WebResourceInfo::~WebResourceInfo()
{
	return ;
}


const string WebResourceInfo::getUrl() const
{ 
	return _url;
}


const int WebResourceInfo::getStatusCode() const
{ 
	return _statusCode;
}


bool WebResourceInfo::isMimePresent(const string& key) const
{ 
	return MIME.count(key) ? true : false ;
}


const string WebResourceInfo::getMimeValue(const string& key) const
{ 
	return MIME.count(key) ? MIME.find(key)->second : string() ;
}


const string WebResourceInfo::getStatusCodeAsString() const
{
	switch(_statusCode)
	{
		case -1: return "Internal Error: coudln't perform connection";
		case  0: return "Couldn't Resolve Host Name"; 
		case  1: return "Infinite Redirection Loops";
		default: if(!isMimePresent("Response Message"))
						return "No Server Message Response";
				 else	return MIME.find("Response Message")->second;
	}
	return "This status message should never appear!";
}

//////////////////////////////////////////////////////
// ---------------------Iterator---------------------
//////////////////////////////////////////////////////

const WebResourceInfo::iterator WebResourceInfo::begin()
{	
	return WebResourceInfo::iterator::iterator(MIME.begin()); 
}
const WebResourceInfo::iterator WebResourceInfo::end()
{	
	return WebResourceInfo::iterator::iterator(MIME.end());
}

WebResourceInfo::iterator::iterator(){}
WebResourceInfo::iterator::iterator(const iterator& copy):_iter(copy._iter) {}
WebResourceInfo::iterator::iterator(const mimemap::iterator& iter): _iter(iter){}
WebResourceInfo::iterator::~iterator(){}
WebResourceInfo::iterator& WebResourceInfo::iterator::operator=(const iterator& copy) 
{ 
	_iter = copy._iter;
	return *this;
}
WebResourceInfo::iterator WebResourceInfo::iterator::operator ++()
{
	mimemap::iterator temp = _iter;
	++_iter;
	return iterator(temp);
}
WebResourceInfo::iterator& WebResourceInfo::iterator::operator ++(int)
{	
	++_iter;
	return *this;
}

bool WebResourceInfo::iterator::operator==(const iterator& iter) const
{	
	return _iter==iter._iter ? true : false ;	
}

bool WebResourceInfo::iterator::operator!=(const iterator& iter) const
{ 	
	return !(iter._iter==_iter);
}

WebResourceInfo::mimepair WebResourceInfo::iterator::operator*() const
{ 	
	return *_iter;
}



///////////////////////////////////////////////////////
//-------------- EXTERNAL FUNCTIONS -------------------
///////////////////////////////////////////////////////

const string encodeUrl(const string& url, const char charToEnc)
{
	string temp(url);
	ostringstream enc;
	enc<<"%"<<hex<<(int)charToEnc;
	size_t pos;
	while ((pos = temp.find(charToEnc))!=string::npos)
		temp.replace(pos, 1, enc.str());
	return temp;
}



const string getHostName(const WebResourceInfo& wri)
{
	const string& url = wri.getUrl();
	size_t pos = url.find("//");
	if (pos == string::npos)
			return url.substr(0, url.find('/'));
	return url.substr(pos+2, url.find('/', pos+2)-pos-2);
}


const string getHostName(const string& url)
{
	size_t pos = url.find("//");
	if (pos == string::npos)
			return url.substr(0, url.find('/'));
	return url.substr(pos+2, url.find('/', pos+2)-pos-2);
}


const string getResourceFileName(const WebResourceInfo& wri)
{
	const string& url = wri.getUrl();
	size_t pos = url.find("//");
	if (pos == string::npos)
			return url.rfind('/')!=string::npos ? url.substr(url.rfind('/')+1) : string() ;
	return url.substr(pos+2).rfind('/')!=string::npos ? url.substr(url.substr(pos+2).rfind('/')+pos+2+1) : string();
}


const string getResourceFileName(const string& url)
{
	size_t pos = url.find("//");
	if (pos == string::npos)
			return url.rfind('/')!=string::npos ? url.substr(url.rfind('/')+1) : string() ;
	return url.substr(pos+2).rfind('/')!=string::npos ? url.substr(url.substr(pos+2).rfind('/')+pos+2+1) : string();
}


const string getResourceDirs(const WebResourceInfo& wri)
{
	const string& dirs = wri.getUrl();
	size_t pos = dirs.find("//");
	if (pos==string::npos) 
			return dirs.substr(dirs.find('/')+1, dirs.rfind('/')-dirs.find('/'));
	return dirs.substr(dirs.find('/',pos+2)+1, dirs.rfind('/')-dirs.find('/',pos+2));
}


const string getResourceDirs(const string& url)
{
	const string& dirs = url;
	size_t pos = dirs.find("//");
	if (pos==string::npos) 
			return dirs.substr(dirs.find('/')+1, dirs.rfind('/')-dirs.find('/'));
	return dirs.substr(dirs.find('/',pos+2)+1, dirs.rfind('/')-dirs.find('/',pos+2));
}


const string getLocalFileName(const WebResourceInfo& wri)
{
	const string& name(getResourceFileName(wri));
//	const string& ext(getResourceExtension(wri));
	size_t pos = name.find('?');
//	name.replace(name.find('?'), 1, "-");	// '-' instead of '%3F'
	return (name.empty() || name[0]=='?' ? "index" : "")
			+  encodeUrl(name,'?')
			+ ( wri.getMimeValue("Content-Type").find("text/html") != string::npos &&
				name.find(".htm") == string::npos   ?   ".html" : "")
			;
}


const string getLocalFileName(const string& url)
{
	const string& name(getResourceFileName(url));
	size_t pos = name.find('?');
	return (name.empty() || name[0]=='?' ? "index" : "")
			+  encodeUrl(name,'?')
			+ (name.find(".htm") == string::npos   ?   ".html" : "")
			;
}


const string getResourceExtension(const WebResourceInfo& wri)
{
	const string& name = getResourceFileName(wri);
	size_t pos = name.find('.');
	if (pos==string::npos) return string();
	return name.substr(pos+1, name.find('?')-pos-1);
}


const string getResourceExtension(const string& url)
{
	const string& name = getResourceFileName(url);
	size_t pos = name.find('.');
	if (pos==string::npos) return string();
	return name.substr(pos+1, name.find('?')-pos-1);
}


const size_t getFileSize(const WebResourceInfo& wri)
{ 
	return wri.isMimePresent("Content-Length") ? atol(wri.getMimeValue("Content-Length").c_str()) : 0 ;
}


//////////////////////////////////////////////////////
// ---------------------Predicates--------------------
//////////////////////////////////////////////////////

bool isHostFound(const WebResourceInfo& wri)
{
	return wri.getStatusCode()>0 ? true : false ;
}


bool isUrlFound(const WebResourceInfo& wri)
{
	return wri.getStatusCode()>0 && wri.getStatusCode()!=404 ? true : false ;
}


bool canBeDownloaded(const WebResourceInfo& wri)
{
	return wri.getStatusCode()==200 || wri.getStatusCode()/100==3 ? true : false ;
}


}}}} // namespace ua::kiev::ukma::downloader