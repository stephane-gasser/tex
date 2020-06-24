#include "aopenout.h"

bool aopenout(alphafile& f)
{
	f.open(nameoffile, std::ios_base::out);
	return f.is_open();
}
