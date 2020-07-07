#include "morename.h"
#include "erreur.h"

bool morename(ASCIIcode c)
{
	if (c == ' ')
		return false;
	str_room(1);
	append_char(c);
	switch (c)
	{
		case '>':
		case ':':
			areadelimiter = cur_length();
			extdelimiter = 0;
			break;
		case '.':
			if (extdelimiter == 0)
				extdelimiter = cur_length();
	}
	return true;
}
