#include "flushmath.h"
#include "flushnodelist.h"

void flushmath(void)
{
	flushnodelist(link(curlist.headfield));
	flushnodelist(curlist.auxfield.int_);
	link(curlist.headfield) = 0;
	curlist.tailfield = curlist.headfield;
	curlist.auxfield.int_ = 0;
}

