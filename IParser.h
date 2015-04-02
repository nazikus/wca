#if !defined(_IPARSER_)
#define _IPARSER_

#include <vector>
#include <string>
using namespace std;

/**
This is interface. Its responsibility is to retrieve links to external resources 
from given resourse(usually it would be simple text or HTML)
*/
class IParser  
{
public:
	/**
	Method which parser string text, find web links and return them
	@param resource input text to search for links
	@return array of the links which are present in the input string
	*/
	virtual vector<string> getLinks(const string resource)=0;
	
	/**	
	This method convert array of the absolute or relative links to the array of the strictly
	absolute links using baseLink as base. 
	NOTE: If links begin with baseLink it is treated as absolute and are not modified, otherwise baseLink is
	inserter as prefix of the link
	@param links array of the links to convert	
	@param baseLink this is a base address of the relative link(link can by 'shop/car.jpg', but base is 'www.market.ua/images/')	
	*/
	virtual void relative2Absolute(vector<string> &links, const string baseLink)=0;
};

#endif // !defined(_IPARSER_)