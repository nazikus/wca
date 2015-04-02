#include "FileRegistry.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
using namespace std;

namespace ua { namespace kiev { namespace ukma { namespace downloader { namespace registers {

	FileRegistry::FileRegistry(const string& registryFile, ILocalResourceKey *keygen) : _registryFile(registryFile), _keygen(keygen)
	{
		// check if _registryFile is not empty string
		if (_registryFile=="") throw exception("_registryFile should not be empty string");
		ifstream in;
		in.open(_registryFile.c_str());
		if (!in.is_open()) 
		{
			string message = "The specified file : " + _registryFile + " does not exist";
			throw FileNotFoundException(message);
		}
		// read values and add them to the map
		string s = "";
		string url = "";
		string date = "";
		string localPath = "";
		string key = "";
		while (in>>url>>date>>localPath)
		{
#ifndef NDEBUG
		//	cout<<url<<" "<<date<<" "<<localPath<<endl;
#endif
			LocalResourceInfo info(url, date, localPath);
			key = keygen->getKey(info);
#ifndef NDEBUG
		//	cout<<key<<endl;
#endif
			data[key]=info;
		}
		in.close();
#ifndef NDEBUG
	//	cout<<"Number of added elements : "<<data.size()<<endl;
#endif
	}

	FileRegistry::~FileRegistry()
	{
#ifndef NDEBUG
	//	cout<<"Number of elements to write to the file : "<<data.size()<< " to file "<<_registryFile<<endl;
#endif
		ofstream out(_registryFile.c_str());
		map<string, LocalResourceInfo>::iterator iter;
		try {
            for (iter = data.begin(); iter != data.end(); iter++)
			{
				LocalResourceInfo info = iter->second;
#ifndef NDEBUG
	//		cout<<info.getUrl()<<" "<<info.getDate()<<" "<<info.getLocalPath()<<endl;
#endif
				out<<info.getUrl()<<" "<<info.getDate()<<" "<<info.getLocalPath()<<endl;
			}
			out.close();
		} catch (exception& ex) {cout<<"ERROR : "<<ex.what()<<endl;}
		// ATTENTION : We delete ILocalResourceKey 
		delete _keygen;
	}

	bool FileRegistry::exist(const string& key) const
	{
#ifndef NDEBUG 
	//	cout<<key<<endl;
#endif
		return (data.find(key)!=data.end())?
			true:false;
	}

	bool FileRegistry::addRecord(const string& key, LocalResourceInfo& resource)
	{
		if (exist(key)==true) return false;
		else 
		{
			data[key]=LocalResourceInfo(resource);
            return true;
		}
	}

	bool FileRegistry::updateRecord(const string& key, LocalResourceInfo& resource)
	{
		if (exist(key)==false) return false;
		else
		{
			data[key]=LocalResourceInfo(resource);
			return true;
		}
	}

	bool FileRegistry::removeRecord(const string& key)
	{
		if (exist(key)==false) return false;
		else
		{
			data.erase(key);
			return true;
		}
	}

	LocalResourceInfo FileRegistry::getRecord(const string& key)
	{
		if (exist(key)==false) return LocalResourceInfo();
		return data[key];
	}



}}}}}