#include "printfilename.h"
#include "slowprint.h"

void printfilename(const std::string &n, const std::string &a, const std::string &e)
{
	slowprint(a);
	slowprint(n);
	slowprint(e);
}
