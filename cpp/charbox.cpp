#include "charbox.h"
#include "newnullbox.h"
#include "getavail.h"

halfword charbox(internalfontnumber f, quarterword c)
{
	auto q = fontinfo[charbase[f]+c].qqqq;
	auto hd = q.b1;
	auto b = newnullbox();
	mem[b+1].int_ = fontinfo[widthbase[f]+q.b0].int_+fontinfo[italicbase[f]+q.b2/4].int_;
	mem[b+3].int_ = fontinfo[heightbase[f]+(hd)/16].int_;
	mem[b+2].int_ = fontinfo[depthbase[f]+(hd)%16].int_;
	auto p = getavail();
	subtype(p) = c;
	type(p) = f;
	link(b+5) = p;
	return b;
}
