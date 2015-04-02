#include "..\..\IParser.h"
#include "..\RegexpParser.h"
#include <iostream>
#include <sstream>
#include <boostdefines.hpp>
#include <boost/algorithm/string_regex.hpp>
#define BOOST_ALL_DYN_LINK

using namespace ua::kiev::ukma::downloader;
using namespace ua::kiev::ukma::downloader::parsers;

vector<string> links;
IParser* p=new RegexpParser();
static int failTests=0;

void test(int testNumber, const string& inputString, const vector<string>& answer)
{
	unsigned int i;
	bool fail=false;
	links=p->getLinks(inputString);
	if(links.size()!=answer.size())fail=true;
	else
	{		
		for(i=0;i<links.size();i++)if(links[i]!=answer[i])break;
		if(i<links.size())fail=true;
	}
	cout<<"TestId:"<<testNumber<<endl<<" input:"<<inputString<<endl<<" output:";
	for(i=0;i<links.size();i++)cout<<links[i]<<";";
	cout<<endl;
	if(fail)
	{
		failTests++; cout<<"FAIL"<<endl;
		cout<<"answer:";
		for(i=0;i<answer.size();i++)cout<<answer[i]<<";";
		cout<<endl;
	}else cout<<"PASS"<<endl;
	cout<<"-----------------------------------------------------"<<endl;	
}

/*
void main()
{		
	vector<string> answer;
		
	string test1[]={"dsf"};
	test(1,"src='dsf'",vector<string>(test1,test1+sizeof(test1)/sizeof(test1[0])));
	string test2[]={"www.dsf.ru"};
	test(2,"src=\"www.dsf.ru\"",vector<string>(test2,test2+sizeof(test2)/sizeof(test2[0])));
	string test3[]={"ds.ccdcf"};
	test(3,"src='ds.ccdcf'",vector<string>(test3,test3+sizeof(test3)/sizeof(test3[0])));
	string test4[]={"ds.f"};
	test(4,"src='ds.f'",vector<string>(test4,test4+sizeof(test4)/sizeof(test4[0])));
	string test5[]={"ds.f"};
	test(5,"src=\"ds.f\"ffgh",vector<string>(test5,test5+sizeof(test5)/sizeof(test5[0])));
	string test6[]={"dsf.rdsf.ro/~rfe/sdf/fdsf_sdf.lsd"};
	test(6,"src='dsf.rdsf.ro/~rfe/sdf/fdsf_sdf.lsd'<",vector<string>(test6,test6+sizeof(test6)/sizeof(test6[0])));
	string test7[]={"dsf.rdsf.ro/~rfe/sdf/fdsf_sdf.lsd"};
	test(7,"src='dsf.rdsf.ro/~rfe/sdf/fdsf_sdf.lsd' <",vector<string>(test7,test7+sizeof(test7)/sizeof(test7[0])));
	string test8[]={"dsf"};
	test(8,"src=dsf",vector<string>(test8,test8+sizeof(test8)/sizeof(test8[0])));

	string test9[]={"ds.f","ffgh"};
	test(9,"src=\"ds.f\" href=ffgh",vector<string>(test9,test9+sizeof(test9)/sizeof(test9[0])));
	string test10[]={"dsf.rdsf.ro/~rfe/sdf/fdsf_sdf.lsd"};
	test(10,"dsfg dfg|src='dsf.rdsf.ro/~rfe/sdf/fdsf_sdf.lsd' action=\"ghfg.fgh!~_ghgf$%#^&*\"<",vector<string>(test10,test10+sizeof(test10)/sizeof(test10[0])));
	string test11[]={"dsf.rdsf.ro/~rfe/sdf/fdsf_sdf.lsd"};
	test(11,"asdfsdf src='dsf.rdsf.ro/~rfe/sdf/fdsf_sdf.lsd' <src=",vector<string>(test11,test11+sizeof(test11)/sizeof(test11[0])));
	string test12[]={"dsf"};
	test(12,"src=\"dsf action='",vector<string>(test12,test12+sizeof(test12)/sizeof(test12[0])));
	string test13[]={"dsf"};
	test(13,"src=dsf' href='",vector<string>(test13,test13+sizeof(test13)/sizeof(test13[0])));


	string test20[]={"http://"};
	test(20,"href=\"http://'dsf'\"",vector<string>(test20,test20+sizeof(test20)/sizeof(test20[0])));
	string test21[]={"http//dsf.fsd.sdf/~dasf/sdf.sf"};
	test(21,"href='http//dsf.fsd.sdf/~dasf/sdf.sf'",vector<string>(test21,test21+sizeof(test21)/sizeof(test21[0])));
	string test23[]={"http//dsf.fsd.sdf/~da"};
	test(23,"href=' href='http//dsf.fsd.sdf/~da''",vector<string>(test23,test23+sizeof(test23)/sizeof(test23[0])));	

	//!!! BUGGY thing: !!!
	string test24[]={"http//dsf.fsd.sdf/~da"};
	test(24,"href='src='http//dsf.fsd.sdf/~da''",vector<string>(test24,test24+sizeof(test24)/sizeof(test24[0])));

	string test41[]={"nighshif.txt_Contents"};
	test(41,"HREF=nighshif.txt_Contents'",vector<string>(test41,test41+sizeof(test41)/sizeof(test41[0])));
	
	if(!failTests)cout<<"PASS ALL"; else cout<<"FAIL:"<<failTests;
	cout<<endl;
}
*/