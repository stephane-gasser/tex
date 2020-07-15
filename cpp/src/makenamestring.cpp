#include "makenamestring.h"
#include "makestring.h"

std::string makenamestring(void)
{
	if (cur_length() > 0)
		return "?";
	
	strings.push_back(/*currentString+*/nameoffile);
	currentString = "";
	return strings.back();
}
