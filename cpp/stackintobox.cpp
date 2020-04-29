#include "stackintobox.h"
#include "charbox.h"

void stackintobox(halfword b, internalfontnumber f, quarterword c)
{
	auto p = charbox(f, c);
	link(p) = link(b+5);
	link(b+5) = p;
	mem[b+3].int_ = mem[p+3].int_;
}
