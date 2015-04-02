#ifndef _FILEREGISTRY_
#define _FILEREGISTRY_

#include "..\IRegistry.h"
#include "..\ILocalResourceKey.h"
#include "..\FileNotFoundException.h"
#include <string>
#include <map>
using namespace std;

namespace ua { namespace kiev { namespace ukma { namespace downloader { namespace registers {

/**
This is an implementation, which stores information in memory during programm execution and performs reading from the file, when programm starts and writes data to the file, when the programm ends.
@todo This implementation requires huge memory expenses. Database should be used instead.
*/
class FileRegistry : public IRegistry
{
public:
	/** 
	Constructor. Reads information from registry file to the memory.
	@param registryFile File to read information from
	@param keygen Implementation of ILocalResourceKey, that will generate identification key for LocalResourceInfo.
	*/
	FileRegistry(const string& registryFile, ILocalResourceKey *keygen);
	/**
	Destructor. Writes information to the file.
	*/
	~FileRegistry();
	/**
	A method to add LocalResourceInfo identified by the given string key to the registry.
	@param key LocalResourceInfo identification string
	@param resource LocalResourceInfo to add
	@return true if resource was added, false if the geven key already exists.
	*/
	virtual bool addRecord(const string& key, LocalResourceInfo& resource);
	/**
	A method to  update LocalResourceInfo identified by the given string key to the new instance
	@param key LocalResourceInfo identification string
	@param resource LocalResourceInfo to update
	@return true if resource was updated, false if resource with the given key do not exist.
	*/
	virtual bool updateRecord(const string& key, LocalResourceInfo& resource);
	/**
	A method to  remove LocalResourceInfo identified by the given string key from the registry
	@param key LocalResourceInfo identification string
	@return true if resource was deleted, false if resource with the given key do not exist.
	*/
	virtual bool removeRecord(const string& key);
	/**
	A method to obtain a copy of LocalResourceInfo identified by the given string key from the registry
	@param key LocalResourceInfo identification string
	@return copy of LocalResourceInfo from the registry
	*/
	virtual LocalResourceInfo getRecord(const string& key);
	/**
	A method to check whether LocalResourceInfo identified by the given string key exists in the registry
	@param key LocalResourceInfo identification string
	@return true, if instance under such a name exists, false otherwise
	*/
	virtual bool exist(const string& key) const;
private:
	FileRegistry(FileRegistry&);
	FileRegistry& operator= (FileRegistry&);
	string _registryFile;
	// _keygen will be destroyed in ~ctor
	ILocalResourceKey *_keygen;
	map<string,LocalResourceInfo> data;
};

}}}}}

#endif