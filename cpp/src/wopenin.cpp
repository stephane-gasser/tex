#include "wopenin.h"

bool wopenin(wordfile& f)
{
	f.open(nameoffile, std::ios_base::in);
	return f.is_open();
}
