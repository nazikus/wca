#include "HttpManager.h"
#include "downloader/Downloader.h"
#include "WebResourceInfo.h"
#include "configurators/FileConfigurator.h"
#include <iostream>
using namespace ua::kiev::ukma::downloader;
using namespace ua::kiev::ukma::downloader::configurators;


void main(int argc, char * argv)
{
	try {
		// get configuration information
		IConfigurator *config = new FileConfigurator("config.txt");
		string url = config->getValue("URL");
		string depthString = config->getValue("DEPTH");
		if (depthString.empty()) throw exception("DEPTH is not present in the config file.");
		if (url.empty()) throw exception("URL is not present in the config file.");
		int depth = atoi(depthString.c_str());
		delete config;
		// run manager
		cout<<"Begin of the test of the HttpManager"<<endl;
		HttpManager* manager=new HttpManager(url,depth,"downloads\\");
		manager->run();
		cout<<"End of the test of the HttpManager"<<endl;  
		delete manager;
 }
 catch (exception& ex) {cout<<ex.what()<<endl;}
}