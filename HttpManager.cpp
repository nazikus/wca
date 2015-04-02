#include "HttpManager.h"

#include "downloader/Downloader.h"
#include "WebResourceInfo.h"
#include "LocalResourceInfo.h"
#include "registers/FileRegistry.h"
#include "UrlLocalResourceKey.h"
#include "parsers/RegexpParser.h"
#include "ILocalResourceKey.h"
#include "UrlLocalResourceKey.h"

#include <fstream>
#include <algorithm>
#include <string>
#include <deque>
#include <time.h>
#include <iostream>

namespace ua { namespace kiev { namespace ukma { namespace downloader {

HttpManager::HttpManager(const string link, int maxDeep, const string localDir):link(link), maxDeep(maxDeep), localDir(localDir)
{
	init();
}

HttpManager::HttpManager(const string link, int maxDeep, const string localDir, const vector<IValidator*>& validators): link(link), maxDeep(maxDeep), localDir(localDir), validators(validators)
{	
	init();
}

void HttpManager::init()
{
	//add '\' to the end if it doesn't exist
	if(localDir!="" && localDir.rfind("\\")!=localDir.length()-1)localDir=localDir+"\\";
	downloader=new downloaders::Downloader();
	parser=new parsers::RegexpParser();
	// Here we simulate SmartPtr - Registry will delete UrlLocalResourceKey
	registry=new registers::FileRegistry("downloader.reg",new UrlLocalResourceKey());	
}

HttpManager::~HttpManager()
{	
	delete parser;
	delete registry;
	delete downloader;
	// Now keygen is deleted within FileRegistry
	//delete keyGen;
}


HttpManager::HttpManager(const HttpManager& T) { }

void HttpManager::operator=(HttpManager T) { }

void HttpManager::run()
{
	unsigned int i;
	deque<pair<string,int> > linksQueue;  	//queue that is used for BFS exploring
	// We create another instance of UrlLocalResourceKey
	UrlLocalResourceKey * keygen = new UrlLocalResourceKey();
	
	linksQueue.push_back(make_pair(link,1));
	while(!linksQueue.empty())
	{
		string url=linksQueue[0].first;
		int currentDeep=linksQueue[0].second;
		linksQueue.pop_front();
				
		cout<<"Deep of search:"<<currentDeep<<" trying to get "<<url<<endl;

		WebResourceInfo webResource=downloader->getWebResourceInfo(url);
		
		//call all the validators and if not valid skip this resource
		bool valid=true;		
		for(i=0;i<validators.size();i++)valid=valid && validators[i]->isValid(webResource);
		if(!valid)
		{
			cout<<"But validators say not to download!"<<endl;
			continue;
		}

		// oldbam
		LocalResourceInfo storedLocalResource = registry->getRecord(url);
		if (storedLocalResource.getUrl() == webResource.getUrl()) {
			cout<<"INFO:"<<"Resource exists in the registry"<<endl;
			cout<<"URL:"<<storedLocalResource.getUrl()<<endl;
			cout<<"DATE:"<<storedLocalResource.getDate()<<endl;
			cout<<"LOCALPATH:"<<storedLocalResource.getLocalPath()<<endl;
			continue;
		}
		// end oldbam

		string hostName=getHostName(webResource);
		//virtual path of the resource on the server
		string resourceHostPath=getResourceDirs(webResource);
		//change last '/' to '\'
		if(resourceHostPath!="")
			resourceHostPath[resourceHostPath.length()-1]='\\';

		//local resource's path
		string localResourceDir=localDir+hostName+"\\"+resourceHostPath;
		
		//full resource's local file name(path + name)
		string fullLocalFileName=localResourceDir+getLocalFileName(webResource);
		
		
		downloader->makeDir(localResourceDir);
		bool result = downloader->download(webResource,localResourceDir);
		if (result == true) cout<<"Ok. Placed to: "<<fullLocalFileName<<endl;
		else cout<<"ERROR : Downloader returned 'false' after download."<<endl;

		//create and register LocalResource
		char timeChar [19];
        _strdate( timeChar );
		timeChar[8]='#';
		_strtime( timeChar+9 );					
		LocalResourceInfo localResource(webResource.getUrl(),(string)timeChar,fullLocalFileName);
		registry->addRecord(keygen->getKey(localResource),localResource);

		//parse and add new links to the queue
		if(webResource.getMimeValue("Content-Type").find("text/html")!=string::npos && currentDeep<maxDeep)
		{
			string content,tmp;
			ifstream file(fullLocalFileName.c_str());
			while (getline(file, tmp)) 
			{
				content += tmp;
			}
			content = encodeUrl(content, ' ');
			vector<string> links=parser->getLinks(content);
			
			//deleting duplicates
			sort(links.begin(),links.end());
			links.erase(unique(links.begin(),links.end()),links.end());						
			parser->relative2Absolute(links,getHostName(webResource)+"/"+getResourceDirs(webResource));

			// modified by oldbam, add cout for links
			cout<<"INFO : New links are found by manager:"<<endl;
			for(i=0;i<links.size();i++)
			{
				linksQueue.push_back(make_pair(links[i],currentDeep+1));
				cout<<"LINK : "<<links[i]<<endl<<"DEPTH : "<<currentDeep+1<<endl;
			}
			cout<<endl;
			// end modified by oldbam
		}
		cout<<endl;
	}
	delete keygen;
}

}}}}