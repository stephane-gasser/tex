#include "dvifontdef.h"
#include "dviswap.h"
#include "dvifour.h"

void dvifontdef(internalfontnumber f)

{
	dvibuf[dviptr++] = 243;
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
	dvibuf[dviptr++] = strstart[fontarea[f]+1]-strstart[fontarea[f]];
	if (dviptr == dvilimit)
		dviswap();
	dvibuf[dviptr++] = strstart[fontname[f]+1]-strstart[fontname[f]];
	if (dviptr == dvilimit)
		dviswap();
	for (auto k = strstart[fontarea[f]]; k < strstart[fontarea[f]+1]; k++)
	{
		dvibuf[dviptr++] = strpool[k];
		if (dviptr == dvilimit)
			dviswap();
	}
	for (auto k = strstart[fontname[f]]; k < strstart[fontname[f]+1]; k++)
	{
		dvibuf[dviptr++] = strpool[k];
		if (dviptr == dvilimit)
			dviswap();
	}
}
