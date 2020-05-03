#include "makeunder.h"
#include "newkern.h"
#include "cleanbox.h"
#include "vpackage.h"
#include "fractionrule.h"

void makeunder(halfword q)
{
	auto x = cleanbox(q+1, curstyle);
	auto p = newkern(3 * fontinfo[8+parambase[fam_fnt(3+cursize)]].int_);
	link(x) = p;
	link(p) = fractionrule(fontinfo[8+parambase[fam_fnt(3+cursize)]].int_);
	auto y = vpackage(x, 0, 1, max_dimen);
	scaled delta = mem[y+3].int_+mem[y+2].int_+fontinfo[8+parambase[fam_fnt(3+cursize)]].int_;
	mem[y+3].int_ = mem[x+3].int_;
	mem[y+2].int_ = delta-mem[y+3].int_;
	info(q+1) = y;
	link(q+1) = 2;
}
