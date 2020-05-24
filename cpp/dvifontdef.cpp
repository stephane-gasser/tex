#include "dvifontdef.h"
#include "dviswap.h"
#include "dvifour.h"

void dvifontdef(internalfontnumber f)

{
	dvibuf[dviptr++] = fnt_def1;
	if (dviptr == dvilimit)
		dviswap();
	dvibuf[dviptr++] = f-1;
	if (dviptr == dvilimit)
		dviswap();
	dvibuf[dviptr++] = fontcheck[f].b0;
	if (dviptr == dvilimit)
		dviswap();
	dvibuf[dviptr++] = fontcheck[f].b1;
	if (dviptr == dvilimit)
		dviswap();
	dvibuf[dviptr++] = fontcheck[f].b2;
	if (dviptr == dvilimit)
		dviswap();
	dvibuf[dviptr++] = fontcheck[f].b3;
	if (dviptr == dvilimit)
		dviswap();
	dvifour(fontsize[f]);
	dvifour(fontdsize[f]);
	dvibuf[dviptr++] = fontarea[f].size();
	if (dviptr == dvilimit)
		dviswap();
	dvibuf[dviptr++] = fontname[f].size();
	if (dviptr == dvilimit)
		dviswap();
	for (auto c: fontarea[f])
	{
		dvibuf[dviptr++] = c;
		if (dviptr == dvilimit)
			dviswap();
	}
	for (auto c: fontname[f])
	{
		dvibuf[dviptr++] = c;
		if (dviptr == dvilimit)
			dviswap();
	}
}
