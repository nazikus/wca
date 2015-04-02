#include "Downloader.h"
#include "../WebResourceInfo.h"
//#include "../mydebug.h"    // ---------------DEBUG-----------------

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>	// int system(char*);
#include <curl/curl.h>
using namespace std;

namespace ua { namespace kiev { namespace ukma { namespace downloader { namespace downloaders {


Downloader::Downloader(){}
Downloader::~Downloader(){}

WebResourceInfo Downloader::getWebResourceInfo(const string& url)
{
	const int max_redirections = 5;
	string redUrl(url);  //for assigning redirection url
	for (int i=0; i<max_redirections; ++i)
	{
		CURL *curl = curl_easy_init(); 
		if (curl==0)
			return WebResourceInfo(redUrl, -1, 0);
	
#ifdef VERBOSE
curl_easy_setopt(curl, CURLOPT_VERBOSE, true);
#endif
		const string& encUrl = encodeUrl(redUrl);
		stringstream strheader;

		curl_easy_setopt(curl, CURLOPT_URL, encUrl.c_str());
		curl_easy_setopt(curl, CURLOPT_NOBODY, true);
		curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEHEADER, &strheader);

		CURLcode curlResCode = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
#ifdef RESPONSE
cout<<"ResCode="<<(long)curlResCode<<endl<<curl_easy_strerror(curlResCode)<<endl;
#endif

		if (curlResCode==CURLE_COULDNT_RESOLVE_HOST)
			return WebResourceInfo(redUrl,0,0);
		WebResourceInfo wri(redUrl, 1, (istream*)&strheader);
		if (wri.getStatusCode()/100==3)	//if status == 3xx
		{
			redUrl = wri.getMimeValue("Location");
			continue;
		}
		return wri;
	}
	return WebResourceInfo(url, 1, 0);
}

bool Downloader::download(const WebResourceInfo& resource, const string& localpath)
{
	CURL *curl = curl_easy_init(); 
	if (curl==0 || !canBeDownloaded(resource))
		return false;
	
	const string& filename = localpath + getLocalFileName(resource);
	ofstream fout(filename.c_str(), ios_base::out | ios_base::binary);
	if (!fout.is_open()) return false;

	const string& encUrl = encodeUrl(resource.getUrl());
	curl_easy_setopt(curl, CURLOPT_URL, encUrl.c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &fout);
#ifdef VERBOSE
	curl_easy_setopt(curl, CURLOPT_VERBOSE, true);
#endif
	CURLcode curlResCode = curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	fout.close();

#ifdef RESPONSE
	cout<<"ResCode="<<(long)curlResCode<<endl<<curl_easy_strerror(curlResCode)<<endl;
#endif
	return curlResCode==CURLE_OK ? true : false ;
}


size_t Downloader::write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
	((ostream*)stream)->write((char*)ptr, size*nmemb);
	return size*nmemb;
}


bool Downloader::makeDir(string dir)
{
	const char* tempfile = "_$_!_$_";
	size_t pos;
	while( (pos=dir.find('/')) != string::npos)
		dir.replace(pos,1,"\\");
	
	fstream check((dir+tempfile).c_str(), ios_base::out);
	/// if such dir exists
	if (check.is_open())
	{ 
		check.close();
		system(("DEL \"" + dir + tempfile + '\"').c_str());
		return true;
	}
	/// if such file exists
	check.open(dir.substr(0, dir.length()-1).c_str(), ios_base::in | ios_base::binary);
	if (check.is_open())
	{
		check.close();
		return false;
	}
	return system(("MKDIR \"" + dir + '\"').c_str()) ? false : true ;
}

}}}}} // namespace ua::kiev::ukma::downloader::downloaders