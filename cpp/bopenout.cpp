#include "bopenout.h"

bool bopenout(bytefile& f)
{
	f.open(nameoffile, std::ios_base::out);
	return f.is_open();
}
