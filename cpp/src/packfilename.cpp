#include "packfilename.h"

void packfilename(const std::string &n, const std::string &a, const std::string &e)
{
	int k = 0;
	for (auto c: a)
		append_to_name(k, c);
	for (auto c: n)
		append_to_name(k, c);
	for (auto c: e)
		append_to_name(k, c);
	namelength = std::min(k, filenamesize);
	for (k = namelength+1; k <= filenamesize; k++)
		nameoffile[k] = ' ';
}

void pack_cur_name(void)
{
	packfilename(curname, curarea, curext);
}

