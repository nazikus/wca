#ifndef _WEBRESOURCEINFO_
#define _WEBRESOURCEINFO_

#include <istream>
#include <map>
#include <vector>
#include <string>
#include <functional>
using namespace std;

namespace ua { namespace kiev { namespace ukma { namespace downloader {

/**
Class which is something like a shell of STL map that contains general information
about the web resource retrieved by IDownloader.
By web resource we mean any kind of file (html, jpeg, gif, avi, mp3, etc.)
*/

class WebResourceInfo
{
	typedef map <string,string> mimemap;
	typedef pair<string,string> mimepair;

	int _statusCode;
	string _url;
	mimemap MIME;	

	WebResourceInfo();	/**< Not allowed implement default concstructor*/
	WebResourceInfo& operator=(const WebResourceInfo&);
public:

	class iterator;				/**< WebresourceInfo iterator that acts like STL map iterator*/
	const iterator begin();		
	const iterator end();
	
	/**
	Constructor creates an associative array containing MIME headers and its values
	are read from any kind of input stream. The content of input stream MUST correspond
	to HTTP header format standart: every line ends up with CRLF symbols, and last
	line MUST be the empty string (CRLF), MIME headers and values are delimited with
	':' symbol.
	@param string representing url where the needed web resource is located
	@param integer value of response staus code
	@param pointer to input stream, from which the MIME headers are read. The 
	pointer's value can be 0, which means the host name was not resolved or
	connection performance failed.
	*/
	WebResourceInfo(const string& url, const int statusCode, istream* headers);
	/// Regular copy constructor
	WebResourceInfo(const WebResourceInfo&);
	/// Empty destructor (since class doesn't make memory allocation)
	virtual ~WebResourceInfo();
	
	/**
	Method which returns the URL of the current web resource
	@return A constant string value which represents URL
	*/
	const string getUrl() const;

	/**
	Method which returns the status code of the web resource. Status code
	SHOULD correspond to one of the standart HTTP response codes. In other
	case (ex. "Couldn't Resolve Host Name"),  a diffirent value is assigned
	to the status code:
	-1 - Peromance Error
	 0 - Couldn't Resolve Host Name
	 1 - Infinite Redirection Loops
	Status code corresponding to the 3xx mask (except 304-306) or 200 is
	considered fine to be downloaded.
	@return Integer value of status code
	*/
	const int getStatusCode() const;
	
	/**
	Predicate which defines whether the input MIME header is present in the web resource information
	@param key which will be checked whether it is a MIME Header that is present in the web resource information
	@return true if key is present MIME header, false in other case
	*/
	bool  isMimePresent(const string& key) const;

	/**
	Method retrieves value of MIME Header
	@param key which SHOULD be a MIME Header.  CAUTION: case sensitive
	@return value of input MIME header, if MIME not found - empty string is returned
	*/
	const string getMimeValue(const string& key) const;
	
	/**
	Method forms a human readable message based on web resource status code
	@return string description of the status code
	*/
	const string getStatusCodeAsString() const;
};



//////////////////////////////////////////////////////
// ---------------------Iterator---------------------
//////////////////////////////////////////////////////

class WebResourceInfo::iterator
{
	// mimemap == map<string,string>
	// mimepair==pair<string,string>
	WebResourceInfo::mimemap::iterator _iter;
public:
	iterator();
	iterator(const iterator&);
	iterator(const mimemap::iterator&);
	~iterator();
	iterator& operator=(const iterator&);
	iterator  operator++();
	iterator& operator++(int);
	bool operator==(const iterator&) const;
	bool operator!=(const iterator&) const;
	WebResourceInfo::mimepair operator*() const;
};


///////////////////////////////////////////////////////
//-------------- EXTERNAL FUNCTIONS -------------------
///////////////////////////////////////////////////////

/**
Function which replaces specified char with string representation of 
it's ASCII code corresponding to URL format ("%XX" where X is a
hexadecimal digit).
@param URL which is needed to be encoded
@param chararacter that is needed to be encoded
@param string representation of encoded URL
*/
const string encodeUrl(const string& url, const char charToEnc = ' ');


/**
Function retrieves hostname of the web resource URL
@param web resource which hostname is needed
@return string representation of host name
*/
const string getHostName(const WebResourceInfo&);
const string getHostName(const string&);

/**
Function retrieves file name of the web resource
@param web resource which filename is needed
@return string representation of web resource filename
*/
const string getResourceFileName(const WebResourceInfo&);
const string getResourceFileName(const string&);


/**
Function retrieves the extension web resource filename
@param web resource info which filename's extension is needed
@return string representation of filename extension
*/
const string getResourceExtension(const WebResourceInfo&);
const string getResourceExtension(const string&);

/**
Function retrieves the directory path of web resource file on host machine
@param web resource which directory path is needed
@return string representation of directory path
*/
const string getResourceDirs(const WebResourceInfo&);
const string getResourceDirs(const string&);


/**
Function retrieves the local filename of web resource (if downloaded).
If URL of web resource is a script, filename contains all the parameters of
script as it is in URL and question mark symbol ('?') is replaced with it's 
ASCII code (corresponding to URL format: %XX, where X is a hexadecimal digit),
since it is not allowed a local filename to contain '?'.
@pararm web resource which filename after downloading is needed
@return string representation of local filename
*/
const string getLocalFileName(const WebResourceInfo&);
const string getLocalFileName(const string&);


/**
Method converts value of web resource "Conten-Length" MIME header to size type
@param web resource which size is needed
@return size of the web resource, if "Content-Length" MIME header is absent 0 is returned
*/
const size_t getFileSize(const WebResourceInfo&);


//////////////////////////////////////////////////////
// ---------------------Predicates--------------------
//////////////////////////////////////////////////////

/**
Predicate defines whether host name of the web resource was successfully resolved
@return true is host name was resolved, false in other case
*/
bool isHostFound(const WebResourceInfo&);

/**
Predicate defines whether the specified file of web resource was found on the given host
@return true if file was found on the host, false in other case
*/
bool isUrlFound(const WebResourceInfo&);

/**
Predicate defines wheter the server response allows web resource to be downloaded
@return true if it is fine to download, false in other case
*/
bool canBeDownloaded(const WebResourceInfo&);

}}}} // namespace ua::kiev::ukma::downloader
#endif
