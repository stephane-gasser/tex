#include "wopenout.h"

bool wopenout(wordfile& f)
{
	f.open(nameoffile, std::ios_base::out);
	return f.is_open();
}
