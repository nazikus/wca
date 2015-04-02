#include "../FileConfigurator.h"
#include <assert.h>
#include <exception>
#include <iostream>
using namespace std;
using namespace ua::kiev::ukma::downloader;
using namespace ua::kiev::ukma::downloader::configurators;

class FileConfiguratorTest : FileConfigurator
{
public:
	static void test()
	{
		int passed = 0;
		try {
			// 1. Testing trim
			assert(trim("")==""); 
			assert(trim("          ")==""); 
			assert(trim(" a ")=="a");
			assert(trim("a")!="b"); 
			assert(trim("a")!=trim("b")); 
			assert(trim("string")=="string");
			assert(trim(" string")=="string");
			assert(trim("string ")=="string");
			assert(trim(" string ")=="string");
			assert(trim("            string            ")=="string");
			passed++;
			// 2. Testing constructor
			// 2.1 Testing constructor with empty string
			try {
				FileConfigurator fc1("");
				throw exception("FileNotFoundException was not thrown");
			}
			catch (exception&)
			{
				passed++;
			}
			// 2.2 Testing constructor with not-existing file
			try {
				FileConfigurator fc1("asdf");
				throw exception("FileNotFoundException was not thrown");
			}
			catch (FileNotFoundException&)
			{
				passed++;
			}
			// 2.3 Testing constructor with existing file from the same directory
			FileConfigurator fc2("config.txt");
			passed++;
			// 2.4 Testing constructor with not-existing file with some path
			try {
				FileConfigurator fc1("c:\\asdf");
				throw exception("FileNotFoundException was not thrown");
			}
			catch (FileNotFoundException&)
			{
				passed++;
			}
			// 2.5 Testing constructor with existing file with some path
			FileConfigurator fc3("c:\\config.txt");
			passed++;
			// 3. Testing how values are read
			FileConfigurator fc4("config.txt");
			string empty = "";
			assert(fc4.getValue("key0")==empty);
			assert(fc4.getValue("key1")==empty);
			assert(fc4.getValue("key2")==empty);
			assert(fc4.getValue("key3")==empty);
			assert(fc4.getValue("key4")==empty);
			assert(fc4.getValue("key5")==string("value5"));
			assert(fc4.getValue("key6")==string("value6"));
			assert(fc4.getValue("key7")==string("value7"));
			passed++;
			// END TEST
			cout<<"Passed tests: "<<passed<<endl;
		}
		catch(std::exception e)
		{
			cout<<e.what()<<endl; 
		}
	}
};
/*
void main()
{
	FileConfiguratorTest::test();
}
*/