#include "makevcenter.h"
#include "confusion.h"	
#include "half.h"	

void makevcenter(halfword q)
{
	halfword v = info(q+1);
	if (type(v) != 1)
		confusion(539); //vcenter
	scaled delta = mem[v+3].int_+mem[v+2].int_;
	mem[v+3].int_ = fontinfo[22+parambase[eqtb[3937+cursize].hh.rh]].int_+half(delta);
	mem[v+2].int_ = delta-mem[v+3].int_;
}

