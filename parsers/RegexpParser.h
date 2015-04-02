#ifndef _REGEXP_PARSER_
#define _REGEXP_PARSER_

#include <string>
#include <vector>
using namespace std;


#include "..\IParser.h"

//TODO: this is the most buggy class for the application, so 
//anyone should apply the most of efforts to review it carefully

namespace ua { namespace kiev { namespace ukma { namespace downloader { namespace parsers {
/**
This is the default implementation of the namesake interface 
which retrieve links to external resources 
from given resourse(usually it would be simple text or HTML)
*/
class RegexpParser : public IParser
{
public:
	/**
	Default constructor
	*/
	RegexpParser();
	
	/**
	NOTE: there at least one fail test: for "href='href='http//dsf.fsd.sdf/~da" output is "href=" because of overlap
	Method which parser string text, find web links and return them.
	It use predefined regular expression to find in string such substrings as 
	1) src=''
	2) href=''
	3) action=''
	@param resource input text to search for links
	@return array of the links which are present in the input string	
	*/
	vector<string> getLinks(const string resource);

	/**
	NOTE: this method is not tested, because now it has no usage
	Method which parser string text, find web links and return them.
	It use user defined regular expression to find in string such substrings as link
	@param resource input text to search for links
	@param patterns is the array of the regexp patterns to use as link pattern while retrieving
	@return array of the links which are present in the input string	
	*/
	vector<string> getLinks(const string resource, const vector<string> patterns);

	/**	
	This method convert array of the absolute or relative links to the array of the strictly
	absolute links using baseLink as base. 
	NOTE: If links begin with baseLink it is treated as absolute and are not modified, otherwise baseLink is
	inserter as prefix of the link
	@param links array of the links to convert	
	@param baseLink this is a base address of the relative link(link can by 'shop/car.jpg', but base is 'www.market.ua/images/')	
	*/
	void relative2Absolute(vector<string> &links, const string baseLink);

	/**	
	This is a helper of the method relative2Absolute. It denotes whether the link is absolute
	NOTE: this is the VERY important method of the absolute-process
	@param link this is a link to test
	@param baseLink this is a base address of the relative link(link can by 'shop/car.jpg', but base is 'www.market.ua/images/')
	@return bool which denotes whether link is absolute
	*/
	bool isAbsoluteLink(const string link, const string baseLink);
};

}}}}}
#endif