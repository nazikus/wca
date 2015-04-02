#include "..\IRegistry.h"
#include "..\LocalResourceInfo.h"
#include "..\ILocalResourceKey.h"
#include "..\UrlLocalResourceKey.h"
#include "FileRegistry.h"

#include <iostream>
#include <fstream>
#include <exception>
#include <cassert>
using namespace std;

void printFile(int testNum)
{
	//ifstream in("C:\\registry.txt");
	//string s;
	//cout<<"Test #"<<testNum<<endl;
	//while(getline(in,s)) cout<<s<<endl;
	//cout<<"*****"<<endl;
	//in.close();
}
/*
void main()
{
	using namespace ua::kiev::ukma::downloader;
	using namespace ua::kiev::ukma::downloader::registers;
	UrlLocalResourceKey keygen;
	try{
		// Create new file
		ofstream in("C:\\registry.txt");
		in.close();
		// 0. Do nothing
		{
            FileRegistry registry((string)"C:\\registry.txt", keygen);
			printFile(0);
		}
		// 1. Add one element
		{
            FileRegistry registry((string)"C:\\registry.txt", keygen);
			bool r1 = registry.addRecord((string)"url-1", LocalResourceInfo((string)"url-1", (string)"data-1", (string)"path-1"));
			assert(r1==true);
			printFile(1);
		}
		// 2. Assetr that the first element exists and add two other elements
		{
            FileRegistry registry((string)"C:\\registry.txt", keygen);
			bool r0 = registry.exist((string)"url-1");
			assert(r0==true);
			bool r1 = registry.addRecord((string)"url-2", LocalResourceInfo((string)"url-2", (string)"data-2", (string)"path-2"));
			bool r2 = registry.addRecord((string)"url-3", LocalResourceInfo((string)"url-3", (string)"data-3", (string)"path-3"));
			assert(r1==true);
			assert(r2==true);
			printFile(2);
		}
		// 3. Try to add existing element
		{
			FileRegistry registry((string)"C:\\registry.txt", keygen);
			bool result = registry.addRecord((string)"url-1", LocalResourceInfo((string)"url-1", (string)"data-1", (string)"path-1"));
			assert(result==false);
			printFile(3);
		}
		// 4. Try to delete existing element
		{
			FileRegistry registry((string)"C:\\registry.txt", keygen);
			bool r1 = registry.removeRecord((string)"url-2");
			assert(r1==true);
			printFile(4);
		}
		// 5. Try to delete non-existing element
		{
			FileRegistry registry((string)"C:\\registry.txt", keygen);
			bool r1 = registry.removeRecord((string)"2345");
			assert(r1==false);
			printFile(5);
		}

		// 6. Try to update existing element
		{
			FileRegistry registry((string)"C:\\registry.txt", keygen);
			bool r1 = registry.updateRecord((string)"url-3", LocalResourceInfo((string)"new-url-3", (string)"new-data-3", (string)"new-path-3"));
			assert(r1==true);
			printFile(6);
		}
		// 7. Try to update non-existing element
		{
			FileRegistry registry((string)"C:\\registry.txt", keygen);
			bool r1 = registry.updateRecord((string)"23456", LocalResourceInfo((string)"new-url-3", (string)"new-data-3", (string)"new-path-3"));
			assert(r1==false);
			printFile(7);
		}
	}
	catch (exception& c)
	{
		cout << c.what() <<endl;
	}

}
*/