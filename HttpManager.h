#ifndef _HTTP_MANAGER_
#define _HTTP_MANAGER_

#include "IDownloader.h"
#include "IValidator.h"
#include "IRegistry.h"
#include "IParser.h"
#include "ILocalResourceKey.h"

#include <string>
#include <vector>
using namespace std;

namespace ua { namespace kiev { namespace ukma { namespace downloader { 
//This is the main class of the http downloading
class HttpManager
{
private:
	const string link;			//initial link
	int maxDeep;				//deep of exploring
	string localDir;			//where resourses should be saved
	IDownloader* downloader;	//for downloading  resources
	IRegistry* registry;		//for registering local resources on the PC
	// Do not store it now - oldbam
	//ILocalResourceKey* keyGen;  //for primary key generation
	IParser* parser;			//parser to use for links retrieving
	vector<IValidator*> validators; //validators which denote whether it is worth to download the link
	
	/**
	Constructor's helper
	*/
	void init();
	
	/**
	Disable copy constructor and operator=
	*/
	
	void operator=(HttpManager);	
	HttpManager(const HttpManager&);	
public:
	/**
	Constructor with parameters
	@param link where exploring is started
	@param deep of the link-exploring
	@param localDir local place to save downloaded files
	*/
	HttpManager(const string link, int deep, const string localDir);

	/**
	Constructor with parameters
	@param link where exploring is started
	@param deep of the link-exploring
	@param localDir local place to save downloaded files
	@param validators which denote whether it is worth to download the link
	*/
	HttpManager(const string link, int deep, const string localDir, const vector<IValidator*>& validators);

	/**
	Destructor. It is very important to call it after all =). Because it is not only memory leak, but wrong work of the Registry
	*/
	~HttpManager();

	/**
	Run the retrieving process
	1) while queue is not empty
	2) take url from it
	3) IDownloader#getWebResourceInfo(string url)
	4) for every WebResourceInfo call isValid(WebResourceInfo) from the validators array
	5) if valid IDownloader#download(WebResourceInfo, string localpath)
	6) if WebResource is html and deep is not reached then Parser#Parse and pushback all the links to thequeue 
	*/
	void run();
};

}}}}
#endif