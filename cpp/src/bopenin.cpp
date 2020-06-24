#include "bopenin.h"

bool bopenin(bytefile& f)
{
	f.open(nameoffile, std::ios_base::in);
	return f.is_open();
}
