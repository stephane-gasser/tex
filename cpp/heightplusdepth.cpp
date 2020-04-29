#include "heightplusdepth.h"

scaled heightplusdepth(internalfontnumber f, quarterword c)
{
	auto q = fontinfo[charbase[f]+c].qqqq;
	auto hd = q.b1;
	return fontinfo[heightbase[f]+hd/16].int_+fontinfo[depthbase[f]+hd%16].int_;
}
