#include "aopenin.h"

bool aopenin(alphafile& f)
{
	f.open(nameoffile, std::ios_base::in);
	return f.is_open();
}
