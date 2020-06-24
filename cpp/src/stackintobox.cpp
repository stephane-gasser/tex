#include "stackintobox.h"
#include "charbox.h"

void stackintobox(halfword b, internalfontnumber f, quarterword c)
{
	auto p = charbox(f, c);
	link(p) = list_ptr(b);
	list_ptr(b) = p;
	height(b) = height(p);
}
