#include "morename.h"
#include "overflow.h"

bool morename(ASCIIcode c)
{
	if (c == ' ')
		return false;
	str_room(1);
	append_char(c);
	if (c == '>' || c == ':')
	{
		areadelimiter = cur_length();
		extdelimiter = 0;
	}
	else 
		if (c == '.' && extdelimiter == 0)
			extdelimiter = cur_length();
	return true;
}
