// \/ updated by Nazar G.
#include "../WebResourceInfo.h"

// /\ updated by Nazar G.

#include "RegexpParser.h"
#include <string>
#include <sstream>
#include <iostream>
#include <boostdefines.hpp>
#include <boost/algorithm/string/regex.hpp>
#define BOOST_ALL_DYN_LINK
using namespace boost;

namespace ua { namespace kiev { namespace ukma { namespace downloader { namespace parsers {

RegexpParser::RegexpParser()
{}

vector<string> RegexpParser::getLinks(const string resource)
{
	unsigned int i;
	vector<string> allLinks;
	boost::regex pattern("(href|src)=['\"]?([^ \n\r\t'\">]+)([ '\"\t\n\r>]|$)",boost::regex::icase);
	string tmp="['\"]?([^ '\"\n\t\r>]*)[ '\"\n\t\r>]?";

	//pattern.set_expression("(href|src|HREF|SRC|Href|Src)=['\"]?([^ \n\r\t'\">]+)([ '\"\t\n\r>]|$)");
	
	boost::find_all_regex(allLinks,resource,pattern);

	//delete reduntant substrings
	for(i=0;i<allLinks.size();i++)
	{
		string temp;
		ostringstream sout;		
		std::ostream_iterator<char> out (sout);
		regex_replace(back_inserter(temp), allLinks[i].begin(), allLinks[i].end(), 
			regex("(href="+tmp+")|(src="+tmp+")",boost::regex::icase), 
			"(?1$2)(?3$4)", boost::match_default | boost::format_all);
		allLinks[i]=temp;
	}
	return allLinks;
}

vector<string> RegexpParser::getLinks(const string resource, const vector<string> patterns)
{
	unsigned int i;
	vector<string> allLinks,temp;
	boost::basic_regex<char> pattern;
	for(i=0;i<patterns.size();i++)
	{
		pattern.set_expression(patterns[i]);
		boost::find_all_regex(temp,resource,pattern);
		allLinks.insert(allLinks.end(),temp.begin(),temp.end());
	}	
	return allLinks;
}

bool RegexpParser::isAbsoluteLink(string link, const string baseLink)
{
	if(link.find(baseLink)<=7)return true;//if starts with base - already absolute
	if(link.find("//")!=string::npos)return true;//if has with "//" - absolute (http://, ftp://)
	return false; //it seems it is not absolute, but it is not 100%
}

// \/ updated by Nazar G.
void RegexpParser::relative2Absolute(vector<string>& links, const string baseLink)
{
	unsigned int i;
	for(i=0;i<links.size();i++)
		if(!isAbsoluteLink(links[i],getHostName(baseLink))) // more precise checking
//		if(!isAbsoluteLink(links[i],baseLink)) //link is relative so convert it to absolute
		{			

			bool linkBeginsWithSlash=links[i][0]=='/';
			if (linkBeginsWithSlash)
				links[i] = getHostName(baseLink) + links[i];
			else links[i] = baseLink + links[i];
/*
			bool baseEndsWithSlash=baseLink[baseLink.length()-1]=='/';
			bool linkBeginsWithSlash=links[i][0]=='/';
			if(baseEndsWithSlash && linkBeginsWithSlash)links[i]=baseLink.substr(0,baseLink.length()-1)+links[i];
			 else if(!baseEndsWithSlash && !linkBeginsWithSlash) links[i]=baseLink+"/"+links[i];
			 else links[i]=baseLink+links[i];
*/
		}
}
// /\ updated by Nazar G.
}}}}}