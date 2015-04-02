#ifndef _IREGISTRY_
#define _IREGISTRY_

#include "LocalResourceInfo.h"
#include "ILocalResourceKey.h"

namespace ua { namespace kiev { namespace ukma { namespace downloader {

/**
This is the interface which defines a contract for working with pluggable data store.
*/
class IRegistry
{
public:
	/**
	A method to add LocalResourceInfo identified by the given string key to the registry.
	This method should first check if the given key already exists in the registry.
	@param key LocalResourceInfo identification string
	@param resource LocalResourceInfo to add
	@return true if resource was added, false if the given key already exists.
	*/
	virtual bool addRecord(const string& key, LocalResourceInfo& resource) = 0;
	/**
	A method to add LocalResourceInfo identified by the given string key to the registry.
	This method should first check if the given key already exists in the registry.
	@param key ILocalResourceKey for key generation
	@param resource LocalResourceInfo to add
	@return true if resource was added, false if the given key already exists.
	*/
	virtual bool addRecord(ILocalResourceKey* key, LocalResourceInfo& resource);	
	/**
	A method to  update LocalResourceInfo identified by the given string key to the new instance.
	This method should return false, if the given key doesn't exist in the registry.
	@param key LocalResourceInfo identification string
	@param resource LocalResourceInfo to update
	@return true if resource was updated, false if resource with the given key do not exist.
	*/
	virtual bool updateRecord(const string& key, LocalResourceInfo& resource) = 0;
	/**
	A method to  remove LocalResourceInfo identified by the given string key from the registry
	This method should return false, if the given key doesn't exist in the registry.
	@param key LocalResourceInfo identification string
	@return true if resource was deleted, false if resource with the given key do not exist.
	*/
	virtual bool removeRecord(const string& key) = 0;
	/**
	A method to obtain a copy of LocalResourceInfo identified by the given string key from the registry
	@param key LocalResourceInfo identification string
	@return copy of LocalResourceInfo from the registry
	*/
	virtual LocalResourceInfo getRecord(const string& key) = 0;
	/**
	A method to check whether LocalResourceInfo identified by the given string key exists in the registry
	@param key LocalResourceInfo identification string
	@return true, if instance under such a name exists, false otherwise
	*/
	virtual bool exist(const string& key) const = 0;
	/**
	Destructor
	*/
	virtual ~IRegistry() {}
};

}}}}

#endif